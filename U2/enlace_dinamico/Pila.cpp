#include "Pila.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const string MSJ_PEDIR_NOMBRE = "Ingrese el nombre del elemento: ";

Pila *push(Pila *ultimo_elemento) {
  Pila *nuevo_elemento = (Pila *)malloc(sizeof(Pila));
  cout << MSJ_PEDIR_NOMBRE;
  cin.ignore();
  cin.getline(nuevo_elemento->nombre, TAMANO_MAXIMO);
  nuevo_elemento->elemento_trasero= ultimo_elemento;
  return nuevo_elemento;
}

Pila *pop(Pila *ultimo_elemento) {
  Pila *penultimo_elemento = ultimo_elemento->elemento_trasero;
  free(ultimo_elemento);
  // delete ultimo_elemento; // es mejor usar delete?
  return penultimo_elemento;
}

Pila *clear(Pila *ultimo_elemento) {
  while (ultimo_elemento != nullptr)
    ultimo_elemento = pop(ultimo_elemento);
  return nullptr;
}

bool is_empty(Pila *ultimo_elemento) {
  return !ultimo_elemento;
}

void show(Pila *ultimo_elemento) {
  Pila *a_mostrar = ultimo_elemento;
  cout << "======================================" << endl;
  while (a_mostrar != nullptr) {
    cout << "‖" << endl;
    cout << "‖ Nombre del elemento: " << a_mostrar->nombre << endl;
    cout << "‖ Direccion en memoria: " << a_mostrar << endl;
    cout << "‖" << endl;
    cout << "‖ (Encima de " << (a_mostrar->elemento_trasero ? a_mostrar->elemento_trasero->nombre : "ninguno") << ")" <<endl;
    cout << "======================================" << endl;
    a_mostrar = a_mostrar->elemento_trasero;
  }
}
