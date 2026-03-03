#include "core/Vision.hpp"
#include <opencv2/videoio.hpp>
#include <stdexcept>
#include <string>

Vision::Vision(int cameraID) {
  this->cameraID = cameraID;
}




void Vision::open() {
  if( this->stream.isOpened() )
    throw std::runtime_error("camera already opened");
  if( !this->stream.open(this->cameraID) ) {
/*
    if( this->stream.isOpened() )
*/
      this->stream.release();
    throw std::runtime_error( "failed to open camera with id " + std::to_string(this->cameraID) );
  }
}




void Vision::close() {
/*
  if( !this->stream.isOpened() )
    throw std::runtime_error("camera already closed");
  else this->stream.release();
*/ 
  this->stream.release();
}



// assuming the camera is opened
bool Vision::read() {
  return this->stream.read(this->framebuffer);
}




cv::Mat Vision::getFramebuffer() {
  return this->framebuffer;
}

