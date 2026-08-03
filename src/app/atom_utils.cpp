#include "app/atom_utils.hpp"
#include <cmath>


float get_position_distances(const Transform& p1, const Transform& p2) {
  glm::vec3 pos1, pos2;
  pos1 = p1.get_position();
  pos2 = p2.get_position();
  return sqrt(
    (pos1.x - pos2.x) * (pos1.x - pos2.x) +
    (pos1.y - pos2.y) * (pos1.y - pos2.y) +
    (pos1.z - pos2.z) * (pos1.z - pos2.z)
  );
}

bool verify_distance_higher_than(const Transform& p1, const Transform& p2, const float distance) {
  glm::vec3 pos1, pos2;
  pos1 = p1.get_position();
  pos2 = p2.get_position();
  return (
    (pos1.x - pos2.x) * (pos1.x - pos2.x) +
    (pos1.y - pos2.y) * (pos1.y - pos2.y) +
    (pos1.z - pos2.z) * (pos1.z - pos2.z)
  ) > ( distance * distance);
}
