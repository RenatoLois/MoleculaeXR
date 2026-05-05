#pragma once

#include <cstddef>
#include <vector>
#include "engine/Vertex.hpp"

class Mesh {
private:
  unsigned int VAO, VBO, EBO;

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // construtor sem indices
  Mesh(const std::vector<Vertex>& vertices);

  // construtor com indices
  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices);

  // destrutor
  ~Mesh();

  size_t get_indices_size() const;

  // inicializa o mesh
  void setup_mesh();

  // vincula o mesh
  void bind() const;
};
