#include "Pila.h"
#include <iostream>

void despedida(Pila *ultimo_elemento) {
  if (ultimo_elemento) {
    cout << "¡Pila no vacia! Se ha vaciado automáticamente" << endl;
    ultimo_elemento = clear(ultimo_elemento);
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
  Pila *ultimo_elemento = nullptr;
  int opcion;
  do {
    mostrar_menu();
    cin >> opcion;
    if(!cin) {
      cout << "¡No ingresó dígito válido! ";  
      cin.clear();
      cin.ignore();
    }
    if (opcion == 1)
      ultimo_elemento = push(ultimo_elemento);
    else if (opcion == 2 && ultimo_elemento)
      show(ultimo_elemento);
    else if (opcion == 3 && ultimo_elemento)
      ultimo_elemento = pop(ultimo_elemento);
    else if (opcion == 4 && ultimo_elemento)
      ultimo_elemento = clear(ultimo_elemento);
    else if (opcion == 5)
      despedida(ultimo_elemento);
    else
      cout << "No se realizó ninguna operación" << endl;
  } while (opcion != 5);
  return 0;
}
