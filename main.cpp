#include "core/Window.hpp"
#include "core/Vision.hpp"

#include "engine/Camera.hpp"        // pode remover se não for mais usada
#include "engine/Texture.hpp"
#include "engine/Vertex.hpp"
#include "engine/Mesh.hpp"
#include "engine/Shader.hpp"
#include "engine/Material.hpp"      // incluí Material, que estava faltando
// #include "engine/Renderer.hpp"   // REMOVIDO

#include <memory>
#include <opencv2/objdetect/aruco_dictionary.hpp>

void initialize(Window& window, Vision& vision);
void update_camera_background(Vision& vision);

int main(int argc, char** argv) {
    Window window(600, 600, "MoleculaeXR");
    Vision vision(0, cv::aruco::DICT_APRILTAG_36h11);

    initialize(window, vision);

    double delta_time;
    while (!window.should_close()) {
        window.poll_events();
        delta_time = window.get_delta_time();
        update_camera_background(vision);
        window.swap_buffers();
    }
}

void initialize(Window& window, Vision& vision) {
    vision.open();
    window.init_backend();
    window.init();
    window.set_visible(true);
    glViewport(0, 0, window.get_width(), window.get_height());
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void update_camera_background(Vision& vision) {
    static bool first_time = true;

    // vértices do quad em NDC (z = 0.0, que fica no meio do volume de clipping)
    // coordenadas de textura invertidas (como você já tinha)
    static std::vector<Vertex> corner_vertices = {
        Vertex(glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 0.0f)), // top-left
        Vertex(glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 0.0f)), // top-right
        Vertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(1.0f, 1.0f)), // bottom-left
        Vertex(glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f, 1.0f))  // bottom-right
    };

    static std::vector<unsigned int> corner_indices = {
        0, 1, 2,
        1, 2, 3
    };

    static auto texture_background = std::make_shared<Texture>();
    static auto mesh_bg = std::make_shared<Mesh>(corner_vertices, corner_indices);
    static auto shader_bg = std::make_shared<Shader>(
        "res/shaders/vertex_shader_bg.glsl",
        "res/shaders/fragment_shader_bg.glsl"
    );
    static auto material_bg = std::make_shared<Material>(shader_bg);

    vision.read();   // captura o frame da câmera

    if (first_time) {
        texture_background->load(vision.get_framebuffer(), true);
        material_bg->set_diffuse(texture_background);
        material_bg->set_use_texture(true);
        first_time = false;
    } else {
        texture_background->update(vision.get_framebuffer(), true);
    }

    // limpa a tela antes de desenhar o fundo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // desabilita o teste de profundidade enquanto desenha o fundo
    // (opcional, mas garante que nada fique na frente do quad)
    glDisable(GL_DEPTH_TEST);

    // ativa o shader e aplica o material (liga a textura)
    shader_bg->use();
    material_bg->apply();

    // desenha o quad
    mesh_bg->bind();
    glDrawElements(GL_TRIANGLES, mesh_bg->get_indices_size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // reabilita o depth test se precisar desenhar outros objetos depois
    glEnable(GL_DEPTH_TEST);
}
