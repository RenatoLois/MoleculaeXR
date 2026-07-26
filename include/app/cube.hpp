#pragma once
#include "engine/Entity.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include "engine/Renderer.hpp"

#include <memory>
class Cube {
  private:
    std::shared_ptr<Entity> cube_entity;

  public:
    Cube(float size_factor = 1.0f);
    void set_transform(const Transform& transform);
    void render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light);
};
