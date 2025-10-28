#ifndef PILA_H
#define PILA_H

#ifdef _WIN32 // sistemas windows: g++ -shared -o practica7.dll practica7.cpp -static-libgcc -static-libstdc++
#define EXPORT __declspec(dllexport)
#else // linux (.so) y mac (.dylib): g++ -fPIC -shared -o libpractica7.so practica7.cpp
#define EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif
const int TAMANO_MAXIMO = 1024;
struct Pila {
  char nombre[TAMANO_MAXIMO];
  Pila *elemento_trasero;
};
Pila *get_last();
void push();
void pop();
void clear();
void show();
#ifdef __cplusplus
}
#endif

#endif
