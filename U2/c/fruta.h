#ifndef FRUTA_H
#define FRUTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fruta {
  char nombre[100];
  struct Fruta *fruta_trasera;
};

struct Fruta *push(struct Fruta *ultima_fruta);
struct Fruta *pop(struct Fruta *ultima_fruta);
struct Fruta *clear(struct Fruta *ultima_fruta);
int is_empty(struct Fruta *ultima_fruta);
void show(struct Fruta *ultima_fruta);

#endif
