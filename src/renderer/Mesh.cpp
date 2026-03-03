#include "renderer/Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures) 
{
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  this->setupMesh();
}

void Mesh::setupMesh() {
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
               &indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);	

  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

  glBindVertexArray(0);
}
