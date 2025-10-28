#include "LibreriaPractica7.h"
#include <iostream>

extern "C" EXPORT void saludo() {
  std::cout << "Hola mundo desde C++" << std::endl;
}

extern "C" EXPORT void saludoConNombre(const char* nombre) {
  std::cout << "Hola mundo desde C++ " << nombre << std::endl;
}
