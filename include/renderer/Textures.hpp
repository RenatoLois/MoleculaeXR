#pragma once

#include <string>
#include <opencv2/core/mat.hpp>


// observação importante!
// não sei se é pela versão do OpenGL, mas as imagens ficam distorcidas
// caso seus tamanhos nao sejam potencia de dois (1, 2, 4, 8, 16, 32, 64, 128...)
// por isso no construtor, no load e no update tem a opcao de redimensionar a 
// imagem da altura e largura original para a potencia de dois mais proxima


class Texture {
public:
  unsigned int id;
  std::string type;

  // construtor sem definir ainda a imagem ( usar this.load() posteriormente )
  // obs: nao usar update antes de load no caso de nao ter uma imagem ainda
  Texture(std::string type);

  // construtor definindo a imagem
  Texture(std::string type, std:: string texture_filepath, bool to_power_of_2);

  // destrutor (libera a memoria da textura)
  ~Texture();

  // carrega uma imagem para a textura pelo nome do local do arquivo
  void load(std::string texture_filepath, bool to_power_of_2);

  // carrega uma imagem da camera do OpenCV
  void load(const cv::Mat& frame, bool to_power_of_2);

  // vincula a textura à unidade de textura do contexto
  void bind();

  // desvincula a textura à unidade de textura do contexto
  void unbind();

  // atualiza a imagem usada na textura
  void update(const cv::Mat& frame, bool to_power_of_2);
};
