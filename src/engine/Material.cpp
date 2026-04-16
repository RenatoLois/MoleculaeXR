#include "engine/Material.hpp"
#include <memory>


Material::Material(std::shared_ptr<Shader> shader) {
  this->shader = shader;
  this->color = glm::vec4(1.0f);
  this->texture_diffuse = nullptr;
  this->texture_specular = nullptr;
  // this->texture_ambient = nullptr;
}




void Material::bind() {
  this->shader->use();
  
  this->shader->set_vec4("u_color", this->color);

  if(this->texture_diffuse != nullptr) {
    this->texture_diffuse->bind(0);
  }

  if(this->texture_specular != nullptr) {
    this->texture_specular->bind(1);
  }

  this->shader->set_float("u_shininess", this->shininess);
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
