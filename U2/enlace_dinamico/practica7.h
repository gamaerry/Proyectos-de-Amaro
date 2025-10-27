#ifndef PRACTICA7_H
#define PRACTICA7_H

#ifdef _WIN32 // sistemas windows: g++ -shared -o practica7.dll practica7.cpp -static-libgcc -static-libstdc++
#define EXPORT __declspec(dllexport)
#else // linux (.so) y mac (.dylib): g++ -fPIC -shared -o libpractica7.so practica7.cpp
#define EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif
EXPORT void saludo();
EXPORT void saludoConNombre(const char *nombre);
#ifdef __cplusplus
}
#endif

#endif
