#include "LibreriaListaDoblementeEnlazada.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sched.h>
#include <string>

using namespace std;

void despedida() {
  if (clear())
    cout << "¡Playlist no vacia! Se ha vaciado automáticamente" << endl;
  else
    cout << "¡Hasta pronto!" << endl;
}

string menu() {
  string is_circular = is_loop() ? "Quitar" : "Poner";
  string is_aleatorio = is_random() ? "Quitar" : "Poner";
  string nombre = get_nombre_playlist();
  return "\n" + nombre + " (" + to_string(get_contador()) + " canciones)\n 1. Cambiar nombre a la playlist\n 2. Llenar playlist\n 3. Ingresar a la playlist(before this track)\n 4. Ingresar a la playlist(after this track)\n 5. Reproducir playlist\n 6. " + is_circular + " playlist en bucle " + (is_loop() ? "(Activado)" : "(Desactivado)") + " \n 7. " + is_aleatorio + " playlist en aleatorio " + (is_random() ? "(Activado)" : "(Desactivado)") + "\n 8. Eliminar de la playlist\n 9. Limpiar playlist\n 0. Salir\n ";
}

string get_linea(string mensaje) {
  cout << mensaje;
  string linea;
  getline(cin >> ws, linea);
  return linea;
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

string rango() {
  int canciones_actuales = get_contador() - 1;
  return "[0, " + (canciones_actuales < 0 ? "0" : to_string(canciones_actuales)) + "]";
}

void manage_option(int opcion, int indice) {
  switch (opcion) {
  case 1:
    set_nombre_playlist(get_linea("Ingrese nuevo nombre: ").c_str());
    break;
  case 2:
    indice = get_int_valido("Ingrese el número de canciones a agregar: ");
    if (indice < 0)
      break;
    for (; indice > 0; indice--)
      insert(false, get_contador() - 1, get_linea("Ingrese nombre de la canción: ").c_str());
    break;
  case 3:
    indice = get_int_valido("Ingrese el índice " + rango() + ": ");
    if (indice < 0)
      break;
    if (!insert(true, indice, get_linea("Ingrese nombre de la canción: ").c_str())) // before
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 4:
    indice = get_int_valido("Ingrese el índice " + rango() + ": ");
    if (indice < 0)
      break;
    if (!insert(false, indice, get_linea("Ingrese nombre de la canción: ").c_str())) // after
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 5:
    if (!play())
      cout << "¡Playlist vacía!";
    break;
  case 6:
    if (is_loop()) // note que si la playlist está vacía, esto no efectua ningún cambio
      disable_loop();
    else
      enable_loop();
    break;
  case 7:
    set_random(!is_random());
    break;
  case 8:
    indice = get_int_valido("Ingrese el índice a eliminar " + rango() + ": ");
    if (indice < 0)
      break;
    if (!remove_in(indice))
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 9:
    if (!clear())
      cout << "¡Playlist vacía!";
    break;
  case 0:
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
  } while (opcion != 0);
  return 0;
}
