#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <regex>
#include <string>
using namespace std;

const string INSTRUCCIONES = "Comandos: \nUse WASD para moverse, puede combinar y presionar varias veces en un solo comando, así como indicar cuantos pasos moverse (pe. para dos arriba y tres derecha puede escribir \"2w3d\" o bien \"wwddd\") y use Q para salir\n";
const string LEYENDA = "Ayuda al principito a encontrarse con su Rosa...";
const string FINAL_FELIZ = "―He aquí mi secreto: Solo con el corazón se puede ver bien; lo escencial es invisible a los ojos.\n\n―Sólo con el corazón... Lo escencial es invisible a los ojos...―repitió el principito para recordarlo.\n\n―Lo que hace importante a tu rosa, es el tiempo que le has dedicado.\n\n―...es el tiempo que le he dedicado...―repitió el principito con el fin de recordarlo.";
const string FINAL_TRISTE = "―Adiós― le dijo a la flor, pero ella no respondió.\n―Adiós― repitió el principito.\nLa flor tosió aunque no estaba resfriada y al fin dijo:\n―He sido una tonta, perdóname y procura ser feliz.";
const char32_t prince = U'♥';
const char32_t beauty = U'🥀';
const char32_t puente = U'⧥';
const char32_t plataforma = U'_';
const char32_t agua = U' ';
const char32_t agua2 = U'⦚';
const int LARGO_TOTAL = 5;
const int ANCHO_PLATAFORMAS = 3;
const int ANCHO_PUENTE = 20;
const int ANCHO_TOTAL = ANCHO_PLATAFORMAS * 2 + ANCHO_PUENTE;
const int i_inicial_jugador = LARGO_TOTAL / 2;
const int j_inicial_jugador = 1;
const int i_inicial_rosa = i_inicial_jugador;
const int j_inicial_rosa = ANCHO_TOTAL - 2;
const string nombre_del_shm = "/Jugador";
const size_t tamano_del_shm = 1024;
const regex patron_movimiento("^[0-9wasdWASD]+$");
const regex patron_salir("^[qQ]$");
const string direcciones_validas = "wasdWASD";


// Estructura simple
struct Coordenada {
  int i;
  int j;
  int mov_anterior = 0;
  int espacio_requerido = 0;
  char32_t simbolo;
};

#endif

