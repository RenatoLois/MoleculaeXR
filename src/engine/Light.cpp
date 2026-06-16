#include "engine/Light.hpp"


Light::Light() {
    this->translation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->color = glm::vec3(1.0f, 1.0f, 1.0f);
    this->intensity = 1.0f;
}




Light::Light(glm::vec3 color, float intensity) {
    this->translation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->color = color;
    this->intensity = intensity;
}




void Light::translate(const glm::vec3& translation) {
    this->translation += translation;
}




void Light::translate(float x, float y, float z) {
    this->translation += glm::vec3(x, y, z);
}




void Light::set_translation(const glm::vec3& translation) {
    this->translation = translation;
}




void Light::set_translation(float x, float y, float z) {
    this->translation = glm::vec3(x, y, z);
}




void Light::set_color(const glm::vec3& color) {
    this->color = color;
}




void Light::set_color(float r, float g, float b) {
    this->color = glm::vec3(r, g, b);
}




void Light::set_intensity(float intensity) {
    this->intensity = intensity;
}




float Light::get_intensity() const {
    return this->intensity;
}




glm::vec3 Light::get_color() const {
    return this->color;
}




glm::vec3 Light::get_translation_matrix() const {
    return this->translation;
}
