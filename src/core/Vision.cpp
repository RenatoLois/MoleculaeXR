#include "core/Vision.hpp"
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/objdetect/aruco_dictionary.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>

#include "engine/Renderer.hpp"
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
  aruco_params.markerBorderBits = 1;
}




// open camera with id = this->id
void Vision::open() {
  if( this->stream.isOpened() )
    throw std::runtime_error("camera already opened");
  if( !this->stream.open(this->cameraID, cv::CAP_V4L2) ) { // change this on mobile!
/*
    if( this->stream.isOpened() )
*/
      this->stream.release();
    throw std::runtime_error( "failed to open camera with id " + std::to_string(this->cameraID) );
  }

  this->stream.set(cv::CAP_PROP_BUFFERSIZE, 1);
}




// close opened camera
void Vision::close() {
/*
  if( !this->stream.isOpened() )
    throw std::runtime_error("camera already closed");
  else this->stream.release();
*/ 
  this->stream.release();
}



// sends an image from the camera to this->framebuffer
// assuming the camera is opened
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
  cv::aruco::detectMarkers(this->framebuffer,  cv::makePtr<cv::aruco::Dictionary>(aruco_dict), this->tags_corners, this->tag_IDs, cv::makePtr<cv::aruco::DetectorParameters>(aruco_params));
  return !tag_IDs.empty();
}




void Vision::update_camera_background() {
  static bool first_time = true;
  static Renderer bg_renderer;

  static auto camera = std::make_shared<Camera>();

  // x and y axis is fliped
  static std::vector<Vertex> corner_vertices = {
    // up left
    Vertex( glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) ),
    // up right
    Vertex( glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) ),
    // bottom left
    Vertex( glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) ),
    // bottom right
    Vertex( glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) ),
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
    "res/shaders/vertex_bg_shader.glsl",
    "res/shaders/fragment_bg_shader.glsl"
  );
  
  this->read();
  
  static auto bg_material = std::make_shared<Material>(bg_shader);

  if (first_time) {
    camera->set_aspect(1.0f);

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
