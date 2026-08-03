#pragma once


#include "engine/Transform.hpp"

float get_position_distances(const Transform& p1, const Transform& p2);

bool verify_distance_higher_than(const Transform& p1, const Transform& p2, const float distance);
