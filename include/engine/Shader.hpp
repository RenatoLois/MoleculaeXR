#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


class Shader {
public:
  GLuint programID;  // id do programa shader

  // construtor
  Shader(const char *vtxShaderFilepath, const char *frgShaderFilepath);

  // destrutor (libera memoria do shader)
  ~Shader();

  // envia um "uniform" do tipo "int" para o shader
  void set_uniform(const char* uniform_name, const int value);
  // envia um "uniform" do tipo "float" para o shader
  void set_uniform(const char* uniform_name, const float value);
  // envia um "uniform" do tipo "mat4" para o shader
  void set_uniform(const char* uniform_name, const glm::mat4& matrix);
  // envia um "uniform" do tipo "vec3" para o shader
  void set_uniform(const char* uniform_name, const glm::vec3& vector);
  // envia um "uniform" do tipo "vec4" para o shader
  void set_uniform(const char* uniform_name, const glm::vec4& vector);

  inline void use() {
    glUseProgram(this->programID);
  }
};
