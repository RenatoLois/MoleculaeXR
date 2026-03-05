#include "renderer/Shader.hpp"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

GLchar* read_shader(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if(file == NULL) {
        fprintf(stderr, "failed to open shader file\n");
        return NULL;
    }

    if(fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        fprintf(stderr, "failed to seek to the end of shader file\n");
        return NULL;
    }

    long length = ftell(file);
    if(length < 0) {
        fclose(file);
        fprintf(stderr, "failed to get the file length\n");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    char* charBuffer = (char*) malloc(sizeof(GLchar) * (length + 1));
    if(charBuffer == NULL) {
        fclose(file);
        fprintf(stderr, "failed to allocate memory for the buffer\n");
        return NULL;
    }

    if(fread(charBuffer, sizeof(char), length, file) != length) {
        fclose(file);
        free(charBuffer);
        fprintf(stderr, "failed to copy file content to the buffer\n");
        return NULL;
    }

    fclose(file);

    charBuffer[length] = '\0';
    
    return charBuffer;
}




Shader::Shader(const char *vtxShaderFilepath, const char *frgShaderFilepath) {
  GLchar const* vtxShaderFileBuffer = read_shader(vtxShaderFilepath);
  if(!vtxShaderFileBuffer) {
    throw std::runtime_error("failed to open vertex shader file");
  }
  GLchar const* frgShaderFileBuffer = read_shader(frgShaderFilepath);
  if(!frgShaderFileBuffer) {
    free((void*) vtxShaderFileBuffer);
    throw std::runtime_error("failed to open fragment shader file");
  }
  GLuint vtxShaderId = glCreateShader(GL_VERTEX_SHADER);
  GLuint frgShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vtxShaderId, 1, &vtxShaderFileBuffer, NULL);
  glShaderSource(frgShaderId, 1, &frgShaderFileBuffer, NULL);
  glCompileShader(vtxShaderId);
  glCompileShader(frgShaderId);
  
  GLint compileSuccess;    
  GLint linkSuccess;    

  glGetShaderiv(vtxShaderId, GL_COMPILE_STATUS, &compileSuccess);
  if(compileSuccess == GL_FALSE) {
    GLchar logBuffer[512];
    glGetShaderInfoLog(vtxShaderId, 512, NULL, logBuffer);
    glDeleteShader(vtxShaderId);
    glDeleteShader(frgShaderId);
    free((void*) vtxShaderFileBuffer);
    free((void*) frgShaderFileBuffer);
    throw std::runtime_error(logBuffer);
  }

  glGetShaderiv(frgShaderId, GL_COMPILE_STATUS, &compileSuccess);
  if(compileSuccess == GL_FALSE) {
    GLchar logBuffer[512];
    glGetShaderInfoLog(frgShaderId, 512, NULL, logBuffer);
    glDeleteShader(vtxShaderId);
    glDeleteShader(frgShaderId);
    free((void*) vtxShaderFileBuffer);
    free((void*) frgShaderFileBuffer);
    throw std::runtime_error(logBuffer);
  }

  free((void*) vtxShaderFileBuffer);
  free((void*) frgShaderFileBuffer);

  this->programID = glCreateProgram();
  glAttachShader(this->programID, vtxShaderId);
  glAttachShader(this->programID, frgShaderId);
  glLinkProgram(this->programID);
  glDetachShader(this->programID, vtxShaderId);
  glDetachShader(this->programID, frgShaderId);

  glGetProgramiv(this->programID, GL_LINK_STATUS, &linkSuccess);
  if(linkSuccess == GL_FALSE) {
    GLchar logBuffer[512];
    glGetProgramInfoLog(this->programID, 512, NULL, logBuffer);
    glDeleteShader(vtxShaderId);
    glDeleteShader(frgShaderId);
    glDeleteProgram(this->programID);
    fprintf(stderr, "error compiling fragment shader: %s", logBuffer);
    throw std::runtime_error(logBuffer);
  }

  glDeleteShader(vtxShaderId);
  glDeleteShader(frgShaderId);
}




void Shader::setInt(const char* uniform_name, int value) {
  int location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found!\n";
  }
  glUniform1i(location, value);
}




void Shader::setFloat(const char* uniform_name, float value) {
  int location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found!\n";
  }
  glUniform1f(location, value);
}
