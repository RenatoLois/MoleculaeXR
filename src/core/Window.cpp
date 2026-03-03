#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "core/Window.hpp"

Window::Window(int width, int height, const std::string& title) {
  this->width  = width;
  this->height = height;
  this->title  = title;
}

Window::~Window() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
#endif
}




int Window::initBackend() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)


#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)

  if( !glfwInit() ) {
    std::cerr << "failed to initialize GLFW.\n";
    return 1;
  }
  return 0;

#endif
}




int Window::init() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)

#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

  this->window = glfwCreateWindow(
    this->width, 
    this->height, 
    this->title.c_str(), 
    NULL, 
    NULL
  );
  
  if( !this->window ) {
    glfwTerminate();
    std::cerr << "failed to create window.\n";
    return 1;
  }

  glfwMakeContextCurrent(this->window);
    
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  return 0;

#endif
}




int Window::destroy() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
  
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)

  if(this->window) {
    glfwDestroyWindow(this->window);
    this->window = nullptr;
  }
  return 0;

#endif
}




bool Window::isVisible() const {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  return glfwGetWindowAttrib(this->window, GLFW_VISIBLE);
#endif
}

void Window::setVisible(bool visible) {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  visible ? glfwShowWindow(this->window) : glfwHideWindow(this->window);
#endif
}




void Window::pollEvents() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  glfwPollEvents();
#endif
}




#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
SDL_window* Window::getWindow() const {
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
GLFWwindow* Window::getWindow() const {
#endif
  return this->window;
}
