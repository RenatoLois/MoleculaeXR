#include "renderer/Vertex.hpp"

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex) {
  this->position = position;
  this->normal = normal;
  this->tex = tex;
}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal) {
  this->position = position;
  this->normal = normal;
  this->tex = glm::vec2(0, 0);
}
