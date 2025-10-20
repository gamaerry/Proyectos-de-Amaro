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
  for (int i = 0; i < contador; i++)
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
  Nodo *a_modificar = primero;
  for (int i = 0; i < indice; i++)
    a_modificar = a_modificar->siguiente;
  Nodo *anterior = a_modificar->anterior;
  Nodo *siguiente = a_modificar->siguiente;
  if (anterior && before) {
    anterior->siguiente = nuevo;
    nuevo->anterior = anterior;
    a_modificar->anterior = nuevo;
    nuevo->siguiente = a_modificar;
  }
  if (siguiente && !before) {
    siguiente->anterior = nuevo;
    nuevo->siguiente = siguiente;
    a_modificar->siguiente = nuevo;
    nuevo->anterior = a_modificar;
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
  if (anterior) {
    anterior->siguiente = siguiente;
    actual->anterior = nullptr;
  }
  if (siguiente) {
    siguiente->anterior = anterior;
    actual->siguiente = nullptr;
  }
  contador--;
  return true;
}

bool clear() {
  if (contador == 0)
    return false;
  Nodo *actual = primero;
  while (actual) {
    Nodo *siguiente = actual->siguiente;
    actual->anterior = nullptr;
    actual->siguiente = nullptr;
    delete actual;
    actual = siguiente;
  }
  primero = nullptr;
  contador = 0;
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
    cout << "┌──────────────────────────────────────────────\n";
    cout << "│ #" << i << "  " << actual->nombre << " (" << actual << ")\n";
    cout << "├──────────────────────────────────────────────\n";
    cout << "│ ⏮ ";
    if (actual->anterior)
      cout << actual->anterior->nombre << " (" << actual->anterior << ")";
    else
      cout << "(No hay anterior)";
    cout << "\n";
    cout << "│ ⏭ ";
    if (actual->siguiente)
      cout << actual->siguiente->nombre << " (" << actual->siguiente << ")";
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
  return "\n" + nombre + "\n0. Cambiar nombre a la playlist\n 1. Llenar playlist\n 2. Ingresar a la playlist(before this track)\n 3. Ingresar a la playlist(after this track)\n 4. Eliminar de la playlist\n 5. Reproducir playlist\n 6. Limpiar playlist\n 7. " + is_loop + " playlist en bucle\n 8. " + is_random + " playlist en aleatorio\n 9. Salir\n ";
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
    if (indice < 0)
      break;
    for (; indice > 0; indice--)
      insert(false, contador, get_nuevo_elemento());
  case 2:
    indice = get_int_valido("Ingrese el índice (iniciando del 0)");
    if (indice < 0)
      break;
    if (!insert(true, indice, get_nuevo_elemento())) // before
      cout << indice_fuera_del_rango();
    break;
  case 3:
    indice = get_int_valido("Ingrese el índice (iniciando del 0)");
    if (indice < 0)
      break;
    if (!insert(false, indice, get_nuevo_elemento())) // after
      cout << indice_fuera_del_rango();
    break;
  case 4:
    indice = get_int_valido("Ingrese el índice a eliminar (iniciando del 0)");
    if (indice < 0)
      break;
    if (!remove(indice))
      cout << indice_fuera_del_rango();
  case 5:
    if (!reproducir())
      cout << "¡Playlist vacía!";
    break;
  case 6:
    if (!clear())
      cout << "¡Playlist vacía!";
    break;
  case 7:
    if (circular) // note que si la playlist está vacía, esto no efectua ningún cambio
      disable_loop();
    else
      enable_loop();
    break;
  case 8:
    aleatorio = !aleatorio;
    break;
  case 9:
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
  } while (opcion != 9);
  return 0;
}
