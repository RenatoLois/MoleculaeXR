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




Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned int> indices)
: Mesh::Mesh(vertices, indices, {}) { // chamando construtor com array de shaders vazio

}




// nao precisa verificar se existe,
// caso nao existir o opengl nao faz
// nada, entao basta tentar excluir
Mesh::~Mesh() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}




void Mesh::setupMesh() {
  glGenVertexArrays(1, & this->VAO);
  glGenBuffers(1, & this->VBO);
  glGenBuffers(1, & this->EBO);
  
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), & this->vertices[0], GL_STATIC_DRAW);  

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
               & indices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(0);	

  glEnableVertexAttribArray(1);	
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);	
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

  glBindVertexArray(0);
}




/*
 *  Inspired by https://learnopengl.com/Model-Loading/Mesh
 */
void Mesh::draw(Shader& shader, glm::mat4 model) {
  if(indices.empty()) {
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    return;
  }

  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  for(unsigned int i = 0; i < this->textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = this->textures[i].type;
    if(name == "texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if(name == "texture_specular")
      number = std::to_string(specularNr++);

    shader.setInt(( std::string("material_" + name + number) ).c_str(), i);
    glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
  }
  glActiveTexture(GL_TEXTURE0);

  glBindVertexArray(this->VAO);

  shader.setMat4("model_matrix", model);

  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
