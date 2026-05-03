#pragma once

#include <memory>
#include "engine/Mesh.hpp"
#include "engine/Material.hpp"
#include "engine/Transform.hpp"


struct ModelPiece {
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
  Transform transform;
};
