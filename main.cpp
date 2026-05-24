#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "engine/Camera.hpp"
#include "engine/Texture.hpp"
#include "engine/Vertex.hpp"
#include "engine/Mesh.hpp"
#include "engine/Shader.hpp"
#include "engine/Renderer.hpp"

#include <memory>
#include <opencv2/objdetect/aruco_dictionary.hpp>


void initialize(Window& window, Vision& vision);
void update_camera_background(Vision& vision);


int main(int argc, char** argv) {
  Window window(600, 600, "MoleculaeXR");
  
  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

  initialize(window, vision);

  double delta_time;
  while(!window.should_close()) {
    window.poll_events();

    delta_time = window.get_delta_time();
    update_camera_background(vision);   

    window.swap_buffers();
  }
}


void initialize(Window& window, Vision& vision) {
  vision.open();
  window.init_backend();
  window.init();
  window.set_visible(true);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}


void update_camera_background(Vision& vision) {
  static bool first_time = true;
  static Renderer bg_renderer;

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

  static auto mesh_bg = std::make_shared<Mesh>(
    corner_vertices,
    corner_indices
  );

  static auto shader_bg = std::make_shared<Shader>(
    "res/shaders/vertex_shader_bg.glsl",
    "res/shaders/fragment_shader_bg.glsl"
  );
  
  vision.read();
  
  static auto material_bg = std::make_shared<Material>(shader_bg);

  if(first_time) {
    texture_background->load(vision.get_framebuffer(), true);
    
    material_bg->set_diffuse(texture_background);
    material_bg->set_use_texture(true);

    first_time = false;

  } else {
    texture_background->update(vision.get_framebuffer(), true);
  }

  
  static Transform transform_bg(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  );


  static auto model_bg = std::make_shared<Model>(
    (std::vector<std::shared_ptr<Mesh>>) { mesh_bg },
    (std::vector<std::shared_ptr<Material>>) { material_bg },
    (std::vector<Transform>) { transform_bg }
  );

  static auto camera = std::make_shared<Camera>();

  bg_renderer.render(camera, model_bg);
}
