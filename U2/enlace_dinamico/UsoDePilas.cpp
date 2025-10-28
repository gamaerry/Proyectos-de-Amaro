#include "LibreriaPila.h"
#include <iostream>
#include <string>

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
  string nombre;
  do {
    mostrar_menu();
    cin >> opcion;
    if (!cin) {
      cout << "¡No ingresó dígito válido! ";
      cin.clear();
      cin.ignore();
    }
    if (opcion == 1) {
      cout << "Ingrese el nombre del elemento: ";
      cin.ignore();
      getline(cin, nombre);
      push(nombre.c_str());
    } else if (opcion == 2 && !empty())
      show();
    else if (opcion == 3 && !empty())
      pop();
    else if (opcion == 4 && !empty())
      clear();
    else if (opcion == 5)
      despedida(!empty());
    else
      cout << "No se realizó ninguna operación" << endl;
  } while (opcion != 5);
  return 0;
}
