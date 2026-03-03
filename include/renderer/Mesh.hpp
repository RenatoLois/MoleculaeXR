#pragma once

#include <vector>
#include "renderer/Vertex.hpp"
#include "renderer/Textures.hpp"

class Mesh {
private:
  unsigned int VAO, VBO, EBO;

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  void setupMesh();
};
