#pragma once

#include <glm/glm.hpp>

class Vertex {
public:
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex;

  // construtor
  Vertex(
    glm::vec3 position,
    glm::vec3 normal,
    glm::vec2 tex = glm::vec2(0, 0)
  );
};
