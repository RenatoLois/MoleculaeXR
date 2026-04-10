#include "renderer/Material.hpp"
#include <memory>


Material::Material(std::shared_ptr<Shader> shader) {
  this->shader = shader;
  this->color = glm::vec4(1.0f);
}

void Material::bind() {
  this->shader->use();
}

void Material::setColor(glm::vec4 color) {
  this->color = color;
}

void Material::setColor(float r, float g, float b, float a) {
  this->color = glm::vec4(r, g, b, a);
}
