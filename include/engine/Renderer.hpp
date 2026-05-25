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
  void render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform) const;
  void render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Transform& transform) const;
  void render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Model>& model) const;
  void render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform) const;
  void render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Transform& transform) const;
  void render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Model>& model) const;
  void render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Entity>& entity) const;
  void render(const std::shared_ptr<Camera>& camera, const std::vector<std::shared_ptr<Entity>>& entities) const;
  void set_view_port(Camera& camera, int w, int h) const;
  void set_view_port(int w, int h) const;
};
