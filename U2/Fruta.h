#ifndef FRUTA_H
#define FRUTA_H

#include <string>
using namespace std;

const int TAMANO_MAXIMO = 1024;

struct Fruta {
  char nombre[TAMANO_MAXIMO];
  Fruta* fruta_trasera;
};

Fruta* push(Fruta* ultima_fruta);
Fruta* pop(Fruta* ultima_fruta);
Fruta* clear(Fruta* ultima_fruta);
bool is_empty(Fruta* ultima_fruta);
void show(Fruta* ultima_fruta);

#endif

