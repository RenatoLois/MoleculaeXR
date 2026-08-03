#include "engine/Entity.hpp"
#include <memory>


Entity::Entity(
  const std::shared_ptr<Model> model,
  const Transform& transform
) {
  this->model = model;
  this->transform = transform;
}




Transform Entity::get_transform() const {
  return this->transform;
}




void Entity::set_transform(const Transform& transform) {
  this->transform = transform;
}




void Entity::set_translation(glm::vec3 pos) {
  this->transform.set_position(pos);
}




void Entity::set_rotation(glm::quat rotation) {
  this->transform.set_rotation(rotation);
}




void Entity::set_scale(glm::vec3 scale) {
  this->transform.set_scale(scale);
}




std::shared_ptr<Model> Entity::get_model() const {
  return this->model;
}




glm::mat4 Entity::get_model_matrix() const {
  return this->transform.get_model_matrix();
}




void Entity::add_child(std::shared_ptr<Entity> child) {
    child->parent = this;
    this->children.push_back(child);
}




const std::vector<std::shared_ptr<Entity>>& Entity::get_children() const {
    return this->children;
}
