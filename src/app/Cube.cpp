#include "app/cube.hpp"
#include "engine/Camera.hpp"
#include "engine/Renderer.hpp"
#include "engine/Vertex.hpp"
#include "engine/Mesh.hpp"
#include "engine/Shader.hpp"
#include "engine/Material.hpp"
#include "engine/Model.hpp"
#include "engine/Transform.hpp"
#include "engine/Entity.hpp"
#include <memory>
#include <vector>


Cube::Cube() {
  std::vector<Vertex> cube_vertices = {
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0,  1,  0)), // 0  | direita  - cima   - frente - face cima
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0,  1,  0)), // 1  | direita  - cima   - trás   - face cima
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0,  1,  0)), // 2  | esquerda - cima   - frente - face cima
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0,  1,  0)), // 3  | esquerda - cima   - trás   - face cima
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0,  0,  1)), // 4  | direita  - cima   - frente - face frente
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0,  0,  1)), // 7  | direita  - baixo  - frente - face frente
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0,  0,  1)), // 6  | esquerda - cima   - frente - face frente
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0,  0,  1)), // 5  | esquerda - baixo  - frente - face frente
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0, -1,  0)), // 11 | direita  - baixo  - frente - face baixo
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0, -1,  0)), // 8  | direita  - baixo  - trás   - face baixo
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0, -1,  0)), // 9  | esquerda - baixo  - frente - face baixo
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0, -1,  0)), // 10 | esquerda - baixo  - trás   - face baixo
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0,  0, -1)), // 12 | direita  - cima   - trás   - face trás
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0,  0, -1)), // 15 | direita  - baixo  - trás   - face trás
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0,  0, -1)), // 14 | esquerda - cima   - trás   - face trás
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0,  0, -1)), // 13 | esquerda - baixo  - trás   - face trás
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1,  0,  0)), // 16 | direita  - cima   - frente - face direita
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1,  0,  0)), // 17 | direita  - cima   - trás   - face direita
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1,  0,  0)), // 19 | direita  - baixo  - frente - face direita
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1,  0,  0)), // 18 | direita  - baixo  - trás   - face direita
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1,  0,  0)), // 21 | esquerda - cima   - frente - face esquerda
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1,  0,  0)), // 20 | esquerda - cima   - trás   - face esquerda
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1,  0,  0)), // 23 | esquerda - baixo  - frente - face esquerda
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1,  0,  0))  // 22 | esquerda - baixo  - trás   - face esquerda
  };

  std::vector<unsigned int> cube_indices = {
     0,  1,  2,
     1,  2,  3,

     4,  5,  6,
     5,  6,  7,

     8,  9, 10,
     9, 10, 11,

    12, 13, 14,
    13, 14, 15,

    16, 17, 18,
    17, 18, 19,

    20, 21, 22,
    21, 22, 23
  };

  Transform indentity_transform(
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
  );

  auto cube_mesh = std::make_shared<Mesh>(cube_vertices, cube_indices);

  auto cube_shader = std::make_shared<Shader>("res/shaders/cube.vert", "res/shaders/cube.frag");

  auto cube_material = std::make_shared<Material>(
    cube_shader,
    glm::vec4(0.5f, 0.5f, 0.9f, 1.0f)
  );

  auto cube_model = std::make_shared<Model>(
    std::vector<std::shared_ptr<Mesh>>{cube_mesh},
    std::vector<std::shared_ptr<Material>>{cube_material},
    std::vector<Transform>{indentity_transform}
  );

  auto cube_entity = std::make_shared<Entity>(cube_model, indentity_transform);

  this->cube_entity = cube_entity;
}




void Cube::render(const Renderer& render, const std::shared_ptr<Camera>& camera) {
  render.render(camera, this->cube_entity);
}
