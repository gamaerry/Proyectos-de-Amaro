#ifndef LIBRERIAPILA_H
#define LIBRERIAPILA_H

#ifdef _WIN32 // sistemas windows: g++ -shared -o LibreriaPila.dll LibreriaPila.cpp -static-libgcc -static-libstdc++
#define EXPORT __declspec(dllexport)
#else // linux (.so) y mac (.dylib): g++ -fPIC -shared -o libLibreriaPila.so LibreriaPila.cpp
#define EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif
int empty();
void push(const char* nombre);
void pop();
void clear();
void show();
#ifdef __cplusplus
}
#endif

#endif
