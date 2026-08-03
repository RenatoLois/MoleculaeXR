#pragma once 

#include "app/Atom.hpp"
#include "app/ATOM_TAG_IDS_CONSTANTS.hpp"


class Hydrogen: public Atom {
private:
  inline static glm::vec4 sphere_color = HYDROGEN_SPHERE_COLOR;
  inline static float radius_contant_factor = 4.0f / 10.0f;

public:
  Hydrogen (
    unsigned int tag_id,
    float tag_size,
    float sphere_lat_level = 3,
    float sphere_lon_level = 3
  );
};
