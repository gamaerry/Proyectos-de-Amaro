#include "constantes.h"
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

using namespace std::chrono;


 void wait_pantalla() {
  auto dur = std::chrono::system_clock::now().time_since_epoch();
  auto reloj_control = time_point<system_clock>(
    (duration_cast<milliseconds>(dur).count() / 1000 + 1) * 1000ms + 500ms // mitad de segundo
  );
  auto reloj_pantalla = time_point<system_clock>(
    (duration_cast<milliseconds>(dur).count() / 1000 + 1) * 1000ms // en el segundo
  );
  std::this_thread::sleep_until(reloj_pantalla);
  reloj_pantalla += 1s;
}

int main() {
  while (true) {
    wait_pantalla();

  }
}
