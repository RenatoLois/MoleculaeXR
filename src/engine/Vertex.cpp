#include "engine/Vertex.hpp"

Vertex::Vertex(
  glm::vec3 position,
  glm::vec3 normal,
  glm::vec2 tex  // = glm::vec2(0, 0)
) {
  this->position = position;
  this->normal = normal;
  this->tex = tex;
}
