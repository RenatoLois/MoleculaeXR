#pragma once

#include <glad/glad.h>

class Shader {
  GLuint programID;
  Shader(const char *vtxShaderFilepath, const char *frgShaderFilepath);
};
