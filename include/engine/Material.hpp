#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "engine/Shader.hpp"
#include "engine/Textures.hpp"


class Material {
  private:
    std::shared_ptr<Shader> shader;  
    std::shared_ptr<Texture> texture_diffuse;
    std::shared_ptr<Texture> texture_specular;
    // std::shared_ptr<Texture> texture_ambient;
    float shininess;

    glm::vec4 color = glm::vec4(1.0f);
        
  public:
    Material(std::shared_ptr<Shader> shader);

    void bind();

    void set_color(glm::vec4 color);
    void set_color(float r, float g, float b, float a);

    void set_diffuse(std::shared_ptr<Texture> tex);
    void set_specular(std::shared_ptr<Texture> tex);
    // void set_ambient(std::shared_ptr<Texture> tex);
};
