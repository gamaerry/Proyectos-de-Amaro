#include "LibreriaPila.h"
#include <iostream>

using namespace std;

void despedida(bool hay_elementos) {
  if (hay_elementos) {
    cout << "¡Pila no vacia! Se ha vaciado automáticamente" << endl;
    clear();
  }
  cout << "¡Hasta pronto!" << endl;
}

void mostrar_menu() {
  cout << "\nIngrese opcion: " << endl;
  cout << "1. Ingresar elemento a la pila" << endl;
  cout << "2. Mostrar la pila" << endl;
  cout << "3. Quitar el utilmo elemento" << endl;
  cout << "4. Limpiar pila" << endl;
  cout << "5. Salir" << endl;
}

int main() {
  int opcion;
  do {
    mostrar_menu();
    cin >> opcion;
    if (!cin) {
      cout << "¡No ingresó dígito válido! ";
      cin.clear();
      cin.ignore();
    }
    if (opcion == 1)
      push();
    else if (opcion == 2 && !esta_vacio())
      show();
    else if (opcion == 3 && !esta_vacio())
      pop();
    else if (opcion == 4 && !esta_vacio())
      clear();
    else if (opcion == 5)
      despedida(!esta_vacio());
    else
      cout << "No se realizó ninguna operación" << endl;
  } while (opcion != 5);
  return 0;
}
