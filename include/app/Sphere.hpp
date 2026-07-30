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
    Sphere(float radius = 0.5f, int lat_level = 4, int lon_level = 4);
    void set_transform(const Transform& transform);
    void render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light);
};
