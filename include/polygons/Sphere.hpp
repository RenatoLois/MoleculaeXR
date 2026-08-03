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
    Sphere(
      float radius = 0.5f,
      int lat_level = 4,
      int lon_level = 4,
      glm::vec4 sphere_color = {1.0f, 0.0f, 0.0f, 1.0f}
    );
    void set_transform(const Transform& transform);
    void set_color(const glm::vec4& color);
    glm::vec4 get_color() const;
    void render(const Renderer& render, const std::shared_ptr<Camera>& camera, std::shared_ptr<Light>& light);
};
