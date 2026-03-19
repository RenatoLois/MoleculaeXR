#pragma once

#include <unordered_map>
class CallbackManager {
private:
  std::unordered_map<unsigned int, void(*)()> callbacks_map;

public:
  // adiciona uma funcao que sera executada caso seja usado esse id
  void register_callback(unsigned int id, void(* callback )() );

  // retorna verdadeiro caso encontrar callback que use esse ID 
  // retorna falso caso nao encontre
  bool run_callback(unsigned int id);
};
