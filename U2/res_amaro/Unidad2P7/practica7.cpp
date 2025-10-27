#include <iostream>
#include "practica7.h"

extern "C" __declspec(dllexport) void hola()
{
    std::cout << "Hola mundo desde C++" << std::endl;
}
