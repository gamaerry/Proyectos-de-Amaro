#ifndef PILA_H
#define PILA_H

#include <string>
using namespace std;

const int TAMANO_MAXIMO = 1024;

struct Pila {
  char nombre[TAMANO_MAXIMO];
  Pila* elemento_trasero;
};

Pila* push(Pila* ultimo_elemento);
Pila* pop(Pila* ultimo_elemento);
Pila* clear(Pila* ultimo_elemento);
bool is_empty(Pila* ultimo_elemento);
void show(Pila* ultimo_elemento);

#endif

