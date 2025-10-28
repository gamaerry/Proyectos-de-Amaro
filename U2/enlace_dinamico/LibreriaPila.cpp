#include "LibreriaPila.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

const int TAMANO_MAXIMO = 1024;

struct Pila {
  char nombre[TAMANO_MAXIMO];
  Pila *elemento_trasero;
};

Pila *ultimo_elemento = nullptr;

int empty() {
  return !ultimo_elemento;
}

void push(const char *nombre) {
  Pila *nuevo_elemento = (Pila *)malloc(sizeof(Pila));
  strncpy(nuevo_elemento->nombre, nombre, TAMANO_MAXIMO - 1);
  nuevo_elemento->nombre[TAMANO_MAXIMO - 1] = '\0';
  nuevo_elemento->elemento_trasero = ultimo_elemento;
  ultimo_elemento = nuevo_elemento;
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
