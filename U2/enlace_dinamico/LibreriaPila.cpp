#include "LibreriaPila.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const int TAMANO_MAXIMO = 1024;
const string MSJ_PEDIR_NOMBRE = "Ingrese el nombre del elemento: ";

struct Pila {
  char nombre[TAMANO_MAXIMO];
  Pila *elemento_trasero;
};

Pila *ultimo_elemento = nullptr;

int empty() {
  return !ultimo_elemento;
}

void push() {
  Pila *nuevo_elemento = (Pila *)malloc(sizeof(Pila));
  cout << MSJ_PEDIR_NOMBRE;
  cin.ignore();
  cin.getline(nuevo_elemento->nombre, TAMANO_MAXIMO);
  nuevo_elemento->elemento_trasero = ultimo_elemento;
  ultimo_elemento = nuevo_elemento;
  if (!empty())
    cout << "¡Nuevo " << ultimo_elemento->nombre << " elemento introducido!" << endl;
}

void pop() {
  Pila *penultimo_elemento = ultimo_elemento->elemento_trasero;
  ultimo_elemento->elemento_trasero = nullptr;
  free(ultimo_elemento);
  // delete ultimo_elemento; // es mejor usar delete?
  ultimo_elemento = penultimo_elemento;
}

void clear() {
  while (ultimo_elemento)
    pop();
}

void show() {
  Pila *a_mostrar = ultimo_elemento;
  cout << "======================================" << endl;
  while (a_mostrar != nullptr) {
    cout << "‖" << endl;
    cout << "‖ Nombre del elemento: " << a_mostrar->nombre << endl;
    cout << "‖ Direccion en memoria: " << a_mostrar << endl;
    cout << "‖" << endl;
    cout << "‖ (Encima de " << (a_mostrar->elemento_trasero ? a_mostrar->elemento_trasero->nombre : "ninguno") << ")" << endl;
    cout << "======================================" << endl;
    a_mostrar = a_mostrar->elemento_trasero;
  }
}
