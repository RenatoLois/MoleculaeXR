#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "engine/Shader.hpp"
#include "engine/Texture.hpp"


class Material {
private:
    //  std::shared_ptr<Texture> texture_ambient;
  std::shared_ptr<Shader> shader;
  std::shared_ptr<Texture> texture_diffuse = nullptr;
  std::shared_ptr<Texture> texture_specular = nullptr;
  glm::vec4 color = glm::vec4(1.0f);
  float shininess = 32.0f;
  bool use_texture = false;

public:
  Material() = default;

  Material(
    std::shared_ptr<Shader> shader = nullptr,
    glm::vec4 color = {0.8f, 0.8f, 0.8f, 1.0f},
    float shininess = 32,
    // std::shared_ptr<Texture> texture_ambient = nullptr,
    std::shared_ptr<Texture> texture_diffuse = nullptr,
    std::shared_ptr<Texture> texture_specular = nullptr
  );


  void apply() const;

  template<typename ...Args>
  void set_uniform(Args... args) {
    this->shader->set_uniform(std::forward<Args>(args)...);
  }

  void set_color(glm::vec4 color);
  void set_color(float r, float g, float b, float a);

  void set_diffuse(std::shared_ptr<Texture> tex);
  void set_specular(std::shared_ptr<Texture> tex);
  // void set_ambient(std::shared_ptr<Texture> tex);

  void set_use_texture(bool value);
};
