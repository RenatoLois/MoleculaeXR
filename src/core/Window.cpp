#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "core/Window.hpp"




// function to resize the glViewport if the window is resized
void window_resize_callback(GLFWwindow* window, int width, int height) {
#if defined (USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
    float aspectRatio = 1.0f / 1.0f;
    int viewportWidth = width;
    int viewportHeight = height;
    if (width > (height * aspectRatio)) {
        viewportWidth = (height * aspectRatio);
    } else {
        viewportHeight = width / aspectRatio;
    }

    glViewport( ( (width / 2) - (viewportWidth / 2) ),
                ( (height / 2) - (viewportHeight / 2) ),
                viewportWidth, 
                viewportHeight 
    );
}
#endif




// window constructor
Window::Window(int width, int height, const std::string& title) {
  this->width  = width;
  this->height = height;
  this->title  = title;
}




// window destructor
Window::~Window() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
#endif
}




// start gflw or sdl backend (depends on which one you use)
int Window::init_backend() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)


#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)

  if( !glfwInit() ) {
    std::cerr << "failed to initialize GLFW.\n";
    return 1;
  }
  return 0;

#endif
}




// initialize window properties
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
    
  if( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) ) {
    throw std::runtime_error("failed to initialize glad");
    return 1;
  }

  glfwSetFramebufferSizeCallback(window, window_resize_callback);

  return 0;

#endif
}




// destroy window
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




// return if window is visible
// assuming this->window != NULL
bool Window::is_visible() const {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  return glfwGetWindowAttrib(this->window, GLFW_VISIBLE);
#endif
}




// assuming this->window != NULL
void Window::set_visible(bool visible) {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  visible ? glfwShowWindow(this->window) : glfwHideWindow(this->window);
#endif
}




void Window::poll_events() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  glfwPollEvents();
#endif
}




// assuming this->window != NULL
void Window::swap_buffers() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  glfwSwapBuffers(this->window);
#endif
}




#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
SDL_window* Window::get_window() const {
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
GLFWwindow* Window::get_window() const {
#endif
  return this->window;
}




void Window::init_delta_time() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  this->last_time = this->get_current_time();
  this->current_time = this->last_time;
#endif
}




double Window::get_delta_time() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  this->current_time = this->get_current_time();
  double delta_time = this->current_time - this->last_time;
  this->last_time = this->current_time;
  return delta_time;
#endif
}




bool Window::should_close() {
#if defined(USE_WINDOW_BACKEND_LIBRARY_SDL)
#elif defined(USE_WINDOW_BACKEND_LIBRARY_GLFW)
  return glfwWindowShouldClose(this->window);
#endif
}
