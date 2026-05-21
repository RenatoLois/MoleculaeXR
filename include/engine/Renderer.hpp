#pragma once

#include <memory>
#include <vector>
#include "engine/Entity.hpp"
#include "engine/Mesh.hpp"
#include "engine/Material.hpp"
#include "engine/Transform.hpp"
#include "engine/Model.hpp"
#include "engine/Camera.hpp"


class Renderer {
public:
  void render(const Camera& camera, const Mesh& mesh, Material& material, const glm::mat4& transform);
  void render(const Camera& camera, const Mesh& mesh, Material& material, const Transform& transform);
  void render(const Camera& camera, Model& model);
  void render(const Camera& camera, Entity& entity);
  void render(const Camera& camera, std::vector<std::shared_ptr<Entity>>& entities);
  void set_view_port(Camera& camera, int w, int h);
  void set_view_port(int w, int h);
};
