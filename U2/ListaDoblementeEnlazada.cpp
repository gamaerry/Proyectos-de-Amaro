#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sched.h>
#include <string>

using namespace std;

struct Nodo {
  string nombre;
  Nodo *siguiente;
  Nodo *anterior;
};

Nodo *primero = nullptr;
Nodo *ultimo = nullptr;
int contador = 0;
bool circular = false;

// Metodos de la Lista enlazada

// Métodos del main:

string nombre = "My new playlist";

void despedida() {
  if (clear())
    cout << "¡Lista no vacia! Se ha vaciado automáticamente" << endl;
  else
    cout << "¡Hasta pronto!" << endl;
}

string menu() {
  string loop = circular ?  "Quitar" : "Poner";
  return "\n" + nombre + "\n0. Cambiar nombre a la playlist\n 1. Llenar playlist\n 2. Ingresar a la playlist(before this track)\n 3. Ingresar a la playlist(after this track)\n 4. Eliminar de la playlist\n 5. Reproducir playlist\n 6. Limpiar playlist\n 7. " + loop + " playlist en bucle 8. Salir\n ";
}

string get_linea(string mensaje) {
  cout << mensaje;
  string linea;
  cin.ignore();
  getline(cin, linea);
  return linea;
}

Nodo *get_nuevo_elemento() {
  Nodo *nuevo = new Nodo;
  nuevo->nombre = get_linea("Ingrese nombre de la canción: ");
  return nuevo;
}

int get_int_valido(string mensaje) {
  cout << mensaje;
  int opcion;
  cin >> opcion;
  if (!cin) {
    cout << "¡No ingresó dígito válido! ";
    cin.clear();
    cin.ignore();
    return -1;
  }
  return opcion;
}

string indice_fuera_del_rango() {
  return "¡Índice fuera del rango! El rango actual de canciones es: [0, " + to_string(contador) + "]";
}

void manage_option(int opcion, int indice) {
  switch (opcion) {
  case 0:
    nombre = get_linea("Ingrese nuevo nombre: ");
  case 1:
    indice = get_int_valido("Ingrese el número de canciones a agregar: ");
    for (; indice > 0; indice--)
      insert(0, contador, get_nuevo_elemento());
  case 2:
    indice = get_int_valido("Ingrese el índice (iniciando del 0)");
    if (!insert(1, indice, get_nuevo_elemento())) // before
      cout << indice_fuera_del_rango();
    break;
  case 3:
    indice = get_int_valido("Ingrese el índice (iniciando del 0)");
    if (!insert(0, indice, get_nuevo_elemento())) // after
      cout << indice_fuera_del_rango();
    break;
  case 4:
    indice = get_int_valido("Ingrese el índice a eliminar (iniciando del 0)");
    if (!remove(indice))
      cout << indice_fuera_del_rango();
  case 5:
    if (!print())
      cout << "¡Lista vacia!";
    break;
  case 6:
    if (!clear())
      cout << "¡Lista vacia!";
    break;
  case 7:
    if (circular)
      enable_loop();
    else
      disable_loop();
  case 8:
    despedida();
    break;
  default:
    cout << "No se realizó ninguna operación" << endl;
  }
}

int main() {
  int opcion = 0;
  int indice = 0;
  do { // get_int_valido() siempre va a recibir un string para mostrar antes de pedir el int
    opcion = get_int_valido(menu());
    manage_option(opcion, indice);
  } while (opcion != 8);
  return 0;
}
