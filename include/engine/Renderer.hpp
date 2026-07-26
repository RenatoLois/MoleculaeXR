#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <vector>
#include "engine/Entity.hpp"
#include "engine/Mesh.hpp"
#include "engine/Material.hpp"
#include "engine/Transform.hpp"
#include "engine/Model.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"

class Renderer {
public:
  void render_fullscreen_ortho(
    const std::shared_ptr<Camera>& camera,
    const std::shared_ptr<Mesh>& mesh,
    const std::shared_ptr<Material>& material, 
    const glm::mat4& transform
  ) const;

  void render_fullscreen_ortho(
    const std::shared_ptr<Camera>& camera, 
    const std::shared_ptr<Mesh>& mesh,
    const std::shared_ptr<Material>& material,
    const Transform& transform
  ) const;

  void render_fullscreen_ortho(
    const std::shared_ptr<Camera>& camera,
    const std::shared_ptr<Model>& model
  ) const;
  
  void render(
    const std::shared_ptr<Camera>& camera, 
    const std::shared_ptr<Mesh>& mesh,
    const std::shared_ptr<Material>& material, 
    const glm::mat4& transform,
    const std::shared_ptr<Light>& light = nullptr
  ) const;

  void render(
    const std::shared_ptr<Camera>& camera, 
    const std::shared_ptr<Mesh>& mesh, 
    const std::shared_ptr<Material>& material,
    const Transform& transform,
    const std::shared_ptr<Light>& light = nullptr
  ) const;

  void render(
    const std::shared_ptr<Camera>& camera,
    const std::shared_ptr<Model>& model,
    const std::shared_ptr<Light>& light = nullptr
  ) const;

  void render(
    const std::shared_ptr<Camera>& camera,
    const std::shared_ptr<Entity>& entity, 
    const std::shared_ptr<Light>& light = nullptr,
    const glm::mat4 parent_transform = glm::mat4(1.0f)
  ) const;

  void render(
    const std::shared_ptr<Camera>& camera,
    const std::vector<std::shared_ptr<Entity>>& entities, 
    const std::shared_ptr<Light>& light = nullptr
  ) const;
  
  void set_view_port(Camera& camera, int w, int h) const;
  void set_view_port(int w, int h) const;
  void clear() const;
};
