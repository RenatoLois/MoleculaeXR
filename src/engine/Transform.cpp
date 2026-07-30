#include "engine/Transform.hpp"
#include <glm/ext/quaternion_common.hpp>

Transform::Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}




void Transform::set_position(const glm::vec3& position) {
	this->position = position;
  this-> dirty = true;
}




void Transform::set_rotation(const glm::quat& rotation) {
	this->rotation = rotation;
  this->dirty = true;
}




void Transform::set_scale(const glm::vec3& scale) {
	this->scale = scale;
  this->dirty = true;
}




glm::mat4 Transform::get_model_matrix() const {
  if(this->dirty) {
  	this->cached_model_matrix = glm::mat4(1.0f);
  	this->cached_model_matrix = glm::translate(this->cached_model_matrix, this->position);
  	this->cached_model_matrix = this->cached_model_matrix * glm::mat4_cast(this->rotation);
  	this->cached_model_matrix = glm::scale(this->cached_model_matrix, this->scale);

    this->dirty = false;
  }

	return this->cached_model_matrix;
}




glm::vec3 Transform::get_position() const {
  return this->position;
}




glm::quat Transform::get_rotation() const {
  return this->rotation;
}




glm::vec3 Transform::get_scale() const {
  return this->scale;
}




void Transform::tranlate_local(glm::vec3 offset) {
  this->position += this->rotation * offset;
  this->dirty = true;
}




void Transform::translate_global(glm::vec3 offset) {
  this->position += offset;
  this->dirty = true;
}
