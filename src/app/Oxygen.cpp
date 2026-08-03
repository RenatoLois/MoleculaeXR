#include "app/Oxygen.hpp"


Oxygen::Oxygen(
  unsigned int tag_id,
  float tag_size,
  float sphere_lat_level,  // default = 3
  float sphere_lon_level   // default = 3
): Atom(
  tag_id,
  tag_size,
  Oxygen::radius_constant_factor,
  sphere_lat_level,
  sphere_lon_level,
  Oxygen::sphere_color
) {}

