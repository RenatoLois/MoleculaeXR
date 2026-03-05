#pragma once

#include <glad/glad.h>

class Shader {
public:
  GLuint programID;
  Shader(const char *vtxShaderFilepath, const char *frgShaderFilepath);
  void setInt(const char* uniform_name, int value);
  void setFloat(const char* uniform_name, float value);
};
