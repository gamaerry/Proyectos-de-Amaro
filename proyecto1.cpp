#include <cstdlib>
#include <iostream>
#include <system_error>
#include <time.h>

using namespace std;

const int LARGO_TOTAL = 5;
const int ANCHO_PLATAFORMAS = 3;
const int ANCHO_PUENTE = 10;
const int ANCHO_TOTAL = ANCHO_PLATAFORMAS * 2 + ANCHO_PUENTE; //(3+10+3) = 16

// auxiliares para la construccion del puente
int inicio_del_puente;
bool va_vertical;

// char32_t puente_o_vacio(int i, int j) {
//   int primera = ANCHO_PLATAFORMAS;
//   int ultima = ANCHO_TOTAL - ANCHO_PLATAFORMAS - 1;
//   if (j == primera || (j-1) == primera) {
//     return (i == inicio_del_puente ? '_' :' ');
//   } else return ' ';
// }

char32_t **crear_mapa() {
  srand(time(NULL));  // semilla distinta cada vez
  inicio_del_puente = rand()%LARGO_TOTAL;
  // cout << random();
  char32_t **mapa = (char32_t **)malloc(LARGO_TOTAL * sizeof(char32_t *));
  for (int i = 0; i < LARGO_TOTAL; i++)
    mapa[i] = (char32_t *)malloc(ANCHO_TOTAL * sizeof(char32_t));

  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      if (j % ANCHO_TOTAL < ANCHO_PLATAFORMAS)
        mapa[i][j] = '_';
      else if (j % ANCHO_TOTAL < (ANCHO_PLATAFORMAS + ANCHO_PUENTE))
        mapa[i][j] = ' ';
      else
        mapa[i][j] = '_';
    }
  }

  return mapa;
}

void imprimir_mapa(char32_t **mapa) {
  setlocale(LC_ALL, ""); // Habilita UTF-8 en la terminal
  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      if (mapa[i][j] == '_' && mapa[i][j + 1] == U'🯅')
        printf("%c\u0332", mapa[i][j]);
      else
        printf("%lc", (wint_t)mapa[i][j]);
    }
    printf("\n");
  }
}

int main() {
  char32_t jugador = U'🯅';
  char32_t **mapa = crear_mapa();
  mapa[2][1] = jugador;
  imprimir_mapa(mapa);
  return 0;
}
