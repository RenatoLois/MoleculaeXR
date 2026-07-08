#pragma once
#include "engine/Entity.hpp"
#include "engine/Camera.hpp"
#include "engine/Light.hpp"
#include "engine/Renderer.hpp"

#include <memory>
class Sphere {
  private:
    std::shared_ptr<Entity> sphere_entity;

  public:
    Sphere(float radius = 1, int h_level = 4, int v_level = 4);
    void render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light);
};
