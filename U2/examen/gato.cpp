#include <iostream>

using namespace std;

struct Pila { // pila recursiva
  Pila *siguiente;
  char simbolo;
};

Pila *primero = new Pila;
Pila *segundo = new Pila;
bool hay_ganador = false;
Pila *actual = new Pila;
char mapa[9] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

void imprimir_juego() {
  for (int i = 0; i < 9; i++) {
    cout << (mapa[i] == '\0' ? ' ' : mapa[i]);
    if (i % 3 == 2)
      cout << endl
           << "- - -" << endl;
    else
      cout << "|";
  }
}

bool iguales(int a, int b, int c) {
  return mapa[a] == mapa[b] && mapa[b] == mapa[c] && mapa[a] != '\0';
}

void jugar() {
  int coordenada;
  bool coordenada_aceptada = false;
  cout << "Jugador con caracter " << actual->simbolo << " ingrese las coordenadas [0, 8]: ";
  while (!coordenada_aceptada) {
    cin >> coordenada;
    coordenada_aceptada = mapa[coordenada] == '\0';
    if (!coordenada_aceptada)
      cout << "¡Coordenada ya ocupada!" << endl;
    else
      mapa[coordenada] = actual->simbolo;
  }
  actual = actual->siguiente;
  // verificar ganador
  hay_ganador = iguales(0, 1, 2) || iguales(3, 4, 5) || iguales(6, 7, 8) || iguales(0, 3, 6) || iguales(1, 4, 7) || iguales(2, 5, 8) || iguales(0, 4, 8) || iguales(2, 4, 6);
}

int main() {
  primero->siguiente = segundo;
  segundo->siguiente = primero;
  cout << "Ingrese caracter para jugador 1: " << endl;
  cin >> actual->simbolo;
  primero->simbolo = actual->simbolo;
  cout << "Ingrese caracter para jugador 2: " << endl;
  cin >> actual->simbolo;
  segundo->simbolo = actual->simbolo;
  actual = primero;
  while (!hay_ganador) {
    imprimir_juego();
    jugar();
  }
  cout << "Ganó jugador con caracter: " << actual->siguiente->simbolo << endl;
  return 1;
}
