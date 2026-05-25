#include "engine/Renderer.hpp"

#include "memory"

#include "glad/glad.h"
#include "engine/Material.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"
#include "core/Logger.hpp"


void Renderer::render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform) const {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  material->apply();
  mesh->bind();
  material->set_uniform("material.transform", transform);
  material->set_uniform("material.camera_view", camera->get_view_matrix());
  material->set_uniform("material.camera_projection", camera->get_ortho_matrix());
  glDrawElements(GL_TRIANGLES, mesh->get_indices_size(), GL_UNSIGNED_INT, (void*) 0);
}

void Renderer::render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Transform& transform) const {
  this->render_fullscreen_ortho(camera, mesh, material, transform.get_model_matrix());
}

void Renderer::render_fullscreen_ortho(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Model>& model) const {
  for(auto& model_piece: model->get_model_pieces()) {
    this->render_fullscreen_ortho(camera, model_piece.mesh, model_piece.material, model_piece.transform);
  }
}


void Renderer::render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform) const {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  material->apply();
  mesh->bind();
  material->set_uniform("material.transform", transform);
  material->set_uniform("material.camera_view", camera->get_view_matrix());
  material->set_uniform("material.camera_projection", camera->get_projection_matrix());
  glDrawElements(GL_TRIANGLES, mesh->get_indices_size(), GL_UNSIGNED_INT, (void*) 0);
}




void Renderer::render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const Transform& transform) const {
  this->render(camera, mesh, material, transform.get_model_matrix());
}




void Renderer::render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Model>& model) const {
  for(auto& model_piece: model->get_model_pieces()) {
    this->render(camera, model_piece.mesh, model_piece.material, model_piece.transform);
  }
}




void Renderer::render(const std::shared_ptr<Camera>& camera, const std::shared_ptr<Entity>& entity) const {
  glm::mat4 model_matrix = entity->get_model_matrix();
  std::shared_ptr<Model> model = entity->get_model();
  for(auto& model_piece: model->get_model_pieces()) {
    glm::mat4 final_transform = model_matrix * model_piece.transform.get_model_matrix();
    this->render(camera, model_piece.mesh, model_piece.material, final_transform);
  }
}




void Renderer::render(const std::shared_ptr<Camera>& camera, const std::vector<std::shared_ptr<Entity>>& entities) const {
  for(auto& entity: entities) {
    this->render(camera, entity);
  }
}




void Renderer::set_view_port(Camera& camera, int w, int h) const {
  if(h == 0) {
    Logger::warn("renderer height is 0");
    return;
  }
  
  camera.set_aspect((float) w / (float) h);
}
