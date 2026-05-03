#include "engine/Texture.hpp"
#include <glad/glad.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>
#include <stdexcept>
#include <string>


GLenum texture_units[32] = {
  GL_TEXTURE0,
  GL_TEXTURE1,
  GL_TEXTURE2,
  GL_TEXTURE3,
  GL_TEXTURE4,
  GL_TEXTURE5,
  GL_TEXTURE6,
  GL_TEXTURE7,
  GL_TEXTURE8,
  GL_TEXTURE9,
  GL_TEXTURE10,
  GL_TEXTURE11,
  GL_TEXTURE12,
  GL_TEXTURE13,
  GL_TEXTURE14,
  GL_TEXTURE15,
  GL_TEXTURE16,
  GL_TEXTURE17,
  GL_TEXTURE18,
  GL_TEXTURE19,
  GL_TEXTURE20,
  GL_TEXTURE21,
  GL_TEXTURE22,
  GL_TEXTURE23,
  GL_TEXTURE24,
  GL_TEXTURE25,
  GL_TEXTURE26,
  GL_TEXTURE27,
  GL_TEXTURE28,
  GL_TEXTURE29,
  GL_TEXTURE30,
  GL_TEXTURE31,
};


int nearest_power_of_2(int n) {
  if(n <= 1) return 1;
  int power = 1;
  int last_power = power;
  while(power < n) {
    last_power = power;
    power <<= 1;
  }
  return 
    (power - n) < (n - last_power) ? 
    power : last_power;
}




Texture::Texture(std::string& texture_filepath, bool to_power_of_2) {
  glGenTextures(1, & this->id);
  this->load(texture_filepath, to_power_of_2);
}




Texture::~Texture() {
  glDeleteTextures(1, &this->id);
}




void Texture::load(const cv::Mat& frame, bool to_power_of_2) {
  // deletando textura caso ja exista
  glDeleteTextures(1, &(this->id));

  glBindTexture(GL_TEXTURE_2D, this->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  const cv::Mat *final_frame = &frame;
  cv::Mat resized;

  if(to_power_of_2) {
    if( (frame.cols > 0 && ( (frame.cols-1) & frame.cols ) == 0) &&
        (frame.rows > 0 && ( (frame.rows-1) & frame.rows ) == 0) 
    ) {
      to_power_of_2 = false;
    } else {
      int newWidth = nearest_power_of_2(frame.cols);
      int newHeight = nearest_power_of_2(frame.rows);

      cv::resize(frame, resized, cv::Size(newWidth, newHeight));
      final_frame = &resized;
    }
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGB,
    final_frame->cols,
    final_frame->rows,
    0,
    GL_BGR,
    GL_UNSIGNED_BYTE,
    final_frame->data
  );
}




void Texture::load(std::string& texture_filepath, bool to_power_of_2) {
  // deletando textura caso ja exista
  glDeleteTextures(1, &(this->id));

  glBindTexture(GL_TEXTURE_2D, this->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *databuffer = stbi_load(texture_filepath.c_str(), &width, &height, &channels, 0);
  if( !databuffer ) {
    throw std::runtime_error("failed to load texture " + texture_filepath);
    return;
  }
  
  if(to_power_of_2) {
    if( (width  > 0 && ( (width-1)  & width )  == 0) &&
        (height > 0 && ( (height-1) & height ) == 0) 
    ) {
      to_power_of_2 = false;
    } else {
      int newWidth = nearest_power_of_2(width);
      int newHeight = nearest_power_of_2(height);

      unsigned char *resized;

      resized = (unsigned char*) malloc(newWidth * newHeight * channels);
      stbir_resize_uint8(databuffer, width, height, 0, resized, newWidth, newHeight, 0, channels);
      width = newWidth;
      height = newHeight;
      stbi_image_free(databuffer);
      databuffer = resized;
    }
  }

  GLenum format;

  if (channels == 1)
    format = GL_RED;
  else if (channels == 3)
    format = GL_RGB;
  else if (channels == 4)
    format = GL_RGBA;
  else {
    if(to_power_of_2) 
      free(databuffer);
    else 
      stbi_image_free(databuffer);
    throw std::runtime_error("unrecognized texture format");
    return;
  }

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    format,
    width,
    height,
    0,
    format,
    GL_UNSIGNED_BYTE,
    databuffer
  );

  glGenerateMipmap(GL_TEXTURE_2D);

  if(to_power_of_2) 
    free(databuffer);
  else
    stbi_image_free(databuffer);

}




void Texture::update(const cv::Mat& frame, bool to_power_of_2) {
  const cv::Mat *final_frame = &frame;
  cv::Mat resized;

  glBindTexture(GL_TEXTURE_2D, this->id);
  if(to_power_of_2) {
    if( (frame.cols > 0 && ( (frame.cols-1) & frame.cols ) == 0) &&
        (frame.rows > 0 && ( (frame.rows-1) & frame.rows ) == 0)
    ) {
      to_power_of_2 = false;
    } else {
      int newWidth = nearest_power_of_2(frame.cols);
      int newHeight = nearest_power_of_2(frame.rows);

      cv::resize(frame, resized, cv::Size(newWidth, newHeight));
      final_frame = &resized;
    }
  }
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, final_frame->cols, final_frame->rows, GL_BGR, GL_UNSIGNED_BYTE, final_frame->data);
}




// assuming num < 32
void Texture::bind(int num) {
  glActiveTexture( texture_units[num] );
  glBindTexture(GL_TEXTURE_2D, this->id);
}
