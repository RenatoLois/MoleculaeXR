#pragma once
#include "engine/Entity.hpp"
#include "engine/Camera.hpp"
#include "engine/Renderer.hpp"

#include <memory>
class Cube {
  private:
    std::shared_ptr<Entity> cube_entity;

  public:
    Cube();
    void render(const Renderer& render, const std::shared_ptr<Camera>& camera);
};
