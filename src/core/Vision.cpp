#include "core/Vision.hpp"
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/objdetect/aruco_dictionary.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>

#include "engine/Camera.hpp"
#include "engine/Renderer.hpp"
#include "engine/Transform.hpp"
#include "engine/Vertex.hpp"
#include "engine/Shader.hpp"
#include "engine/Texture.hpp"
#include "engine/Mesh.hpp"
#include "engine/Model.hpp"
#include "engine/Material.hpp"

Vision::Vision(int cameraID, cv::aruco::PredefinedDictionaryType marker_type) {
  this->cameraID = cameraID;
  this->aruco_dict   = cv::aruco::getPredefinedDictionary(marker_type);
  this->aruco_params = cv::aruco::DetectorParameters();
  this->aruco_params.markerBorderBits = 1;
}




void Vision::set_aruco_params(const cv::aruco::DetectorParameters& aruco_params) {
  this->aruco_params = aruco_params;
}




cv::aruco::DetectorParameters Vision::get_aruco_params() const {
  return this->aruco_params;
}




// abre a câmera com o id = this->id
void Vision::open() {
  if( this->stream.isOpened() )
    throw std::runtime_error("camera already opened");
  if( !this->stream.open(this->cameraID, cv::CAP_V4L2) ) {
/*
    if( this->stream.isOpened() )
*/
      this->stream.release();
    throw std::runtime_error( "failed to open camera with id " + std::to_string(this->cameraID) );
  }

  this->stream.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  this->stream.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

  this->stream.set(cv::CAP_PROP_BUFFERSIZE, 1);
}




// fechar camera aberta
void Vision::close() {
/*
  if( !this->stream.isOpened() )
    throw std::runtime_error("camera already closed");
  else this->stream.release();
*/ 
  this->stream.release();
}



// envia a imagem da câmera para this->framebuffer
// assumindo que a câmera está aberta
bool Vision::read() {
  return this->stream.read(this->framebuffer);
}




// get this->framebuffer
cv::Mat Vision::get_framebuffer() {
  return this->framebuffer;
}




// detect april tags in framebuffer image
// // returns false if no tag is found, otherwise returns true
bool Vision::detect_markers() {
  cv::cvtColor(this->framebuffer, this->gray_frame, cv::COLOR_BGR2GRAY);

  cv::aruco::detectMarkers(
    this->gray_frame, 
    cv::makePtr<cv::aruco::Dictionary>(aruco_dict),
    this->tags_corners, this->tag_IDs,
    cv::makePtr<cv::aruco::DetectorParameters>(aruco_params));
  return !tag_IDs.empty();
}



