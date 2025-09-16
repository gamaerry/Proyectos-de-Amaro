#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <type_traits>

using namespace std;
const string INSTRUCCIONES = "~ Comandos ~ \nUse WASD para moverse, puede combinar y presionar varias veces en un solo comando, así como indicar cuantos pasos moverse (pe. para dos arriba y tres derecha puede escribir \"2w3d\" o bien \"wwddd\")\n";
const string LEYENDA = "Ayuda al principito a encontrarse con su Rosa...";
const string DESPEDIDA = "¡Hasta pronto!";
const char32_t jugador_neutral = U'♥';
const char32_t jugador_feliz = U'💓';
const char32_t rosa_neutral = U'🥀';
const char32_t rosa_feliz = U'🌹';
const char32_t puente = U'⧥';
const char32_t plataforma = U'_';
const char32_t agua = U' ';
const char32_t agua2 = U'⦚';
const int LARGO_TOTAL = 5;
const int ANCHO_PLATAFORMAS = 3;
const int ANCHO_PUENTE = 10;
const int ANCHO_TOTAL = ANCHO_PLATAFORMAS * 2 + ANCHO_PUENTE;
bool fin = false;

// Estructura simple
struct Coordenada {
  int i;
  int j;
  int mov_anterior;
  int espacio_requerido = 0;
  char32_t simbolo;
};

Coordenada *jugador = (Coordenada *)calloc(1, sizeof(Coordenada));
Coordenada *rosa = (Coordenada *)calloc(1, sizeof(Coordenada));

// auxiliares para la construccion del puente
int inicio_del_puente;
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

char32_t **crear_puente(char32_t **mapa) {
  int random;
  int ultima = ANCHO_TOTAL - ANCHO_PLATAFORMAS - 1;
  while (puente_actual->j < ultima) {
    random = (puente_actual->i == 0)                 ? rand() % 2 + 1
             : (puente_actual->i == LARGO_TOTAL - 1) ? rand() % 2
                                                     : rand() % 3;
    bool nuevo_mov_redundante = (random == 0 && puente_actual->mov_anterior == 2) || (random == 2 && puente_actual->mov_anterior == 0);
    if (nuevo_mov_redundante)
      puente_actual->j++;
    else {
      puente_actual->i += random == 0 ? -1 : random == 2 ? 1
                                                         : 0;
      puente_actual->j += random == 1 ? 1 : 0;
    }
    mapa[puente_actual->i][puente_actual->j] = puente;
    puente_actual->mov_anterior = nuevo_mov_redundante ? 1 : random;
  }
  cout << endl;
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
  mapa[LARGO_TOTAL / 2][ANCHO_TOTAL - 1] = ' ';
  return mapa;
}

void set_jugador(bool vio_a_su_rosa) {
  if (vio_a_su_rosa) {
    jugador->simbolo = jugador->simbolo == jugador_feliz ? jugador_neutral : jugador_feliz;
  } else {
    jugador->simbolo = jugador_neutral;
    jugador->i = LARGO_TOTAL / 2;
    jugador->j = 1;
  }
}

void set_rosa(bool vio_a_jugador) {
  if (vio_a_jugador) {
    rosa->simbolo = rosa->simbolo == rosa_feliz ? rosa_neutral : rosa_feliz;
  } else {
    rosa->simbolo = rosa_neutral;
    rosa->i = LARGO_TOTAL / 2;
    rosa->j = ANCHO_TOTAL - 2;
  }
}

void imprimir_mapa(char32_t **mapa) {
  setlocale(LC_ALL, ""); // Habilita UTF-8 en la terminal
  for (int i = 0; i < LARGO_TOTAL; i++) {
    for (int j = 0; j < ANCHO_TOTAL; j++) {
      bool es_posicion_del_jugador = i == jugador->i && j == jugador->j;
      bool es_posicion_de_la_rosa = i == rosa->i && j == rosa->j;
      if (es_posicion_del_jugador)
        printf("%lc", (wint_t)jugador->simbolo);
      else if (es_posicion_de_la_rosa)
        printf("%lc", (wint_t)rosa->simbolo);
      else
        printf("%lc", (wint_t)mapa[i][j]);
    }
    printf("\n");
  }
}

bool es_agua(char32_t punto_en_el_mapa) {
  return punto_en_el_mapa == agua || punto_en_el_mapa == agua2;
}

bool se_reunieron() {
  return jugador->j == ANCHO_TOTAL - 1 || jugador->j == ANCHO_TOTAL - 2 && jugador->i == LARGO_TOTAL / 2;
}

void dibujar_juego(char32_t **mapa) {
  system("clear");
  if (se_reunieron()){
    cout << "―He aquí mi secreto: Solo con el corazón se puede ver bien; lo escencial es invisible a los ojos.\n\n―Sólo con el corazón... Lo escencial es invisible a los ojos...―repitió el principito para recordarlo.\n\n―Lo que hace importante a tu rosa, es el tiempo que le has dedicado.\n\n―...es el tiempo que le he dedicado...―repitió el principito con el fin de recordarlo." << endl;
    fin = true;
  } else {
      cout << LEYENDA << endl;
      if (es_agua(mapa[jugador->i][jugador->j])) {
        set_jugador(false);
      }
      imprimir_mapa(mapa);
  }
}

void escuchar_input(char32_t **mapa) {
  char input;
  while (!fin) {
    dibujar_juego(mapa);
    cout << (fin ? " " : INSTRUCCIONES);
    cin >> input;
    switch (input) {
    case 'w':
    case 'W':
      if (jugador->i > 0)
        jugador->i--;
      break;
    case 's':
    case 'S':
      if (jugador->i < LARGO_TOTAL - 1)
        jugador->i++;
      break;
    case 'a':
    case 'A':
      if (jugador->j > 0)
        jugador->j--;
      break;
    case 'd':
    case 'D':
      if (jugador->j < ANCHO_TOTAL - 1)
        jugador->j++;
      break;
    case 'q':
    case 'Q':
      // system("clear");
      cout << DESPEDIDA << endl;
      return;
    }
  }
}

int main() {
  char32_t **mapa = crear_plataformas();
  mapa = crear_puente_separado(mapa);
  set_jugador(false);
  set_rosa(false);
  escuchar_input(mapa);
  return 0;
}
