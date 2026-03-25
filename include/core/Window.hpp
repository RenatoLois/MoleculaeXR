#pragma once

#define USE_WINDOW_BACKEND_LIBRARY_GLFW
//#define USE_WINDOW_BACKEND_LIBRARY_SDL



// including window backend library
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  #include <SDL2/SDL.h>
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  #define GLFW_INCLUDE_NONE
  #include <GLFW/glfw3.h>
#endif


#include <string>


class Window{
protected:
  int width;
  int height;
  double last_time, current_time;
  std::string title;

// window attribute
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  SDL_Window* window;
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  GLFWwindow* window;
#endif


public:
  // construtor: constroi a janela com largura, altura e titulo definidos
  Window(int width, int height, const std::string& title);

  // destrutor: destroi a janela (provavelmente so precisa chamar this.destroy())
  ~Window();

  // retorna a instancia da janela
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  SDL_window* get_window() const;
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  GLFWwindow* get_window() const;
#endif

  // prepara a janela internamente para uso
  int init_backend();

  // inicializa a instancia da janela
  int init();

  // termina e libera recursos da janela
  int destroy();

  // retorna "true" se a janela esta visive, "false" caso contrario
  bool is_visible() const;

  // define se a janela deve ser visivel ou nao
  void set_visible(bool visbible);

  // verifica se houve algum evento na janela (clique, digitacao, mouse, fechar, etc)
  void poll_events();  

  // atualiza o buffer de video
  void swap_buffers();

  // funcao que retorna o tempo (para usar em delta-time e outros afins)
  double get_current_time();
  void init_delta_time();
  double get_delta_time();

  // verifica se a janela foi pedida para ser fechada
  bool should_close();
};
