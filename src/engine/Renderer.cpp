#include "glad/glad.h"
#include "engine/Renderer.hpp"
#include "engine/Material.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"


void Renderer::render(const Mesh& mesh, Material& material, const glm::mat4& transform) {
  material.apply();
  mesh.bind();
  material.set_uniform("material.local_transform", transform);
  glDrawElements(GL_TRIANGLES, mesh.get_indices_size(), GL_UNSIGNED_INT, (void*) 0);
}




void Renderer::render(const Mesh& mesh, Material& material, const Transform& transform) {
  this->render(mesh, material, transform.get_model_matrix());
}




void Renderer::render(Model& model) {
  for(auto& model_piece: model.get_model_pieces()) {
    this->render(* model_piece.mesh, * model_piece.material, model_piece.transform);
  }
}




void Renderer::render(Entity& entity) {
  glm::mat4 model_matrix = entity.get_model_matrix();
  std::shared_ptr<Model> model = entity.get_model();
  for(auto& model_piece: model->get_model_pieces()) {
    glm::mat4 final_transform = model_matrix * model_piece.transform.get_model_matrix();
    this->render(* model_piece.mesh, * model_piece.material, final_transform);
  }
}




void Renderer::render(std::vector<std::shared_ptr<Entity>>& entities) {
  for(auto& entity: entities) {
    this->render(*entity);
  }
}
