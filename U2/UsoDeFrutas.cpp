#include "Fruta.h"
#include <iostream>

void despedida(Fruta *ultima_fruta) {
  if (ultima_fruta) {
    cout << "¡Pila no vacia! Se ha vaciado automáticamente" << endl;
    ultima_fruta = clear(ultima_fruta);
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
  Fruta *ultima_fruta = nullptr;
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
      ultima_fruta = push(ultima_fruta);
    else if (opcion == 2 && ultima_fruta)
      show(ultima_fruta);
    else if (opcion == 3 && ultima_fruta)
      ultima_fruta = pop(ultima_fruta);
    else if (opcion == 4 && ultima_fruta)
      ultima_fruta = clear(ultima_fruta);
    else if (opcion == 5)
      despedida(ultima_fruta);
    else
      cout << "No se realizó ninguna operación" << endl;
  } while (opcion != 5);
  return 0;
}
