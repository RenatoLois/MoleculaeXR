#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "app/cube.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include <memory>


void initialize(Window& window, Vision& vision);


int main(int argc, char** argv) {
  Window window(600, 600, "MoleculaeXR");
  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

  initialize(window, vision);

  Renderer render = Renderer();
  auto camera = std::make_shared<Camera>();

  camera->set_position(glm::vec3(0.2,1, 5));
  
  auto light = std::make_shared<Light>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);

  Cube cube = Cube();
  light->translate(0.0f, 5.0f, 0.0f);

  // problema: a cor nao ta indo certo: testar normal e etc.

  double delta_time;
  while(!window.should_close()) {
    window.poll_events();
    delta_time = window.get_delta_time();
    render.clear();

    glDisable(GL_DEPTH_TEST);
    vision.update_camera_background();
    glEnable(GL_DEPTH_TEST);
    cube.render(render, camera, light);

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
