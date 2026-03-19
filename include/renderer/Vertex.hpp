#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex;


  // construtor
  Vertex(  glm::vec3 position, glm::vec3 normal, glm::vec2 tex);

  // construtor sem definir textura (as coordenadas de textura ficam como {0, 0})
  Vertex(glm::vec3 position, glm::vec3 normal);
};
