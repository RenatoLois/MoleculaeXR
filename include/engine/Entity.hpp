#pragma once

#include <memory>
#include "engine/Model.hpp"


class Entity {
private:
  std::shared_ptr<Model> model;
  Transform transform;

public:
  Entity() = default;

  void set_translation(glm::vec3 pos);
  void set_rotation(glm::quat rotation);
  void set_scale(glm::vec3 scale);

  std::shared_ptr<Model> get_model() const;
  glm::mat4 get_model_matrix() const;
};
