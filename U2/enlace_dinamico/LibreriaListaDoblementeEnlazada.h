#ifndef LIBRERIALISTADOBLEMENTEENLAZADA_H
#define LIBRERIALISTADOBLEMENTEENLAZADA_H

#ifdef _WIN32 // sistemas windows: g++ -shared -o LibreriaPila.dll LibreriaPila.cpp -static-libgcc -static-libstdc++
#define EXPORT __declspec(dllexport)
#else // linux (.so) y mac (.dylib): g++ -fPIC -shared -o libLibreriaPila.so LibreriaPila.cpp // COMPROBAR SI ES NECESARIO!!
#define EXPORT __attribute__((visibility("default")))
#endif
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int is_loop();
EXPORT int get_contador();
EXPORT void disable_loop();
EXPORT void enable_loop();
EXPORT int insert(int before, int indice, const char *nombre);
EXPORT int remove_in(int indice);
EXPORT int clear();
EXPORT const char *get_nombre_playlist();
EXPORT void set_nombre_playlist(const char *_nombre);
EXPORT int is_random();
EXPORT void set_random(int _aleatorio);
EXPORT int play();

#ifdef __cplusplus
}
#endif

#endif
