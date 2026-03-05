#pragma once

#include <string>
#include <opencv2/core/mat.hpp>

class Texture {
public:
  unsigned int id;
  std::string type;

  Texture(std::string type);
  Texture(std::string type, std:: string texture_filepath);
  void load(std::string texture_filepath, bool to_power_of_2);
  void load(const cv::Mat& frame, bool to_power_of_2);
  void bind();
  void unbind();
  void update(const cv::Mat& frame, bool to_power_of_2);
};
