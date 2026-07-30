#include "app/Sphere.hpp"
#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "app/cube.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include <memory>
#include <opencv2/objdetect/aruco_detector.hpp>


void initialize(Window& window, Vision& vision);


int main(int argc, char** argv) {

  const float TAG_SIZE_METERS = 0.02f;
  const int TAG_DEBUG_CUBE = 10;
  const int TAG_DEBUG_SPHERE = 11;


  Window window(640, 480, "MoleculaeXR");
  
  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);
  
  cv::aruco::DetectorParameters aruco_parameters = vision.get_aruco_params();
  aruco_parameters.cornerRefinementMethod = cv::aruco::CORNER_REFINE_SUBPIX;
  aruco_parameters.cornerRefinementWinSize = 5;
  aruco_parameters.cornerRefinementMaxIterations = 30;
  aruco_parameters.cornerRefinementMinAccuracy = 0.1;
  aruco_parameters.adaptiveThreshWinSizeMin = 3;
  aruco_parameters.adaptiveThreshWinSizeMax = 23;
  aruco_parameters.adaptiveThreshWinSizeStep = 4;
  aruco_parameters.minMarkerPerimeterRate = 0.02;
  aruco_parameters.maxMarkerPerimeterRate = 4.0;
  aruco_parameters.errorCorrectionRate = 0.6;


  initialize(window, vision);

  Renderer render = Renderer();
  auto ar_camera = std::make_shared<Camera>();

  ar_camera->set_position(glm::vec3(0, 0, 0));
  ar_camera->set_aspect(640.0f / 480.0f);
  ar_camera->set_zoom(60.0f);
  ar_camera->set_near(0.001);
  ar_camera->set_far(10.0f);
  
  auto light = std::make_shared<Light>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
  light->translate(0.0f, 5.0f, 0.0f);
  
  Cube cube(TAG_SIZE_METERS);
  Sphere sphere(TAG_SIZE_METERS / 2, 3, 3);

  double delta_time;

  while(!window.should_close()) {
    window.poll_events();
    delta_time = window.get_delta_time();
    render.clear();
    
    glDisable(GL_DEPTH_TEST);
    vision.update_camera_background(ar_camera->get_aspect());
    glEnable(GL_DEPTH_TEST);

    if(vision.detect_markers()) {
      for (size_t i = 0; i < vision.tag_IDs.size(); ++i) {
        cv::Mat frame = vision.get_framebuffer();
        Transform marker_transform = vision.get_marker_transform(
          vision.tags_corners[i],
          *ar_camera,
          static_cast<float>(frame.cols),
          static_cast<float>(frame.rows),
          TAG_SIZE_METERS
        );

        marker_transform.tranlate_local({0.0f, 0.0f, TAG_SIZE_METERS});

        switch (vision.tag_IDs[i]) {
          case TAG_DEBUG_CUBE:
            cube.set_transform(marker_transform);
            cube.render(render, ar_camera, light);
            break;
          case TAG_DEBUG_SPHERE:
            sphere.set_transform(marker_transform);
            sphere.render(render, ar_camera, light);
            break;
          default:
            break;
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
