#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct Nodo {
  string nombre;
  Nodo *siguiente;
};

Nodo *primero;
int contador;

// Metodos de la Lista enlazada

int insert(int before, int indice, Nodo *nuevo) {
  if (indice > contador || indice < 0) {
    return 1;
  } else if (indice == 0) {
    nuevo->siguiente = primero;
    primero = nuevo;
    contador++;
    return 0;
  } else {
    Nodo *a_modificar = primero;
    Nodo *a_apuntar = primero->siguiente;
    for (int i = 0; i < (indice - before); i++) {
      a_modificar = a_modificar->siguiente;
      a_apuntar = a_modificar->siguiente;
    }
    a_modificar->siguiente = nuevo;
    nuevo->siguiente = a_apuntar;
    contador++;
    return 0;
  }
}

bool clear() {
  if (!primero)
    return false;
  Nodo *actual = primero;
  while (actual) {
    Nodo *siguiente = actual->siguiente;
    delete actual;
    actual = siguiente;
  }
  primero = nullptr;
  contador = 0;
  return true;
}

bool print() {
  if (!primero) {
    return false;
  }
  Nodo *actual = primero;
  int i = 1;
  while (actual) {
    cout << actual->nombre << '\n';
    actual = actual->siguiente;
  }
  return true;
}

// Métodos del main:

void despedida() {
  if (clear())
    cout << "¡Lista no vacia! Se ha vaciado automáticamente" << endl;
  else
    cout << "¡Hasta pronto!" << endl;
}

void mostrar_menu() {
  cout << "\nIngrese opcion: " << endl;
  cout << "1. Ingresar elemento a la lista (before)" << endl;
  cout << "2. Ingresar elemento a la lista (after)" << endl;
  cout << "3. Mostrar la lista" << endl;
  cout << "4. Limpiar lista" << endl;
  cout << "5. Salir" << endl;
}

Nodo *get_nuevo_elemento() {
  Nodo *nuevo = new Nodo;
  nuevo->siguiente = nullptr;
  cout << "Ingrese nombre del nuevo elemento: ";
  cin.ignore();
  getline(cin, nuevo->nombre);
  return nuevo;
}

int recibir_opcion_valida() {
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

void init_lista() {
  for (int i = 1; i <= 5; i++) {
    Nodo *nuevo = new Nodo;
    nuevo->nombre = "nodo " + to_string(i);
    nuevo->siguiente = nullptr;

    // Insertar al final usando tu función insert()
    insert(1, contador, nuevo);
  }
  cout << "Se han cargado 5 nodos por defecto.\n";
}

int main() {
  init_lista();
  int opcion;
  int indice = 0;
  do {
    mostrar_menu();
    opcion = recibir_opcion_valida();
    switch (opcion) {
    case 1:
      cout << "Ingrese el indice:";
      indice = recibir_opcion_valida();
      insert(1, indice, get_nuevo_elemento()); // before
      break;
    case 2:
      indice = recibir_opcion_valida();
      insert(0, indice, get_nuevo_elemento()); // after
      break;
    case 3:
      if (!print())
        cout << "¡Lista vacia!";
      break;
    case 4:
      if (!clear())
        cout << "!Lista vacia!";
      break;
    case 5:
      despedida();
      break;
    default:
      cout << "No se realizó ninguna operación" << endl;
    }
  } while (opcion != 5);
  return 0;
}
