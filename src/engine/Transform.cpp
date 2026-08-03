#include "engine/Transform.hpp"
#include <algorithm>
#include <cmath>
#include <glm/ext/quaternion_common.hpp>


Transform Transform::smooth_transform(
  const Transform& current_transform,
  const Transform& target,
  const float decay_rate, 
  double delta_time
) {
  // exponential decay smoothing -> p = p' - e ^ (-k * t)
  float alpha = 1.0f - exp(-decay_rate * delta_time);

  glm::vec3 smoothed_position = glm::mix(
    current_transform.get_position(),
    target.get_position(),
    alpha
  );

  glm::quat q_target = target.get_rotation();
  glm::quat q_current = current_transform.get_rotation();

  // Se o dot product for negativo, inverte o quaternion alvo para forçar o caminho mais curto
  // trecho recomendado por IA, talvez possa estar errado, preciso estudar mais vetores
  if (glm::dot(q_current, q_target) < 0.0f) {
    q_target = -q_target;
  }

  glm::quat smoothed_rotation = glm::slerp(
    current_transform.get_rotation(),
    q_target,
    alpha
  );

  glm::vec3 smoothed_scale = glm::mix(
    current_transform.get_scale(),
    target.get_scale(),
    alpha
  );

  return Transform(smoothed_position, smoothed_rotation, smoothed_scale);
}




glm::vec4 Transform::smooth_color(const glm::vec4& current_color, const glm::vec4& target_color, float speed, float delta_time) {
  float factor = std::clamp(speed * delta_time, 0.0f, 1.0f);
  return glm::mix(current_color, target_color, factor);
}




glm::vec4 Transform::smooth_color_exponential(
    const glm::vec4& current_color, 
    const glm::vec4& target_color, 
    float decay_rate, 
    double delta_time
) {
    float alpha = 1.0f - std::exp(-decay_rate * static_cast<float>(delta_time));
    return glm::mix(current_color, target_color, alpha);
}




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




void Transform::translate_local(glm::vec3 offset) {
  this->position += this->rotation * offset;
  this->dirty = true;
}




void Transform::translate_global(glm::vec3 offset) {
  this->position += offset;
  this->dirty = true;
}
