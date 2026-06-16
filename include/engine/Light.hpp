#pragma once
#include <glm/glm.hpp>

class Light {
private:
    glm::vec3 translation;
    glm::vec3 color;
    float intensity;

public:
    Light();
    Light(glm::vec3 color, float intensity = 1.0f);
    
    void translate(const glm::vec3& translation);
    void translate(float x, float y, float z);
    void set_translation(const glm::vec3& translation);
    void set_translation(float x, float y, float z);
    void set_color(const glm::vec3& color);
    void set_color(float r, float g, float b);
    void set_intensity(float intensity);
    
    glm::vec3 get_translation_matrix() const;
    glm::vec3 get_color() const;
    float get_intensity() const;   
};
