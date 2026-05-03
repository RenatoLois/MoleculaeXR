#include "engine/Renderer.hpp"
#include "engine/Material.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"
#include <glm/fwd.hpp>


void Renderer::render(Mesh& mesh, Material& material, Transform& Transform) {
  material.apply();
  mesh.
}




void Renderer::render(Entity& entity) {
  glm::mat4 model_matrix = entity.get_model_matrix();
  std::shared_ptr<Model> model = entity.get_model();

}




void Renderer::render(std::vector<std::shared_ptr<Entity>> entities) {
  for(auto entity: entities) {
    this->render(*entity);
  }
}
