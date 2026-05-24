#pragma once

#include <glm/glm.hpp>


class Camera {
private:
  mutable glm::mat4 cached_view_matrix;
  mutable glm::mat4 cached_projection_matrix;
  mutable bool dirty_view = true;
  mutable bool dirty_projection = true;

  glm::vec3 position;
  glm::vec3 front = {0, 0, -1};
  glm::vec3 right;
  glm::vec3 up;
  glm::vec3 world_up = {0, 1, 0};

  float yaw = -90.0f;
  float pitch =  0.0f;

  float zoom =  45.0f;
  float aspect = 4.0f / 3.0f;
  
  /* mexer nisso depois
  float moviment_speed =  2.5f;
  float mouse_sensitivity =  0.1f;
  */

  void update_camera_vectors();

public:
  // construtor com vetores
  Camera(
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f),
    float yaw = -90.0f,
    float pitch = 0.0f,
    float aspect = 4.0f / 3.0f
  );

  // construtor com valores escalares
  Camera(
    float posX, float posY, float posZ,
    float world_upX, float world_upY, float world_upZ,
    float yaw,
    float pitch,
    float aspect = 4.0f / 3.0f
  );

  glm::mat4 get_view_matrix() const;
  glm::mat4 get_projection_matrix() const;

  void set_position(const glm::vec3& pos);
  void set_aspect(const float aspect);
  void set_orientation(float yaw, float pitch);
  void set_target(const glm::vec3& target);
  void set_world_up(const glm::vec3& up);
};
