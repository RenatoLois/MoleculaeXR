#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
private:
  glm::vec3 position = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

public:
  mutable glm::mat4 cached_model_matrix;
  mutable bool dirty = true;
	
// public:
	Transform() = default;
	Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

	void set_position(const glm::vec3& position);
	void set_rotation(const glm::quat& rotation);
	void set_scale(const glm::vec3& scale);

  glm::vec3 get_position() const;
  glm::quat get_rotation() const;
  glm::vec3 get_scale() const;

	glm::mat4 get_model_matrix() const;

  void tranlate_local(glm::vec3 offset);
  void translate_global(glm::vec3 offset);
};
