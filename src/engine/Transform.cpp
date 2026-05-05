#include "engine/Transform.hpp"

Transform::Transform(glm::vec3& position, glm::quat& rotation, glm::vec3& scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

  this->dirty = true;
}




void Transform::set_position(glm::vec3& position) {
	this->position = position;
  this-> dirty = true;
}




void Transform::set_rotation(glm::quat& rotation) {
	this->rotation = rotation;
  this->dirty = true;
}




void Transform::set_scale(glm::vec3& scale) {
	this->scale = scale;
  this->dirty = true;
}




glm::mat4 Transform::get_model_matrix() const {
  if(this->dirty) {
  	this->cached_model_matrix = glm::mat4(1.0f);
  	this->cached_model_matrix = glm::scale(this->cached_model_matrix, this->scale);
  	this->cached_model_matrix = this->cached_model_matrix * glm::mat4_cast(this->rotation);
  	this->cached_model_matrix = glm::translate(this->cached_model_matrix, this->position);

    this->dirty = false;
  }

	return this->cached_model_matrix;
}
