#pragma once

#include <vector>
#include "engine/Vertex.hpp"

class Mesh {
private:
  unsigned int VAO, VBO, EBO;

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  // construtor sem textura
  Mesh(std::vector<Vertex>& vertices,
       std::vector<unsigned int>& indices);

  // destrutor
  ~Mesh();

  // inicializa o mesh
  void setupMesh();

  // vincula o mesh
  void bind() const;
};
