#pragma once

#include <vector>
#include "engine/Vertex.hpp"
#include "engine/Textures.hpp"
#include "engine/Shader.hpp"

class Mesh {
private:
  unsigned int VAO, VBO, EBO;

public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // construtor com textura
  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures);

  // construtor sem textura
  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices);


  // destrutor
  ~Mesh();

  // inicializa o mesh
  void setupMesh();

  // desenha o mesh
  void draw(Shader& shader, glm::mat4 model);
};
