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
// Author: Renato Lóis Marcondes da Silva
// Github: https://github.com/renatolois
// License: all project's source code is licensed under GPL v3.0
//
//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//


#include <cstdlib>
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

#include "core/Window.hpp"
#include "core/Vision.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Textures.hpp"
#include "renderer/Vertex.hpp"
#include "renderer/Shader.hpp"

int main(int argc, char**argv) {
  Window window(600, 600, "MoleculaeXR");
  window.initBackend();
  window.init();

  Vision vision(0);

  // y axis is fliped
  std::vector<Vertex> corner_vertices = {
    // up left
    Vertex( glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) ),
    // up right
    Vertex( glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f) ),
    // bottom left
    Vertex( glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f) ),
    // bottom right
    Vertex( glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f) ),

  };
  
  std::vector<unsigned int> corner_indices {
    0, 1, 2,
    1, 2, 3
  };

  Texture texture("texture_diffuse");
  Mesh mesh(corner_vertices, corner_indices, { texture });
  Shader shader("res/shaders/vertex_shader.glsl", "res/shaders/fragment_shader.glsl");
  
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  double last_time, current_time, delta_time;

  vision.open();
  window.setVisible(true);

  vision.read();
  texture.load(vision.getFramebuffer(), true);

  // main loop
  last_time = window.getCurrentTime();
  while (true) {
    current_time = window.getCurrentTime();
    delta_time = current_time - last_time;
    window.pollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    vision.read();
    texture.update(vision.getFramebuffer(), true);

    glUseProgram(shader.programID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    mesh.draw(shader);
    window.swapBuffers();
    last_time = current_time;
  }

  return EXIT_SUCCESS;
}
