#include "engine/Mesh.hpp"
#include <cstddef>
#include <glad/glad.h>


Mesh::Mesh(const std::vector<Vertex>& vertices,
           const std::vector<unsigned int>& indices)
{
  this->vertices = vertices;
  this->indices = indices;

  this->setup_mesh();
}




// nao precisa verificar se existe,
// caso nao existir o opengl nao faz
// nada, entao basta tentar excluir
Mesh::~Mesh() {
  glDeleteVertexArrays(1, & this->VAO);
  glDeleteBuffers(1, & this->VBO);
  glDeleteBuffers(1, & this->EBO);
}
 



size_t Mesh::get_indices_size() const {
  return this->indices.size();
}




void Mesh::setup_mesh() {
  glGenVertexArrays(1, & this->VAO);
  glGenBuffers(1, & this->VBO);
    
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);  

  if(indices.size() != 0) {
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 this->indices.size() * sizeof(unsigned int), 
                 this->indices.data(), GL_STATIC_DRAW);
  } else {
    this->EBO = 0;
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);	

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(1);	

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
  glEnableVertexAttribArray(2);	

  glBindVertexArray(0);
}




void Mesh::bind() const {
  glBindVertexArray(this->VAO);
}
