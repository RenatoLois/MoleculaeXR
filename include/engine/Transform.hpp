#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
private:
	glm::vec3 position = glm::vec3(1.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f);

  mutable glm::mat4 cached_model_matrix;
  mutable bool dirty;
	
public:
	Transform() = default;
	Transform(glm::vec3& position, glm::quat& rotation, glm::vec3& scale);

	void set_position(glm::vec3& position);

	void set_rotation(glm::quat& rotation);

	void set_scale(glm::vec3& rotation);

	glm::mat4 get_model_matrix() const;
};
