#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sched.h>
#include <string>
#include <vector>

using namespace std;

struct Nodo {
  string nombre;
  Nodo *siguiente;
  Nodo *anterior;
};

Nodo *primero = nullptr;
int contador = 0;
bool circular = false;

// Metodos de la Lista enlazada

Nodo *get_last() {
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
    circular = false;
  }
}

void enable_loop() {
  if (contador > 0) {
    Nodo *ultimo = get_last();
    primero->anterior = ultimo;
    ultimo->siguiente = primero;
    circular = true;
  }
}

bool insert(bool before, int indice, Nodo *nuevo) {
  if (indice > contador)
    return false;
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
  return true;
}

bool remove(int indice) {
  if (indice > contador || contador == 0)
    return false;
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
  return true;
}

bool clear() {
  if (contador == 0)
    return false;
  while (remove(0))
    ;
  return true;
}

// Métodos del main:

string nombre = "My new playlist";
bool aleatorio = false;

bool reproducir() {
  if (contador == 0)
    return false;

  vector<int> orden;
  for (int i = 0; i < contador; i++)
    orden.push_back(i);
  if (aleatorio) {
    // Mezclar el vector usando Fisher-Yates shuffle
    for (int i = contador - 1; i > 0; i--) {
      int j = rand() % (i + 1);
      swap(orden[i], orden[j]);
    }
  }

  cout << "\n===== PLAYLIST: " << nombre << " =====\n";
  for (int i = 0; i < contador; i++) {
    Nodo *actual = primero;
    for (int j = 0; j < orden[i]; j++)
      actual = actual->siguiente;

    // Obtener anterior y siguiente
    Nodo *anterior_en_orden = actual->anterior;
    Nodo *siguiente_en_orden = actual->siguiente;

    if (aleatorio) { // calcular según el orden aleatorio
      if (i > 0) {
        anterior_en_orden = primero;
        for (int j = 0; j < orden[i - 1]; j++)
          anterior_en_orden = anterior_en_orden->siguiente;
      } else if (circular) { // Si es aleatorio Y circular el anterior del primero es el último
        anterior_en_orden = primero;
        for (int j = 0; j < orden[contador - 1]; j++)
          anterior_en_orden = anterior_en_orden->siguiente;
      }
      if (i < contador - 1) {
        siguiente_en_orden = primero;
        for (int j = 0; j < orden[i + 1]; j++)
          siguiente_en_orden = siguiente_en_orden->siguiente;
      } else if (circular) { // Si es aleatorio Y circular el siguiente del último es el primero
        siguiente_en_orden = primero;
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
  cout << "Total de canciones: " << contador << "\n";
  cout << "🔁 " << (circular ? "(Activado)" : "(Desactivado)") << endl;
  cout << "🔀 " << (aleatorio ? "(Activado)" : "(Desactivado)") << endl;
  cout << "===============================================\n\n";
  return true;
}

void despedida() {
  if (clear())
    cout << "¡Playlist no vacia! Se ha vaciado automáticamente" << endl;
  else
    cout << "¡Hasta pronto!" << endl;
}

string menu() {
  string is_loop = circular ? "Quitar" : "Poner";
  string is_random = aleatorio ? "Quitar" : "Poner";
  return "\n" + nombre + " (" + to_string(contador) + " canciones)\n 1. Cambiar nombre a la playlist\n 2. Llenar playlist\n 3. Ingresar a la playlist(before this track)\n 4. Ingresar a la playlist(after this track)\n 5. Reproducir playlist\n 6. " + is_loop + " playlist en bucle " + (circular ? "(Activado)" : "(Desactivado)") + " \n 7. " + is_random + " playlist en aleatorio " + (aleatorio ? "(Activado)" : "(Desactivado)") + "\n 8. Eliminar de la playlist\n 9. Limpiar playlist\n 0. Salir\n ";
}

string get_linea(string mensaje) {
  cout << mensaje;
  string linea;
  getline(cin >> ws, linea);
  return linea;
}

Nodo *get_nuevo_elemento() {
  Nodo *nuevo = new Nodo;
  nuevo->nombre = get_linea("Ingrese nombre de la canción: ");
  nuevo->anterior = nullptr;
  nuevo->siguiente = nullptr;
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

string rango() {
  return "[0, " + to_string(contador - 1) + "]";
}

void manage_option(int opcion, int indice) {
  switch (opcion) {
  case 1:
    nombre = get_linea("Ingrese nuevo nombre: ");
    break;
  case 2:
    indice = get_int_valido("Ingrese el número de canciones a agregar: ");
    if (indice < 0)
      break;
    for (; indice > 0; indice--)
      insert(false, contador - 1, get_nuevo_elemento());
    break;
  case 3:
    indice = get_int_valido("Ingrese el índice" + rango() + ":");
    if (indice < 0)
      break;
    if (!insert(true, indice, get_nuevo_elemento())) // before
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 4:
    indice = get_int_valido("Ingrese el índice" + rango() + ":");
    if (indice < 0)
      break;
    if (!insert(false, indice, get_nuevo_elemento())) // after
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 8:
    indice = get_int_valido("Ingrese el índice a eliminar" + rango() + ":");
    if (indice < 0)
      break;
    if (!remove(indice))
      cout << "¡Índice fuera del rango! El rango de índices actual es: " + rango();
    break;
  case 5:
    if (!reproducir())
      cout << "¡Playlist vacía!";
    break;
  case 9:
    if (!clear())
      cout << "¡Playlist vacía!";
    break;
  case 6:
    if (circular) // note que si la playlist está vacía, esto no efectua ningún cambio
      disable_loop();
    else
      enable_loop();
    break;
  case 7:
    aleatorio = !aleatorio;
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
