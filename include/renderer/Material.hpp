#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "renderer/Shader.hpp"


class Material {
  private:
    std::shared_ptr<Shader> shader;  
    std::shared_ptr<Shader> texture;

    glm::vec4 color = glm::vec4(1.0f);
        
  public:
    Material(std::shared_ptr<Shader> shader);
    void bind();

    void setColor(glm::vec4 color);
    void setColor(float r, float g, float b, float a);
};
