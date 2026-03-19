#pragma once

#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/opencv.hpp>

class Vision {
private:
  int cameraID;                                             // id da camera
  cv::Mat framebuffer;                                      // buffer que armazenara o frame da camera
  cv::VideoCapture stream;                                  // stream de video
  cv::aruco::Dictionary aruco_dict;                         // conjunto definido de marcadores
  cv::aruco::DetectorParameters aruco_params;               // opcoes de configuracao

public:
  // vetor com os cantos de cada marker encontrado
  std::vector< std::vector<cv::Point2f> > tags_corners;
  std::vector<int> tag_IDs;

  // construtor, usa a camera com id igual a "cameraID", e procura pelo
  // tipo de marcador passado no parametro "marker_type"
  Vision(int cameraID, cv::aruco::PredefinedDictionaryType marker_type);
  
  // tenta abrir a camera
  void open();
  // fecha a camera caso esteja aberta
  void close();
  
  // escreve a imagem da camera em this.framebuffer
  bool read();

  // retornar o framebuffer
  cv::Mat getFramebuffer();

  // escreve os dados dos marcadores nos seguintes atributos: this.tags_corners, this.tag_IDs
  bool detectMarkers();
};
