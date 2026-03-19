#include "core/Vision.hpp"
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/objdetect/aruco_dictionary.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/aruco.hpp>
#include <stdexcept>
#include <string>

Vision::Vision(int cameraID, cv::aruco::PredefinedDictionaryType marker_type) {
  this->cameraID = cameraID;
  this->aruco_dict   = cv::aruco::getPredefinedDictionary(marker_type);
  this->aruco_params = cv::aruco::DetectorParameters();
  aruco_params.markerBorderBits = 1;
}




// open camera with id = this->id
void Vision::open() {
  if( this->stream.isOpened() )
    throw std::runtime_error("camera already opened");
  if( !this->stream.open(this->cameraID, cv::CAP_V4L2) ) { // change this on mobile!
/*
    if( this->stream.isOpened() )
*/
      this->stream.release();
    throw std::runtime_error( "failed to open camera with id " + std::to_string(this->cameraID) );
  }

  this->stream.set(cv::CAP_PROP_BUFFERSIZE, 1);
}




// close opened camera
void Vision::close() {
/*
  if( !this->stream.isOpened() )
    throw std::runtime_error("camera already closed");
  else this->stream.release();
*/ 
  this->stream.release();
}



// sends an image from the camera to this->framebuffer
// assuming the camera is opened
bool Vision::read() {
  return this->stream.read(this->framebuffer);
}




// get this->framebuffer
cv::Mat Vision::getFramebuffer() {
  return this->framebuffer;
}




// detect april tags in framebuffer image
// // returns false if no tag is found, otherwise returns true
bool Vision::detectMarkers() {
  cv::aruco::detectMarkers(this->framebuffer,  cv::makePtr<cv::aruco::Dictionary>(aruco_dict), this->tags_corners, this->tag_IDs, cv::makePtr<cv::aruco::DetectorParameters>(aruco_params));
  return !tag_IDs.empty();
}
