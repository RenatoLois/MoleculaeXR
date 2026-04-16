#pragma once

#include <memory.h>
#include <memory>
#include <glm/glm.hpp>
#include "engine/Mesh.hpp"
#include "engine/Material.hpp"


class Entity {
private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  glm::vec3 translation;
  glm::mat4 rotation;
  glm::mat4 scale;

public:
  Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {

  }
};
