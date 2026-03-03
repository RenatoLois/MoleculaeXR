//  ┌──────────────────────────────────────────────────────┐
//  │                                                      │
//  │    .   ,     .             .           .   , ,-.     │
//  │    |\ /|     |             |            \ /  |  )    │
//  │    | V | ,-. | ,-. ,-. . . | ,-: ,-.     X   |-<     │
//  │    |   | | | | |-' |   | | | | | |-'    / \  |  \    │
//  │    '   ' `-' ' `-' `-' `-` ' `-` `-'   '   ` '  '    │
//  │                                                      │
//  └──────────────────────────────────────────────────────┘
//
// Author: Renato Lóis Marcondes da Silva
// Github: https://github.com/renatolois
// License: all projects source code is licensed under GPL v3.0
//
//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//


#include <cstdlib>

#include "core/Window.hpp"

int main(int argc, char**argv) {
  Window window(600, 600, "MoleculaeXR");
  window.initBackend();
  window.init();

  window.setVisible(true);

  while (true) {
    window.pollEvents();
    window.swapBuffers();
  }
  
  return EXIT_SUCCESS;
}
