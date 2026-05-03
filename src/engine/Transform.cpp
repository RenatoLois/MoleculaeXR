#include "engine/Transform.hpp"

Transform::Transform(glm::vec3& position, glm::quat& rotation, glm::vec3& scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}




void Transform::set_position(glm::vec3& position) {
	this->position = position;
}




void Transform::set_rotation(glm::quat& rotation) {
	this->rotation = rotation;
}




void Transform::set_scale(glm::vec3& scale) {
	this->scale = scale;
}




glm::mat4 Transform::get_model_matrix() const {
	glm::mat4 model(1.0f);
	model = glm::scale(model, this->scale);
	model = model * glm::mat4_cast(this->rotation);
	model = glm::translate(model, this->position);
	return model;
}
