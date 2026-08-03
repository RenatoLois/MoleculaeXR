#include "app/Atom.hpp"

Atom::Atom (
  unsigned int tag_id,
  float tag_size,
  float radius_constant_factor,  // default = 7.0f / 10.0f
  float sphere_lat_level,        // default = 3
  float sphere_lon_level,        // default = 3
  glm::vec4 sphere_color         // default = {1.0f, 0.0f, 0.0f, 1.0f}
) {
  this->tag_id = tag_id;
  this->tag_size = tag_size;
  this->radius_constant_factor = radius_constant_factor;

  this->atom_sphere = Sphere(
    tag_size * this->radius_constant_factor,
    sphere_lat_level,
    sphere_lon_level,
    sphere_color
  );
}

float Atom::get_tag_size() const {
  return this->tag_size;
}




void Atom::set_tag_id(unsigned int tag_id) {
  this->tag_id = tag_id;
}




unsigned int Atom::get_tag_id() const {
  return this->tag_id;
}




glm::vec4 Atom::get_color() const {
  return this->atom_sphere.get_color();
}




void Atom::set_color(const glm::vec4& color) {
  this->atom_sphere.set_color(color);
}
