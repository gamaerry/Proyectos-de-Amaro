#include <cstdlib>
#include <iostream>
#include <system_error>
#include <time.h>

using namespace std;

char32_t jugador = U'♡';
char32_t rosa = U'𓍯';
char32_t puente = U'⧥';
char32_t plataforma = U'_';
char32_t agua = U' ';
char32_t agua2 = U'︴';
char32_t vacio;
const int LARGO_TOTAL = 5;
const int ANCHO_PLATAFORMAS = 3;
const int ANCHO_PUENTE = 10;
const int ANCHO_TOTAL = ANCHO_PLATAFORMAS * 2 + ANCHO_PUENTE; //(3+10+3) = 16

// Estructura simple
struct Coordenada {
  int i;
  int j;
};

// auxiliares para la construccion del puente
int inicio_del_puente;
Coordenada *actual = (Coordenada *)calloc(1, sizeof(Coordenada));

char32_t **crear_puente(char32_t **mapa) {
  int random;
  int ultima = ANCHO_TOTAL - ANCHO_PLATAFORMAS - 1;
  while (actual->j < ultima) {
    random = (actual->i == 0)                 ? rand() % 2 + 1
             : (actual->i == LARGO_TOTAL - 1) ? rand() % 2
                                              : rand() % 3;
    actual->i += random == 0 ? -1 : random == 2 ? 1
                                                : 0;
    actual->j += random == 1 ? 1 : 0;
    mapa[actual->i][actual->j] = puente;
  }
  return mapa;
}

char32_t punta_del_puente(int i, int j) {
  int primera = ANCHO_PLATAFORMAS;
  if (j == primera || (j - 1) == primera) {
    actual->i = i;
    actual->j = j;
    return (i == inicio_del_puente ? puente : agua);
  } else
    return agua;
  // return j%2 == 0 ? agua2 : vacio;
}

char32_t **crear_plataformas() {
  srand(time(NULL)); // semilla distinta cada vez
  inicio_del_puente = rand() % LARGO_TOTAL;
  // cout << random();
  char32_t **mapa = (char32_t **)malloc(LARGO_TOTAL * sizeof(char32_t *));
  for (int i = 0; i < LARGO_TOTAL; i++)
    mapa[i] = (char32_t *)malloc(ANCHO_TOTAL * sizeof(char32_t));

  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      if (j % ANCHO_TOTAL < ANCHO_PLATAFORMAS)
        mapa[i][j] = plataforma;
      else if (j % ANCHO_TOTAL < (ANCHO_PLATAFORMAS + ANCHO_PUENTE))
        mapa[i][j] = punta_del_puente(i, j);
      else
        mapa[i][j] = plataforma;
    }
  }

  return mapa;
}

void imprimir_mapa(char32_t **mapa) {
  setlocale(LC_ALL, ""); // Habilita UTF-8 en la terminal
  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++)
      printf("%lc", (wint_t)mapa[i][j]);
    printf("\n");
  }
}

int main() {
  char32_t **mapa = crear_plataformas();
  mapa = crear_puente(mapa);
  mapa[LARGO_TOTAL/2][ANCHO_TOTAL-2] = rosa;
  mapa[LARGO_TOTAL/2][ANCHO_TOTAL-1] = ' ';
  mapa[LARGO_TOTAL/2][1] = jugador;
  imprimir_mapa(mapa);
  return 0;
}
