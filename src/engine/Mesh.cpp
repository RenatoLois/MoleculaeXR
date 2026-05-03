#include "engine/Mesh.hpp"
#include <cstddef>
#include <glad/glad.h>


Mesh::Mesh(std::vector<Vertex>& vertices,
           std::vector<unsigned int>& indices)
{
  this->vertices = vertices;
  this->indices = indices;
  
  this->setupMesh();
}




// nao precisa verificar se existe,
// caso nao existir o opengl nao faz
// nada, entao basta tentar excluir
Mesh::~Mesh() {
  glDeleteVertexArrays(1, & this->VAO);
  glDeleteBuffers(1, & this->VBO);
  glDeleteBuffers(1, & this->EBO);
}
 



void Mesh::setupMesh() {
  glGenVertexArrays(1, & this->VAO);
  glGenBuffers(1, & this->VBO);
  glGenBuffers(1, & this->EBO);
    
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), & this->vertices[0], GL_STATIC_DRAW);  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               this->indices.size() * sizeof(unsigned int), 
               & this->indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);	

  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

  glBindVertexArray(0);
}




void Mesh::bind() const {
  glBindVertexArray(this->VAO);
}

