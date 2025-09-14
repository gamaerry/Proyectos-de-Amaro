#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

// MÉTODO 1: Solo system("clear") - SIMPLE pero lenta
void metodo1_SoloSystemClear() {
    system("clear");
}

// MÉTODO 2: Solo secuencias ANSI - RÁPIDA pero puede dejar rastros
void metodo2_SoloANSI() {
    cout << "\033[2J";  // Limpiar pantalla
    cout << "\033[H";   // Mover cursor al inicio (0,0)
    // O en una sola línea: cout << "\033[2J\033[H";
}

// MÉTODO 3: COMBINACIÓN - Lo mejor de ambos mundos
void metodo3_Combinacion() {
    // Primero: Limpiar con ANSI (rápido)
    cout << "\033[2J\033[H";
    cout.flush();  // Forzar que se ejecute inmediatamente
    
    // Segundo: Reforzar con system (garantía)
    system("clear");
}

// MÉTODO 4: COMBINACIÓN OPTIMIZADA - Mi recomendación
void metodo4_CombinacionOptimizada() {
    // Solo usar system("clear") - es suficiente y confiable
    system("clear");
    
    // Opcional: Asegurar que el cursor esté en (0,0)
    cout << "\033[H";
    cout.flush();
}

// MÉTODO 5: COMBINACIÓN COMPLETA - Para casos extremos
void metodo5_CombinacionCompleta() {
    // 1. Limpiar con ANSI
    cout << "\033[2J";      // Limpiar pantalla completa
    cout << "\033[3J";      // Limpiar historial de scroll (opcional)
    cout << "\033[H";       // Mover cursor al inicio
    cout.flush();
    
    // 2. Reforzar con system
    system("clear");
}

// Función para demostrar cada método
void demostracion() {
    cout << "=== DEMOSTRACIÓN DE MÉTODOS DE LIMPIEZA ===" << endl;
    
    for (int metodo = 1; metodo <= 5; metodo++) {
        cout << "\nPresiona Enter para probar el Método " << metodo << "...";
        cin.get();
        
        // Llenar pantalla con texto basura
        for (int i = 0; i < 20; i++) {
            cout << "Línea basura " << i << " - Esta línea debería desaparecer completamente" << endl;
        }
        
        cout << "\nAhora limpiando con Método " << metodo << "..." << endl;
        usleep(1000000); // Esperar 1 segundo
        
        // Aplicar el método correspondiente
        switch (metodo) {
            case 1:
                metodo1_SoloSystemClear();
                cout << "✓ MÉTODO 1: Solo system(\"clear\")" << endl;
                break;
            case 2:
                metodo2_SoloANSI();
                cout << "✓ MÉTODO 2: Solo secuencias ANSI" << endl;
                break;
            case 3:
                metodo3_Combinacion();
                cout << "✓ MÉTODO 3: Combinación ANSI + system" << endl;
                break;
            case 4:
                metodo4_CombinacionOptimizada();
                cout << "✓ MÉTODO 4: Combinación optimizada (RECOMENDADO)" << endl;
                break;
            case 5:
                metodo5_CombinacionCompleta();
                cout << "✓ MÉTODO 5: Combinación completa" << endl;
                break;
        }
        
        cout << "Pantalla limpiada. ¿Se ve limpia? (s/n): ";
        char respuesta;
        cin >> respuesta;
        cin.ignore(); // Limpiar buffer
        
        if (respuesta == 'n' || respuesta == 'N') {
            cout << "❌ Método " << metodo << " no funcionó bien en tu terminal" << endl;
        } else {
            cout << "✅ Método " << metodo << " funcionó correctamente" << endl;
        }
    }
}

// EJEMPLO PRÁCTICO: Juego simple usando la mejor solución
struct Jugador {
    int x = 10, y = 5;
    char simbolo = '@';
};

void dibujarJuego(const Jugador& jugador, int frame) {
    // AQUÍ ESTÁ LA CLAVE: La solución más efectiva
    // system("clear");  // Borra TODO el contenido anterior
    metodo2_SoloANSI();
    cout << "=== JUEGO FRAME " << frame << " ===" << endl;
    cout << "Posición del jugador: (" << jugador.x << ", " << jugador.y << ")" << endl;
    cout << endl;
    
    // Dibujar mapa simple
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 20; x++) {
            if (x == jugador.x && y == jugador.y) {
                cout << jugador.simbolo;
            } else if (x == 0 || x == 19 || y == 0 || y == 9) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
    
    cout << "\nUsa WASD para mover, Q para salir" << endl;
}

void ejemploPractico() {
    Jugador jugador;
    int frame = 0;
    char input;
    
    cout << "=== EJEMPLO PRÁCTICO ===" << endl;
    cout << "Vamos a probar el movimiento con limpieza de pantalla" << endl;
    cout << "Presiona Enter para comenzar...";
    cin.get();
    
    while (true) {
        // ESTA ES LA LÍNEA CLAVE QUE RESUELVE TU PROBLEMA
        dibujarJuego(jugador, ++frame);
        
        cout << "Movimiento: ";
        cin >> input;
        
        switch (input) {
            case 'w': case 'W':
                if (jugador.y > 1) jugador.y--;
                break;
            case 's': case 'S':
                if (jugador.y < 8) jugador.y++;
                break;
            case 'a': case 'A':
                if (jugador.x > 1) jugador.x--;
                break;
            case 'd': case 'D':
                if (jugador.x < 18) jugador.x++;
                break;
            case 'q': case 'Q':
                system("clear");
                cout << "¡Adiós!" << endl;
                return;
        }
    }
}

int main() {
    int opcion;
    
    cout << "¿Qué quieres hacer?" << endl;
    cout << "1. Ver demostración de métodos" << endl;
    cout << "2. Ejemplo práctico de juego" << endl;
    cout << "Opción: ";
    cin >> opcion;
    cin.ignore();
    
    if (opcion == 1) {
        demostracion();
    } else {
        ejemploPractico();
    }
    
    return 0;
}
