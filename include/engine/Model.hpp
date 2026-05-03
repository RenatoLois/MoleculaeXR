#pragma once

#include <vector>
#include <memory>
#include "engine/ModelPiece.hpp"
#include "engine/Transform.hpp"


class Model {
private:
  std::vector<ModelPiece> model_pieces;

public:
  Model() = default;

  Model(const std::vector<ModelPiece>& model_pieces);

  Model(const std::vector<std::shared_ptr<Mesh>>& meshs,
        const std::vector<std::shared_ptr<Material>>& materials,
        const std::vector<Transform>& transforms);
};
