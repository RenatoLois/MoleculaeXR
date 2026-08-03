#pragma once 

#include "polygons/Sphere.hpp"


class Atom {
private:
  unsigned int tag_id;
  float tag_size;
  float radius_constant_factor;
  glm::vec4 default_color;

public:
  Sphere atom_sphere;

  Atom(
    unsigned int tag_id,
    float tag_size,
    float radius_constant_factor = 7.0f / 10.0f,
    float sphere_lat_level = 3,
    float sphere_lon_level = 3,
    glm::vec4 sphere_color = {1.0f, 0.0f, 0.0f, 1.0f}
  );

  float get_tag_size() const;
  void set_tag_id(unsigned int marker_id);
  unsigned int get_tag_id() const;

  glm::vec4 get_color() const;
  void set_color(const glm::vec4& color);
};
