#pragma once 

#include "app/Atom.hpp"
#include "app/ATOM_TAG_IDS_CONSTANTS.hpp"


class Oxygen: public Atom {
private:
  inline static glm::vec4 sphere_color = OXYGEN_SPHERE_COLOR;
  inline static float radius_constant_factor = 7.0f / 10.0f;

public:
  Oxygen (
    unsigned int tag_id,
    float tag_size,
    float sphere_lat_level = 3,
    float sphere_lon_level = 3
  );
};
