#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "app/cube.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include <memory>


void initialize(Window& window, Vision& vision);


int main(int argc, char** argv) {

  const float TAG_SIZE_METERS = 0.02f;
  const int TAG_DEBUG_CUBE = 10;


  Window window(640, 480, "MoleculaeXR");
  
  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

  initialize(window, vision);

  Renderer render = Renderer();
  auto ar_camera = std::make_shared<Camera>();

  ar_camera->set_position(glm::vec3(0, 0, 0));
  ar_camera->set_aspect(640.0f / 480.0f);
  
  auto light = std::make_shared<Light>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
  light->translate(0.0f, 5.0f, 0.0f);
  
  Cube cube = Cube(TAG_SIZE_METERS);

  double delta_time;

  while(!window.should_close()) {
    window.poll_events();
    delta_time = window.get_delta_time();
    render.clear();
    
    glDisable(GL_DEPTH_TEST);
    vision.update_camera_background();
    glEnable(GL_DEPTH_TEST);

    if(vision.detect_markers()) {
      for (size_t i = 0; i < vision.tag_IDs.size(); ++i) {
        switch (vision.tag_IDs[i]) {

          

          case TAG_DEBUG_CUBE:
            cv::Mat frame = vision.get_framebuffer();
            Transform marker_transform = vision.get_marker_transform(
              vision.tags_corners[i],
              *ar_camera,
              static_cast<float>(frame.cols),
              static_cast<float>(frame.rows),
              TAG_SIZE_METERS
            );

            glm::vec3 pos = marker_transform.get_position();
            glm::quat rot = marker_transform.get_rotation();

            cube.set_transform(marker_transform);
            cube.render(render, ar_camera, light);

            std::cout << "=== MARKER " << TAG_DEBUG_CUBE << " DETECTADO ===" << std::endl; 
            std::cout << "Cantos (pixels):" << std::endl;
            for (auto& corner : vision.tags_corners[i]) {
              std::cout << "  (" << corner.x << ", " << corner.y << ")" << std::endl;
            }
            std::cout << "Posição 3D (metros/unidades):" << std::endl;
            std::cout << "  x: " << pos.x << std::endl;
            std::cout << "  y: " << pos.y << std::endl;
            std::cout << "  z: " << pos.z << std::endl;
            
            std::cout << "Rotação (quaternion):" << std::endl;
            std::cout << "  w: " << rot.w << std::endl;
            std::cout << "  x: " << rot.x << std::endl;
            std::cout << "  y: " << rot.y << std::endl;
            std::cout << "  z: " << rot.z << std::endl;
            
            std::cout << "Escala: (1.0, 1.0, 1.0)" << std::endl;
            std::cout << "================================" << std::endl;

        }
      }
    }

    window.swap_buffers();
  }
}


void initialize(Window& window, Vision& vision) {
  vision.open();
  window.init_backend();
  window.init();
  window.set_visible(true);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.01f, 0.03f, 0.1f, 1.0f);
}
