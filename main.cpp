//  ┌──────────────────────────────────────────────────────┐
//  │                                                      │
//  │    .   ,     .             .           .   , ,-.     │
//  │    |\ /|     |             |            \ /  |  )    │
//  │    | V | ,-. | ,-. ,-. . . | ,-: ,-.     X   |-<     │
//  │    |   | | | | |-' |   | | | | | |-'    / \  |  \    │
//  │    '   ' `-' ' `-' `-' `-` ' `-` `-'   '   ` '  '    │
//  │                                                      │
//  └──────────────────────────────────────────────────────┘
//
//             (¨¨¨¨¨¨¨¨¨)
//              |¨¨¨¨¨¨¨|
//              |       |
//              |       |
//              |       |
//              /       \
//             /         \          Authors:
//            /           \          * Renato Lóis Marcondes da Silva
//           /             \
//          /   .-'-.     .-\       Github: https://github.com/renatolois
//         /-.-´     `-.-´   \      License: all project's source code is licensed under GPL v3.0
//        /                   \
//       /                     \
//      /                       \
//     /                         \
//     \_________________________/
//   
//
//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// !!! Attention, do not add your name next to another contributor's
// name on the same line; create a new line.
// This will greatly avoid commit conflicts.
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//


#include <cstddef>
#include <cstdlib>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <glad/glad.h>

#include "core/Window.hpp"
#include "core/Vision.hpp"
#include "core/CallbackManager.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Textures.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/Shader.hpp"


// functions declaration








int main(int argc, char**argv) {
  Window window(600, 600, "MoleculaeXR");
  window.initBackend();
  window.init();

  Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

  // x and y axis is fliped
  std::vector<Vertex> corner_vertices = {
    // up left
    Vertex( glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) ),
    // up right
    Vertex( glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) ),
    // bottom left
    Vertex( glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) ),
    // bottom right
    Vertex( glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) ),
  };
  
  std::vector<unsigned int> corner_indices {
    0, 1, 2,
    1, 2, 3
  };

  Texture texture_bg("texture_diffuse");
  Mesh mesh_bg(corner_vertices, corner_indices, { texture_bg });
  Shader shader_bg("res/shaders/vertex_shader_bg.glsl", "res/shaders/fragment_shader_bg.glsl");
  
// testing cube
  std::vector<Vertex> cube_vertices = {
    // up front left
    Vertex( glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,   0.0f, 0.0f), glm::vec2(0.0f, 0.0f) ),
    // up front right
    Vertex( glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,   0.0f, 0.0f), glm::vec2(1.0f, 0.0f) ),
    // bottom front left
    Vertex( glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,   0.0f, 0.0f), glm::vec2(0.0f, 1.0f) ),
    // bottom front right
    Vertex( glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,   0.0f, 0.0f), glm::vec2(1.0f, 1.0f) ),
    // up back left
    Vertex( glm::vec3(-0.4f,  0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) ),
    // up back right
    Vertex( glm::vec3( 0.5f,  0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec2(0.5f, 0.0f) ),
    // bottom back left
    Vertex( glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.5f) ),
    // bottom back right
    Vertex( glm::vec3( 0.5f, -0.5f,  0.0f), glm::vec3( 0.0f,  0.0f,  0.0f), glm::vec2(0.5f, 1.0f) ),
  };

  std::vector<unsigned int> cube_indices = {
    // front-
    0, 1, 2,
    1, 2, 3,
    // back
    4, 5, 6,
    5, 6, 7,
    // top 
    0, 1, 4,
    1, 4, 5,
    // bottom 
    2, 3, 5,
    3, 5, 6,
    // left 
    0, 2, 4,
    2, 4, 6,
    // right 
    1, 3, 5,
    3, 5, 7
  };

  Mesh mesh_cube(cube_vertices, cube_indices);
  Shader shader_cube("res/shaders/vertex_shader.glsl", "res/shaders/fragment_shader.glsl");

  glm::mat4 model, view, projection;
  model = view = projection = glm::mat4(1.0f);
  model = glm::scale(model, glm::vec3(0.5f));

  shader_cube.setMat4("view_matrix", view);
  shader_cube.setMat4("projection_matrix", projection);

  shader_bg.setMat4("view_matrix", glm::mat4(1.0f));
  shader_bg.setMat4("projection_matrix", glm::mat4(1.0f));
// ! testing

  glClearColor(0.04f, 0.04f, 0.08f, 1.0f);

  double last_time, current_time, delta_time;

  vision.open();
  window.setVisible(true);

  vision.read();
  texture_bg.load(vision.getFramebuffer(), true);

  // main loop
  last_time = window.getCurrentTime();
  size_t total_tags_detected;

  while ( !window.shouldClose() ) {
    current_time = window.getCurrentTime();
    delta_time = current_time - last_time;
    window.pollEvents();

    glUseProgram(shader_bg.programID);
    glClear(GL_COLOR_BUFFER_BIT);
    vision.read();
    texture_bg.update(vision.getFramebuffer(), true);

    if( vision.detectMarkers() ) {
      total_tags_detected = vision.tag_IDs.size();
      for(size_t i = 0; i < total_tags_detected; i++) {
        std::cout << vision.tags_corners[i];
      }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_bg.id);

    mesh_bg.draw(shader_bg, glm::mat4(1.0f));

// testing
    glUseProgram(shader_cube.programID);
    mesh_cube.draw(shader_cube, model);
// !testing

    glUseProgram(0);


    window.swapBuffers();
    last_time = current_time;
  }

  return EXIT_SUCCESS;
}
