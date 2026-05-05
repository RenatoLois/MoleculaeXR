#include "engine/Material.hpp"
#include <memory>
#include <utility>


Material::Material(
  std::shared_ptr<Shader> shader,
  std::shared_ptr<Texture> texture_diffuse,
  std::shared_ptr<Texture> texture_specular,
  // std::shared_ptr<Texture> texture_ambient,
  glm::vec4& color,
  float shininess
) {
  this->shader = std::move(shader);
  this->texture_diffuse = texture_diffuse;
  this->texture_specular = texture_specular;
  // this->texture_ambient = texture_ambient;
  this->color = color;
  this->shininess = shininess;
}




void Material::apply() const {
  this->shader->use();

  if(this->texture_diffuse != nullptr) {
    this->texture_diffuse->bind(0);
  }

  if(this->texture_specular != nullptr) {
    this->texture_specular->bind(1);
  }

  /*
  if(this->texture_ambient != nullptr) {
    this->texture_ambient->bind(2);
  }
  */

  this->shader->set_uniform("material.diffuse", 0);
  this->shader->set_uniform("material.specular", 1);
  // this->shader->set_uniform("material.ambient", 2);

  this->shader->set_uniform("material.shininess", this->shininess);
}




template<typename ...Args>
void Material::set_uniform(Args... args) {
  this->shader->set_uniform(std::forward<Args>(args)...);
}




void Material::set_color(glm::vec4 color) {
  this->color = color;
}




void Material::set_color(float r, float g, float b, float a) {
  this->color = glm::vec4(r, g, b, a);
}




void Material::set_diffuse(std::shared_ptr<Texture> tex) {
  this->texture_diffuse = tex;
}




void Material::set_specular(std::shared_ptr<Texture> tex) {
  this->texture_specular = tex;
}




/*
void Material::set_ambient(std::shared_ptr<Texture> tex) {
  this->texture_ambient = tex;
}
*/
