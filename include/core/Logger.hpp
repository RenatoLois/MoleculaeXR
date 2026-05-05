#pragma once

#include <string_view>


class Logger {
public:
  Logger() = default;
  static void info(const std::string_view message);
  static void warn(const std::string_view message);
  static void error(const std::string_view message);
  static void fatal(const std::string_view message);
};
