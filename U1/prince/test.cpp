#include "constantes.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    using namespace std::chrono;

    while (true) {
        // --- aquí puedes pedir input sin problema ---
        // std::string s;
        // std::cout << "Escribe algo: ";
        // std::cin >> s;

        // Calcular el próximo tick en el segundo .500 del sistema
        auto dur = system_clock::now().time_since_epoch();
        auto ms  = duration_cast<milliseconds>(dur).count();

        // próximo múltiplo de 1000 ms + 500
        auto siguiente = time_point<system_clock>(
            (ms / 1000 + 1) * 1000ms + 500ms
        );

        // Dormir hasta el tick
        std::this_thread::sleep_until(siguiente);

        // Mostrar marca exacta
        auto tick_ms = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()
        ).count();

        std::cout << "Tick en " << tick_ms << " ms desde epoch\n";
    }
}
