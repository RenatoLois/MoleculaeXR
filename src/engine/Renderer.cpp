#include "glad/glad.h"
#include "engine/Renderer.hpp"
#include "engine/Material.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"
#include "core/Logger.hpp"


void Renderer::render(const Camera& camera, const Mesh& mesh, Material& material, const glm::mat4& transform) {
  material.apply();
  mesh.bind();
  material.set_uniform("material.local_transform", transform);
  material.set_uniform("material.camera_view", camera.get_view_matrix());
  material.set_uniform("material.camera_projection", camera.get_projection_matrix());
  glDrawElements(GL_TRIANGLES, mesh.get_indices_size(), GL_UNSIGNED_INT, (void*) 0);
}




void Renderer::render(const Camera& camera, const Mesh& mesh, Material& material, const Transform& transform) {
  this->render(camera, mesh, material, transform.get_model_matrix());
}




void Renderer::render(const Camera& camera, Model& model) {
  for(auto& model_piece: model.get_model_pieces()) {
    this->render(camera, * model_piece.mesh, * model_piece.material, model_piece.transform);
  }
}




void Renderer::render(const Camera& camera, Entity& entity) {
  glm::mat4 model_matrix = entity.get_model_matrix();
  std::shared_ptr<Model> model = entity.get_model();
  for(auto& model_piece: model->get_model_pieces()) {
    glm::mat4 final_transform = model_matrix * model_piece.transform.get_model_matrix();
    this->render(camera, * model_piece.mesh, * model_piece.material, final_transform);
  }
}




void Renderer::render(const Camera& camera, std::vector<std::shared_ptr<Entity>>& entities) {
  for(auto& entity: entities) {
    this->render(camera, *entity);
  }
}




void Renderer::set_view_port(Camera& camera, int w, int h) {
  if(h == 0) {
    Logger::warn("renderer height is 0");
    return;
  }
  
  camera.set_aspect((float) w / (float) h);
}
