#include "app/Hydrogen.hpp"
#include "app/Oxygen.hpp"
#include "app/atom_utils.hpp"
#include "core/Window.hpp"
#include "core/Vision.hpp"
#include "polygons/Sphere.hpp"
#include "polygons/cube.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include "app/ATOM_TAG_IDS_CONSTANTS.hpp"
#include <memory>
#include <algorithm>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <stdio.h>

#define RENDER_ATOM(tag_id, atom_obj) \
  do { \
    if (detected_tags[(tag_id)].active) { \
      Transform smooth_transform = Transform::smooth_transform( \
        detected_tags[(tag_id)].last_marker_transform, \
        detected_tags[(tag_id)].current_marker_transform, \
        25.0f, \
        delta_time \
      ); \
      (atom_obj).atom_sphere.set_transform(smooth_transform); \
      (atom_obj).atom_sphere.render(render, ar_camera, light); \
    } \
  } while (0)


typedef struct {
  int id;
  Transform current_marker_transform;
  Transform last_marker_transform;
  bool active;
  double time_since_lost;
} DetectedTag;

void initialize(Window& window, Vision& vision);


int main(int argc, char** argv) {
  bool chemical_bonds[NUM_TOTAL_CHEMICAL_BONDS];

  for (int i = 0; i < NUM_TOTAL_CHEMICAL_BONDS; i++) {
    chemical_bonds[i] = false;
  }

  DetectedTag detected_tags[MAX_TAGS_APRILTAG_36H11 + 15];
  std::vector<int> last_tag_ids;
  int active_not_detected_tags[MAX_TAGS_APRILTAG_36H11 + 15]; // criado aqui para otimizar e nao ficar recriando toda hora
  int num_active_not_detected_tags;                           // criado aqui para otimizar e nao ficar recriando toda hora

  glm::vec3 h0_anim_position(0.0f);
  glm::vec3 h1_anim_position(0.0f);

  bool was_bonded_last_frame = false;


  for (size_t i = 0; i < MAX_TAGS_APRILTAG_36H11 + 15; ++i) {
    detected_tags[i].active = false;
    detected_tags[i].time_since_lost = 999.0f;
  }

  Window window(640, 480, "MoleculaeXR");

  int cam_id = 0;
  printf("enter camera id: ");
  scanf("%d", &cam_id);
  
  Vision vision(cam_id, cv::aruco::DICT_APRILTAG_36h11);
  
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

  
  Sphere asphere;
  asphere.get_color();

  ar_camera->set_position(glm::vec3(0, 0, 0));
  ar_camera->set_aspect(640.0f / 480.0f);
  ar_camera->set_zoom(60.0f);
  ar_camera->set_near(0.001);
  ar_camera->set_far(10.0f);
  
  auto light = std::make_shared<Light>(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
  light->translate(0.0f, 5.0f, 0.0f);
 
  Hydrogen hydrogen_0(MOLECULAEXR_TAG_ID_HYDROGEN_0, TAG_SIZE_METERS, 4, 4);
  Hydrogen hydrogen_1(MOLECULAEXR_TAG_ID_HYDROGEN_1, TAG_SIZE_METERS, 4, 4);
  Oxygen oxygen_0(MOLECULAEXR_TAG_ID_OXYGEN_0, TAG_SIZE_METERS, 4, 4);

  Cube cube(TAG_SIZE_METERS);
  Sphere sphere(TAG_SIZE_METERS / 2, 3, 3);

  double delta_time;
  int num_detected_tags = 0;

  while(!window.should_close()) {
    window.poll_events();
    delta_time = window.get_delta_time();
    render.clear();
    
    glDisable(GL_DEPTH_TEST);
    vision.update_camera_background(ar_camera->get_aspect());
    glEnable(GL_DEPTH_TEST);

    // logica de deteccao
    vision.detect_markers();

    num_detected_tags = std::min<int>(vision.tag_IDs.size(), MAX_TAGS_APRILTAG_36H11);

    for (size_t i = 0; i < num_detected_tags; ++i) {
      Transform new_last_marker_transform = detected_tags[vision.tag_IDs[i]].current_marker_transform;
      Transform new_current_marker_transform = vision.get_marker_transform(
        vision.tags_corners[i],
        *ar_camera,
        static_cast<float>(vision.get_framebuffer().cols),
        static_cast<float>(vision.get_framebuffer().rows),
        TAG_SIZE_METERS
      );

      new_current_marker_transform.translate_local({0.0f, 0.0f, TAG_SIZE_METERS});

      detected_tags[vision.tag_IDs[i]] = {
        vision.tag_IDs[i],
        new_current_marker_transform,
        new_last_marker_transform, 
        true, 
        0.0f
      };
    }


    // esse algoritmo eh O(n * m), alternativamente poderia implementar um O(n) percorrendo todo o
    // array, porem preferi utilizar um O(n^2) pois a quantidade de marcadores tende a ser 
    // pequena. Note que o tamanho do array de marcadores são o total de apriltags
    // possíveis + extra por precaussao. mesmo que tivesse 10 marcardores, ainda assim seria
    // menos operacoes. Na verdade o que difere é que nesse é O(n^2) onde N eh a quatidade de
    // marcadores, enquanto no algoritmo O(n), n eh o total de IDs possiveis do dicionario apriltag

    // verificando quem sumiu
    num_active_not_detected_tags = 0;
    for (int i = 0; i < last_tag_ids.size(); i++) {
      int marker_id = last_tag_ids[i];
      auto iterator = std::find(vision.tag_IDs.begin(), vision.tag_IDs.end(), marker_id);
      if (iterator == vision.tag_IDs.end()) {
        detected_tags[marker_id].time_since_lost += delta_time;
        if (detected_tags[marker_id].time_since_lost > MAX_LOST_TIME_TOLERATION) {
          detected_tags[marker_id].active = false;
        } else {
          active_not_detected_tags[ num_active_not_detected_tags++ ] = marker_id;
        }
      }
    }

    // verificando quem apareceu que nao havia antes
    for (int i: vision.tag_IDs) {
      auto iterator = std::find(last_tag_ids.begin(), last_tag_ids.end(), i);
      if (iterator == last_tag_ids.end()) {
        detected_tags[i].active = true;
        detected_tags[i].time_since_lost = 0.0f;
        detected_tags[i].last_marker_transform = detected_tags[i].current_marker_transform;
      }
    }

    last_tag_ids = vision.tag_IDs;
    
    for (int i = 0; i < num_active_not_detected_tags; i++) {
      last_tag_ids.push_back(active_not_detected_tags[i]);
    }
    

    if (detected_tags[TAG_DEBUG_CUBE].active) {
      Transform smooth_transform = Transform::smooth_transform(
        detected_tags[TAG_DEBUG_CUBE].last_marker_transform,
        detected_tags[TAG_DEBUG_CUBE].current_marker_transform,
        25.0f,
        delta_time
      );

      cube.set_transform(smooth_transform);
      cube.render(render, ar_camera, light);
    }

    if (
      detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].active &&
      detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].active &&
      detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].active
    ) {
      // se essa ligacao ainda nao ocorre
      if ( ! chemical_bonds[h0_h1_o0_to_h20_index] ) {
        bool dist_h0_o0_is_bad = verify_distance_higher_than (
          detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].current_marker_transform,
          detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].current_marker_transform,
          MIN_HYDROGEN_OXYGEN_DIST_TO_H2O
        );

        bool dist_h1_o0_is_bad = verify_distance_higher_than (
          detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].current_marker_transform,
          detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].current_marker_transform,
          MIN_HYDROGEN_OXYGEN_DIST_TO_H2O
        );

        if( ! (dist_h0_o0_is_bad || dist_h1_o0_is_bad) ) {
          chemical_bonds[h0_h1_o0_to_h20_index] = true;
        }

      // se esse ligacao ja ocorre
      } else {
        bool dist_h0_o0_is_bad = verify_distance_higher_than (
          detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].current_marker_transform,
          detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].current_marker_transform,
          MIN_HYDROGEN_OXYGEN_DIST_TO_H2O_PLUS_DELTA
        );

        bool dist_h1_o0_is_bad = verify_distance_higher_than (
          detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].current_marker_transform,
          detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].current_marker_transform,
          MIN_HYDROGEN_OXYGEN_DIST_TO_H2O_PLUS_DELTA
        );

        if(dist_h0_o0_is_bad || dist_h1_o0_is_bad) {
          chemical_bonds[h0_h1_o0_to_h20_index] = false;
        }
      }
    } else {
      chemical_bonds[h0_h1_o0_to_h20_index] = false;
    }

    if (chemical_bonds[h0_h1_o0_to_h20_index] && !was_bonded_last_frame) {
      h0_anim_position = detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].current_marker_transform.get_position();
      h1_anim_position = detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].current_marker_transform.get_position();
    }
    was_bonded_last_frame = chemical_bonds[h0_h1_o0_to_h20_index];

    if( ! chemical_bonds[h0_h1_o0_to_h20_index] ) {
      hydrogen_0.set_color(Transform::smooth_color(hydrogen_0.get_color(), HYDROGEN_SPHERE_COLOR, 3.5f, delta_time));
      hydrogen_1.set_color(Transform::smooth_color(hydrogen_1.get_color(), HYDROGEN_SPHERE_COLOR, 3.5f, delta_time));
      oxygen_0.set_color(Transform::smooth_color(oxygen_0.get_color(), OXYGEN_SPHERE_COLOR, 3.5f, delta_time));

      if (detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].active) {
        RENDER_ATOM(MOLECULAEXR_TAG_ID_HYDROGEN_0, hydrogen_0);
      }

      if (detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].active) {
        RENDER_ATOM(MOLECULAEXR_TAG_ID_HYDROGEN_1, hydrogen_1);
      }

      if (detected_tags[MOLECULAEXR_TAG_ID_OXYGEN_0].active) {
        RENDER_ATOM(MOLECULAEXR_TAG_ID_OXYGEN_0, oxygen_0);
      }
    } else {
      // aqui ocorre a disgraca da animacao
      hydrogen_0.set_color(Transform::smooth_color(hydrogen_0.get_color(), H2O_MOLECULE_COLOR, 2.0f, delta_time));
      hydrogen_1.set_color(Transform::smooth_color(hydrogen_1.get_color(), H2O_MOLECULE_COLOR, 2.0f, delta_time));
      oxygen_0.set_color(Transform::smooth_color(oxygen_0.get_color(), H2O_MOLECULE_COLOR, 2.0f, delta_time));

      RENDER_ATOM(MOLECULAEXR_TAG_ID_OXYGEN_0, oxygen_0);

      glm::vec3 oxygen_pos = oxygen_0.atom_sphere.get_transform().get_position();
      float pull_factor = 0.5f; 

      Transform h0_tag_transform = detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_0].current_marker_transform;
      glm::vec3 h0_tag_pos = h0_tag_transform.get_position();
      h0_tag_transform.set_position(glm::mix(h0_tag_pos, oxygen_pos, pull_factor));
      
      Transform h0_smoothed = Transform::smooth_transform(
        hydrogen_0.atom_sphere.get_transform(),
        h0_tag_transform,
        15.0f,
        delta_time
      );

      hydrogen_0.atom_sphere.set_transform(h0_smoothed);
      hydrogen_0.atom_sphere.render(render, ar_camera, light);
 
      Transform h1_tag_transform = detected_tags[MOLECULAEXR_TAG_ID_HYDROGEN_1].current_marker_transform;
      glm::vec3 h1_tag_pos = h1_tag_transform.get_position();
      h1_tag_transform.set_position(glm::mix(h1_tag_pos, oxygen_pos, pull_factor));
      
      Transform h1_smoothed = Transform::smooth_transform(
        hydrogen_1.atom_sphere.get_transform(),
        h1_tag_transform,
        15.0f,
        delta_time
      );

      hydrogen_1.atom_sphere.set_transform(h1_smoothed);
      hydrogen_1.atom_sphere.render(render, ar_camera, light);
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
