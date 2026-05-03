#include "engine/Model.hpp"


Model::Model(const std::vector<ModelPiece>& model_pieces) {
  this->model_pieces = model_pieces;
}

Model::Model(
  const std::vector<std::shared_ptr<Mesh>>& meshs,
  const std::vector<std::shared_ptr<Material>>& materials,
  const std::vector<Transform>& transform
) {
  for(int i=0; i < meshs.size(); i++) {
    this->model_pieces.push_back({meshs[i], materials[i], transform[i]});
  }
}
