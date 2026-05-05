#pragma once

#include <memory>
#include <vector>
#include "engine/Entity.hpp"


class Renderer {
public:

  void render(const Mesh& mesh, Material& material, const glm::mat4& transform);
  void render(const Mesh& mesh, Material& material, const Transform& transform);
  void render(Model& model);
  void render(Entity& entity);
  void render(std::vector<std::shared_ptr<Entity>>& entities);
};
