#include "engine/Model.hpp"
#include "core/Logger.hpp"


Model::Model(const std::vector<ModelPiece>& model_pieces) {
  this->model_pieces = model_pieces;
}

Model::Model(
  const std::vector<std::shared_ptr<Mesh>>& meshs,
  const std::vector<std::shared_ptr<Material>>& materials,
  const std::vector<Transform>& transform
) {
  if(! (meshs.size() != materials.size()) && ! (meshs.size() != transform.size()) ) {
    Logger::fatal("Resource size mismatch: Meshes, Materials, and Transforms must have the same count.");
  }
  
  for(int i=0; i < meshs.size(); i++) {
    this->model_pieces.push_back({meshs[i], materials[i], transform[i]});
  }
}

const std::vector<ModelPiece>& Model::get_model_pieces() const {
  return this->model_pieces;
}
