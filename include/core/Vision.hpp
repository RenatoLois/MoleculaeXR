#pragma once

#include "engine/Camera.hpp"
#include "engine/Transform.hpp"
#include <opencv2/objdetect/aruco_detector.hpp>
#include <opencv2/opencv.hpp>

class Vision {
private:
  int cameraID;                                             // id da camera
  cv::Mat framebuffer;                                      // buffer que armazenara o frame da camera
  cv::Mat gray_frame;                                       // buffer em escalas de cinza para otimizar detecção
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
  
  // define os parametros aruco
  void set_aruco_params(const cv::aruco::DetectorParameters& aruco_params);

  // obtém os parametros aruco
  cv::aruco::DetectorParameters get_aruco_params() const;

  // tenta abrir a camera
  void open();
  // fecha a camera caso esteja aberta
  void close();
  
  // escreve a imagem da camera em this.framebuffer
  bool read();

  // retornar o framebuffer
  cv::Mat get_framebuffer();

  // escreve os dados dos marcadores nos seguintes atributos: this.tags_corners, this.tag_IDs
  bool detect_markers();

  // obtem a Transform de uma tag qualquer a partir de seus cantos
  Transform get_marker_transform (
    const std::vector<cv::Point2f>& tag_corners,
    const Camera& camera,
    float image_width,
    float image_height,
    float tag_size
  );

  // pega um frame da camera, atualiza a textura e desenha um retangulo com essa textura
  void update_camera_background(float aspect_ratio);
};
