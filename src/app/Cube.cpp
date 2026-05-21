#include "app/cube.hpp"
#include "engine/Vertex.hpp"
#include "engine/Mesh.hpp"
#include <vector>


Cube::Cube() {
  std::vector<Vertex> vertices = {
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1,  0,  0)), // direita  - cima   - trás   - face direita
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0,  1,  0)), // direita  - cima   - trás   - face cima
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0,  0, -1)), // direita  - cima   - trás   - face trás
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1,  0,  0)), // direita  - cima   - frente - face direita
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0,  1,  0)), // direita  - cima   - frente - face cima
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0,  0,  1)), // direita  - cima   - frente - face frente
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1,  0,  0)), // direita  - baixo  - trás   - face direita
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0, -1,  0)), // direita  - baixo  - trás   - face baixo
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0,  0, -1)), // direita  - baixo  - trás   - face trás
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1,  0,  0)), // direita  - baixo  - frente - face direita
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0, -1,  0)), // direita  - baixo  - frente - face baixo
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1,  0,  0)), // direita  - baixo  - frente - face direita
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1,  0,  0)), // esquerda - cima   - trás   - face esqueda
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0,  1,  0)), // esquerda - cima   - trás   - face cima
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0,  0, -1)), // esquerda - cima   - trás   - face trás
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1,  0,  0)), // esquerda - cima   - frente - face esquerda
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0,  1,  0)), // esquerda - cima   - frente - face cima
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0,  0,  1)), // esquerda - cima   - frente - face frente
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1,  0,  0)), // esquerda - baixo  - trás   - face esquerda
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0, -1,  0)), // esquerda - baixo  - trás   - face baixo
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0,  0, -1)), // esquerda - baixo  - trás   - face trás
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1,  0,  0)), // esquerda - baixo  - frente - face esquerda
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0, -1,  0)), // esquerda - baixo  - frente - face baixo
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0,  0,  1))  // esquerda - baixo  - frente - face frente
  }

  std::vector<unsigned int> indices = {

  }

  Mesh mesh(vertices)
}