// procurar entender essa lógica depois, gerado por IA
Transform Vision::get_marker_transform(
    const std::vector<cv::Point2f>& tag_corners,
    const Camera& camera,
    float image_width,
    float image_height,
    float tag_size
) {
    // Garante que temos exatamente 4 cantos para resolver o PnP
    if (tag_corners.size() != 4) return Transform();

    float half = tag_size / 2.0f;

    // Coordenadas 3D do objeto (Top-Left, Top-Right, Bottom-Right, Bottom-Left)
    std::vector<cv::Point3f> object_points = {
        cv::Point3f(-half,  half, 0.0f),
        cv::Point3f( half,  half, 0.0f),
        cv::Point3f( half, -half, 0.0f),
        cv::Point3f(-half, -half, 0.0f)
    };

    // Parâmetros Intrínsecos da Câmera
    float fov_y_rad = glm::radians(camera.get_zoom());
    float fy = (image_height / 2.0f) / std::tan(fov_y_rad / 2.0f);
    float fx = fy; // Assumindo pixels quadrados

    float cx = image_width / 2.0f;
    float cy = image_height / 2.0f;

    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) <<
        fx,  0.0, cx,
        0.0, fy,  cy,
        0.0, 0.0, 1.0
    );

    cv::Mat rvec, tvec;
    cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, CV_64F);

    bool success = cv::solvePnP(
        object_points,
        tag_corners,
        camera_matrix,
        dist_coeffs,
        rvec,
        tvec,
        false,
        cv::SOLVEPNP_IPPE_SQUARE
    );

    if (!success) {
        return Transform();
    }

    cv::Mat rotation_matrix;
    cv::Rodrigues(rvec, rotation_matrix);

    // Inversão de Y e Z para compatibilidade com o sistema de coordenadas do OpenGL
    glm::vec3 position(
        static_cast<float>(tvec.at<double>(0)),
        static_cast<float>(-tvec.at<double>(1)),
        static_cast<float>(-tvec.at<double>(2))
    );

    // Mapeamento correto da matriz 3x3 OpenCV para GLM (Column-Major)
    glm::mat3 glm_rot(1.0f);
    
    // Coluna 0
    glm_rot[0][0] =  static_cast<float>(rotation_matrix.at<double>(0,0));
    glm_rot[0][1] = -static_cast<float>(rotation_matrix.at<double>(1,0));
    glm_rot[0][2] = -static_cast<float>(rotation_matrix.at<double>(2,0));

    // Coluna 1
    glm_rot[1][0] =  static_cast<float>(rotation_matrix.at<double>(0,1));
    glm_rot[1][1] = -static_cast<float>(rotation_matrix.at<double>(1,1));
    glm_rot[1][2] = -static_cast<float>(rotation_matrix.at<double>(2,1));

    // Coluna 2
    glm_rot[2][0] =  static_cast<float>(rotation_matrix.at<double>(0,2));
    glm_rot[2][1] = -static_cast<float>(rotation_matrix.at<double>(1,2));
    glm_rot[2][2] = -static_cast<float>(rotation_matrix.at<double>(2,2));

    glm::quat rotation = glm::quat_cast(glm_rot);

    return Transform(position, rotation, glm::vec3(1.0f));
}





void Vision::update_camera_background(float aspect_ratio) {
  static bool first_time = true;
  static Renderer bg_renderer;

  static auto camera = std::make_shared<Camera>();

  // x and y axis is fliped
  static std::vector<Vertex> corner_vertices = {
    // up left
    Vertex( glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) ),
    // up right
    Vertex( glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) ),
    // bottom left
    Vertex( glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) ),
    // bottom right
    Vertex( glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) ),
  };
  
  static std::vector<unsigned int> corner_indices {
    0, 1, 2,
    1, 2, 3
  };

  static auto texture_background = std::make_shared<Texture>(
    Texture()
  );

  static auto bg_mesh = std::make_shared<Mesh>(
    corner_vertices,
    corner_indices
  );

  static auto bg_shader = std::make_shared<Shader>(
    "res/shaders/vertex_shader_bg.glsl",
    "res/shaders/fragment_shader_bg.glsl"
  );
  
  this->read();
  
  static auto bg_material = std::make_shared<Material>(bg_shader);

  if (first_time) {
    camera->set_aspect(aspect_ratio);

    texture_background->load(this->get_framebuffer(), true);
    
    bg_material->set_diffuse(texture_background);
    bg_material->set_use_texture(true);


  } else {
    texture_background->update(this->get_framebuffer(), true);
  }

  
  static Transform bg_transform(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  );


  static auto bg_model = std::make_shared<Model>(
    (std::vector<std::shared_ptr<Mesh>>) { bg_mesh },
    (std::vector<std::shared_ptr<Material>>) { bg_material },
    (std::vector<Transform>) { bg_transform }
  );

  bg_renderer.render_fullscreen_ortho(camera, bg_model);

  /* para debug
  if (first_time) {

    glm::mat4 transform_matrix = bg_transform.get_model_matrix();
    glm::mat4 view_matrix = camera->get_view_matrix();
    glm::mat4 proj_matrix = camera->get_ortho_matrix();

    auto print_mat4 = [](const glm::mat4& m, const char* name) {
        printf("%s:\n", name);
        for (int row = 0; row < 4; ++row) {
            for (int col = 0; col < 4; ++col) {
                printf("%8.4f ", m[col][row]);
            }
            printf("\n");
        }
        printf("\n");
        fflush(stdout);
    };

    print_mat4(transform_matrix, "Transform");
    print_mat4(view_matrix, "View");
    print_mat4(proj_matrix, "Projection");
  }
  */

  if(first_time) first_time = false;
}
