#include "app/Hydrogen.hpp"


Hydrogen::Hydrogen(
  unsigned int tag_id,
  float tag_size,
  float sphere_lat_level,  // default = 3
  float sphere_lon_level   // default = 3
): Atom(
  tag_id,
  tag_size,
  Hydrogen::radius_contant_factor,
  sphere_lat_level,
  sphere_lon_level,
  Hydrogen::sphere_color
) {}
