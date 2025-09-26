#include <cstdlib>
#include <iostream>

using namespace std;

// Estructura simple
struct Coordenada {
  int x;
  int y;
};

int main() {
  // Reservar memoria para una variable de tipo Coordenada
  Coordenada *coordenada = (Coordenada *)calloc(1, sizeof(Coordenada));

  // Asignar valores a los miembros de la estructura
  cout << "Ingrese x: ";
  cin >> coordenada->x;
  cout << "Ingrese y: ";
  cin >> coordenada->y;

  // Imprimir los valores
  cout << "Coordenada: (" << coordenada->x << ", " << coordenada->y << ")"
       << endl;

  for (int i = 0; i < coordenada->x * coordenada->y; i++) {
    if (i % coordenada->x == 0 && i != 0) {
      cout << "\n";
    }
    if (i == (coordenada->x * coordenada->y - 1)) {
      cout << "x";
    } else {
      cout << "_";
    }
  }
  cout << "\n";
  // Liberar la memoria
  free(coordenada);
  coordenada = nullptr;

  return 0;
}
