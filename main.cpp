#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "app/cube.hpp"
#include "engine/Camera.hpp"
#include <memory>


void initialize(Window& window, Vision& vision);


int main(int argc, char** argv) {
  Window window(600, 600, "MoleculaeXR");
  
  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

  initialize(window, vision);

  Renderer render = Renderer();
  auto camera = std::make_shared<Camera>();

  camera->set_position(glm::vec3(0, 0, 2));

  Cube cube = Cube();

  double delta_time;
  while(!window.should_close()) {
    window.poll_events();
    delta_time = window.get_delta_time();
    render.clear();

    // vision.update_camera_background();
    cube.render(render, camera);

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
