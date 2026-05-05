#include "core/Logger.hpp"

#include <cstdlib>
#include <iostream>


void Logger::info(const std::string_view message) {
  std::cout << "[INFO]: " << message << std::endl;
}




void Logger::warn(const std::string_view message) {
  std::cout << "[WARN]: " << message << std::endl;
}




void Logger::error(const std::string_view message) {
  std::cout << "[ERROR]: " << message << std::endl;
}




void Logger::fatal(const std::string_view message) {
  std::cout << "[Fatal]: " << message << std::endl;
  std::abort();
}
