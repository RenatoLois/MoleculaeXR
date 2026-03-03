#pragma once

#include <opencv2/opencv.hpp>

class Vision {
private:
  int cameraID;
  cv::Mat framebuffer;
  cv::VideoCapture stream;

public:
  Vision(int camID);
  
  void open();
  void close();
  
  bool read();
  cv::Mat getFramebuffer();
};
