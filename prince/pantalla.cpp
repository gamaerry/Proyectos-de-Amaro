#include "constantes.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

Coordenada *jugador = (Coordenada *)calloc(1, sizeof(Coordenada));
int frame_actual = 0;
int inicio_del_puente; // auxiliares para la construccion del puente
Coordenada *puente_actual = (Coordenada *)calloc(1, sizeof(Coordenada));

char32_t **crear_puente_separado(char32_t **mapa) {
  puente_actual->simbolo = puente;
  int random;
  int ultima = ANCHO_TOTAL - ANCHO_PLATAFORMAS - 1;
  while (puente_actual->j < ultima) {
    random = (puente_actual->i == 0)                 ? rand() % 2 + 1
             : (puente_actual->i == LARGO_TOTAL - 1) ? rand() % 2
                                                     : rand() % 3;
    bool nuevo_mov_redundante = (random == 0 && puente_actual->mov_anterior == 2) || (random == 2 && puente_actual->mov_anterior == 0);
    if (nuevo_mov_redundante || random == 1 || puente_actual->espacio_requerido > 0) {
      puente_actual->j++;
      puente_actual->espacio_requerido--;
    } else {
      puente_actual->i += random == 0 ? -1 : 1;
      puente_actual->espacio_requerido = 2;
    }
    mapa[puente_actual->i][puente_actual->j] = puente_actual->simbolo;
    puente_actual->mov_anterior = nuevo_mov_redundante ? 1 : random;
  }
  return mapa;
}

char32_t punta_del_puente(int i, int j) {
  int primera = ANCHO_PLATAFORMAS;
  if (j == primera || (j - 1) == primera)
    if (i == inicio_del_puente) {
      puente_actual->i = i;
      puente_actual->j = j;
      puente_actual->mov_anterior = 1;
      return puente;
    } else
      return agua2;
  else
    // return agua;
    return j % 2 == 1 ? agua2 : agua;
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
  mapa[LARGO_TOTAL / 2][ANCHO_TOTAL - 1] = U'\t';
  return mapa;
}

void set_jugador_al_inicio() {
  jugador->simbolo = prince;
  jugador->i = LARGO_TOTAL / 2;
  jugador->j = 1;
}

void imprimir_mapa(char32_t **mapa) {
  setlocale(LC_ALL, ""); // Habilita UTF-8 en la terminal
  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      bool es_posicion_del_jugador = i == jugador->i && j == jugador->j;
      bool es_posicion_de_la_rosa = i == LARGO_TOTAL / 2 && j == ANCHO_TOTAL - 2;
      if (es_posicion_del_jugador)
        printf("%lc", (wint_t)jugador->simbolo);
      else if (es_posicion_de_la_rosa)
        printf("%lc", (wint_t)beauty);
      else
        printf("%lc", (wint_t)mapa[i][j]);
    }
    printf("\n");
  }
}

bool es_agua(char32_t punto_en_el_mapa) {
  return punto_en_el_mapa == agua || punto_en_el_mapa == agua2;
}

void finalizar(bool feliz) {
  cout << (feliz ? FINAL_FELIZ : FINAL_TRISTE) << endl;
  jugador->mov_anterior = 1;
}

bool se_reunieron() {
  return (jugador->j == ANCHO_TOTAL - 1 || jugador->j == ANCHO_TOTAL - 2) && jugador->i == LARGO_TOTAL / 2;
}

void cambiar_olas(char32_t **mapa) {
  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      if (es_agua(mapa[i][j]) && j > ANCHO_PLATAFORMAS + 1)
        mapa[i][j] = mapa[i][j] == agua ? agua2 : agua;
    }
  }
}

void dibujar_juego(char32_t **mapa) {
  system("clear");
  frame_actual++;
  if (frame_actual % 3 == 0 || frame_actual % 3 == 1) {
    cambiar_olas(mapa);
  }
  if (se_reunieron())
    finalizar(true);
  else {
    cout << LEYENDA << endl;
    if (es_agua(mapa[jugador->i][jugador->j])) {
      set_jugador_al_inicio();
    }
    imprimir_mapa(mapa);
  }
}

int* datos;

void update(char32_t **mapa) {
  char input;
  while (jugador->mov_anterior == 0) {
    usleep(1000000);
    dibujar_juego(mapa);
    jugador->i = datos[0];
    jugador->j = datos[1];
    if (datos[0] == -1)
      finalizar(false);
    cout << (jugador->mov_anterior == 0 ? INSTRUCCIONES : "");
  }
}

int mi_fd;

int* leer_shm() {
  mi_fd = shm_open(nombre_del_shm.data(), O_RDONLY, 0666);
  datos = (int *)mmap(0, tamano_del_shm, PROT_READ, MAP_SHARED, mi_fd, 0);
  return datos;
}


int main() {
  char32_t **mapa = crear_plataformas();
  mapa = crear_puente_separado(mapa);
  set_jugador_al_inicio();
  datos = leer_shm();
  update(mapa);
  // Limpiar recursos
  munmap(datos, tamano_del_shm);
  close(mi_fd);
  return 0;
}
