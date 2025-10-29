#include "LibreriaListaDoblementeEnlazada.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sched.h>
#include <string>
#include <vector>

using namespace std;

struct Nodo {
  std::string nombre;
  Nodo *siguiente;
  Nodo *anterior;
};

Nodo *primero = nullptr;
int contador = 0;
int circular = 0;

int is_loop() {
  return circular;
}

int get_contador() {
  return contador;
}

Nodo *get_first() { // metodos privados (no estan registrados en el .h)
  return primero;
}

Nodo *get_last() { // metodos privados (no estan registrados en el .h)
  Nodo *ultimo = primero;
  for (int i = 0; i < contador - 1; i++)
    ultimo = ultimo->siguiente;
  return ultimo;
}

void disable_loop() {
  if (contador > 0) {
    Nodo *ultimo = get_last();
    primero->anterior = nullptr;
    ultimo->siguiente = nullptr;
    circular = 0;
  }
}

void enable_loop() {
  if (contador > 0) {
    Nodo *ultimo = get_last();
    primero->anterior = ultimo;
    ultimo->siguiente = primero;
    circular = 1;
  }
}

int insert(int before, int indice, const char* nombre) {
  Nodo *nuevo = new Nodo;
  nuevo->nombre = nombre;
  nuevo->anterior = nullptr;
  nuevo->siguiente = nullptr;
  if (indice > contador)
    return 0;
  if (contador == 0)
    primero = nuevo;
  else {
    Nodo *a_modificar = primero;
    for (int i = 0; i < indice; i++)
      a_modificar = a_modificar->siguiente;
    Nodo *anterior = a_modificar->anterior;
    Nodo *siguiente = a_modificar->siguiente;
    if (before) {
      nuevo->anterior = anterior;
      nuevo->siguiente = a_modificar;
      if (anterior)
        anterior->siguiente = nuevo;
      if (a_modificar)
        a_modificar->anterior = nuevo;
      if (a_modificar == primero)
        primero = nuevo;
    } else {
      nuevo->siguiente = siguiente;
      nuevo->anterior = a_modificar;
      if (siguiente)
        siguiente->anterior = nuevo;
      if (a_modificar)
        a_modificar->siguiente = nuevo;
    }
  }
  contador++;
  return 1;
}

int remove_in(int indice) {
  if (indice > contador || contador == 0)
    return 0;
  Nodo *actual = primero;
  for (int i = 0; i < indice; i++)
    actual = actual->siguiente;
  Nodo *anterior = actual->anterior;
  Nodo *siguiente = actual->siguiente;

  if (actual == primero)
    primero = siguiente;

  if (anterior)
    anterior->siguiente = siguiente;
  actual->anterior = nullptr;
  if (siguiente)
    siguiente->anterior = anterior;
  actual->siguiente = nullptr;

  delete actual;
  contador--;
  return 1;
}

int clear() {
  if (contador == 0)
    return 0;
  while (remove_in(0))
    ;
  return 1;
}

// Métodos más relacionados con playlist que con listas doblemente enlazadas:
string nombre_playlist = "My new playlist";
int aleatorio = 0;

const char* get_nombre_playlist() {
  return nombre_playlist.c_str();
}

void set_nombre_playlist(const char* _nombre_playlist) {
  nombre_playlist = _nombre_playlist;
}

int is_random() {
  return aleatorio;
}

void set_random(int _aleatorio) {
  aleatorio = _aleatorio;
}

int play() { // es un print especializado, simula la reproduccion de una playlist
  if (get_contador() == 0)
    return 0;
  vector<int> orden;
  for (int i = 0; i < get_contador(); i++)
    orden.push_back(i);
  if (aleatorio) { // Mezclar el vector usando Fisher-Yates shuffle
    for (int i = get_contador() - 1; i > 0; i--) {
      int j = rand() % (i + 1);
      swap(orden[i], orden[j]);
    }
  }
  cout << "\n===== PLAYLIST: " << get_nombre_playlist() << " =====\n";
  for (int i = 0; i < get_contador(); i++) {
    Nodo *actual = get_first();
    for (int j = 0; j < orden[i]; j++)
      actual = actual->siguiente;
    // Obtener anterior y siguiente
    Nodo *anterior_en_orden = actual->anterior;
    Nodo *siguiente_en_orden = actual->siguiente;
    if (aleatorio) { // calcular según el orden aleatorio
      if (i > 0) {
        anterior_en_orden = get_first();
        for (int j = 0; j < orden[i - 1]; j++)
          anterior_en_orden = anterior_en_orden->siguiente;
      } else if (is_loop()) { // Si es aleatorio Y circular el anterior del primero es el último
        anterior_en_orden = get_first();
        for (int j = 0; j < orden[get_contador() - 1]; j++)
          anterior_en_orden = anterior_en_orden->siguiente;
      }
      if (i < get_contador() - 1) {
        siguiente_en_orden = get_first();
        for (int j = 0; j < orden[i + 1]; j++)
          siguiente_en_orden = siguiente_en_orden->siguiente;
      } else if (is_loop()) { // Si es aleatorio Y circular el siguiente del último es el primero
        siguiente_en_orden = get_first();
        for (int j = 0; j < orden[0]; j++)
          siguiente_en_orden = siguiente_en_orden->siguiente;
      }
    }
    cout << "┌──────────────────────────────────────────────\n";
    cout << "│ #" << i << "  " << actual->nombre << " (" << actual << ")\n";
    cout << "├──────────────────────────────────────────────\n";
    cout << "│ ⏮ ";
    if (anterior_en_orden)
      cout << anterior_en_orden->nombre << " (" << anterior_en_orden << ")";
    else
      cout << "(No hay anterior)";
    cout << "\n";
    cout << "│ ⏭ ";
    if (siguiente_en_orden)
      cout << siguiente_en_orden->nombre << " (" << siguiente_en_orden << ")";
    else
      cout << "(No hay siguiente)";
    cout << "\n";
    cout << "└──────────────────────────────────────────────\n\n\n";
  }
  cout << "Total de canciones: " << get_contador() << "\n";
  cout << "🔁 " << (is_loop() ? "(Activado)" : "(Desactivado)") << endl;
  cout << "🔀 " << (aleatorio ? "(Activado)" : "(Desactivado)") << endl;
  cout << "===============================================\n\n";
  return 1;
}
