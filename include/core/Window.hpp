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
  std::string title;

// window attribute
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  SDL_Window* window;
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  GLFWwindow* window;
#endif


public:
  Window(int width, int height, const std::string& title);
  ~Window();

#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  SDL_window* getWindow() const;
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  GLFWwindow* getWindow() const;
#endif

  int initBackend();
  int init();
  int destroy();

  bool isVisible() const;
  void setVisible(bool visbible);

  void pollEvents();  
  void swapBuffers();
};
