#include "engine/Shader.hpp"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>


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
    std::string error = std::string(vtxShaderFilepath) + "\nfailed to open vertex shader file";
    throw std::runtime_error(error);

  }
  GLchar const* frgShaderFileBuffer = read_shader(frgShaderFilepath);
  if(!frgShaderFileBuffer) {
    free((void*) vtxShaderFileBuffer);
    std::string error = std::string(frgShaderFilepath) + "\nfailed to open fragment shader file";
    throw std::runtime_error(error);
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
    std::string error = std::string(vtxShaderFilepath) + ":\n" + std::string(logBuffer);
    throw std::runtime_error(error);
  }

  glGetShaderiv(frgShaderId, GL_COMPILE_STATUS, &compileSuccess);
  if(compileSuccess == GL_FALSE) {
    GLchar logBuffer[512];
    glGetShaderInfoLog(frgShaderId, 512, NULL, logBuffer);
    glDeleteShader(vtxShaderId);
    glDeleteShader(frgShaderId);
    free((void*) vtxShaderFileBuffer);
    free((void*) frgShaderFileBuffer);
    std::string error = std::string(frgShaderFilepath) + ":\n" + std::string(logBuffer);
    throw std::runtime_error(error);
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
    std::string error = std::string("Program Link Error: \n") + std::string(logBuffer);
    throw std::runtime_error(error);
  }

  glDeleteShader(vtxShaderId);
  glDeleteShader(frgShaderId);
}




Shader::~Shader() {
  glDeleteProgram(this->programID);
}




void Shader::set_uniform(const char* uniform_name, const int value) {
  // glUseProgram(this->programID);
  int location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found in program with id = " << this->programID << "\n";
    return;
  }
  // OpenGL ignores this if location == -1
  glUniform1i(location, value);
}




void Shader::set_uniform(const char* uniform_name, const float value) {
  // glUseProgram(this->programID);
  int location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found in program with id = " << this->programID << "\n";
    return;
  }
  // OpenGL ignores this if location == -1
  glUniform1f(location, value);
}




void Shader::set_uniform(const char* uniform_name, const glm::mat4& matrix) {
  // glUseProgram(this->programID);
  GLuint location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found in program with id = " << this->programID << "\n";
    return;
  }
  // OpenGL ignores this if location == -1
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); 
}




void Shader::set_uniform(const char* uniform_name, const glm::vec3& vector) {
  // glUseProgram(this->programID);
  GLuint location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found in program with id = " << this->programID << "\n";
    return;
  }
  // OpenGL ignores this if location == -1
  glUniform3fv(location, 1, glm::value_ptr(vector)); 
}




void Shader::set_uniform(const char* uniform_name, const glm::vec4& vector) {
  // glUseProgram(this->programID);
  GLuint location = glGetUniformLocation(this->programID, uniform_name);
  if(location == -1) {
    std::cerr << "Warning: uniform '" << uniform_name << "' not found in program with id = " << this->programID << "\n";
    return;
  }
  // OpenGL ignores this if location == -1
  glUniform4fv(location, 1, glm::value_ptr(vector)); 
}
