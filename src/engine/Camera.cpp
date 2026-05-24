#include "engine/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <cmath>


// implementação inspirada em < https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h >

void Camera::update_camera_vectors() {
  glm::vec3 new_front;

  new_front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
  new_front.y = sin(glm::radians(this->pitch));
  new_front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

  this->front = glm::normalize(new_front);
  this->right = glm::normalize( glm::cross(this->front, this->world_up) );
  this->up    = glm::normalize( glm::cross(this->right, this->front) );
  
  this->dirty_view = true;
}




Camera::Camera(
  glm::vec3 position,  // = glm::vec3(0.0f, 0.0f, 0.0f)
  glm::vec3 up,  // = glm::vec3(0.0f, 1.0f, 0.0f)
  float yaw,  // = -90.0f
  float pitch,  // = 0.0f
  float aspect  // 4.0f / 3.0f
){
  this->position = position;
  this->world_up = up;
  this->yaw = yaw;
  this->pitch = pitch;
  this->aspect = aspect;
  this->update_camera_vectors();
}




Camera::Camera(
  float pos_x, float pos_y, float pos_z, 
  float world_up_x, float world_up_y, float world_up_z, 
  float yaw,
  float pitch,
  float aspect  // 4.0f / 3.0f
) {
  this->position = glm::vec3(pos_x, pos_y, pos_z);
  this->world_up = glm::vec3(world_up_x, world_up_y, world_up_z);
  this->yaw = yaw;
  this->pitch = pitch;
  this->aspect = aspect;
  update_camera_vectors();
}




glm::mat4 Camera::get_view_matrix() const {
  if(this->dirty_view == false) return this->cached_view_matrix;

  this->cached_view_matrix = glm::lookAt(
    this->position,
    this->position + this->front,
    this->up
  );

  this->dirty_view = false;
  return this->cached_view_matrix;
}




glm::mat4 Camera::get_projection_matrix() const {
  if(this->dirty_projection == false) return this->cached_projection_matrix;

  this->cached_projection_matrix = glm::perspective(
    glm::radians(this->zoom),
    this->aspect,
    0.1f,
    100.0f
  );

  this->dirty_projection = false;
  return this->cached_projection_matrix;
}




void Camera::set_position(const glm::vec3& pos) {
  this->position = pos;

  this->dirty_view = true;
}




void Camera::set_aspect(const float aspect) {
  this->aspect = aspect;
  
  this->dirty_projection = true;
}




void Camera::set_orientation(float yaw, float pitch) {
  this->yaw = yaw;
  this->pitch = pitch;
  update_camera_vectors();

//  this->dirty_view = true; // update_camera_vectors() ja faz isso
}




// esse método foi implementado por IA, preciso entender ele depois
// vou aceitar por enquanto devido ao prazo de entrega
void Camera::set_target(const glm::vec3& target) {
  glm::vec3 dir = glm::normalize(target - this->position);
  this->pitch = glm::degrees(asin(dir.y));
  this->yaw   = glm::degrees(atan2(dir.z, dir.x));
  update_camera_vectors();

//  this->dirty_view = true; // update_camera_vectors() ja faz isso
}




void Camera::set_world_up(const glm::vec3& up) {
  this->world_up = up;
  update_camera_vectors();

//  this->dirty_view = true; // update_camera_vectors() ja faz isso
}
