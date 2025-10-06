#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

struct Cola {
  std::string nombre;
  Cola *anterior;
};

Cola *primero;

// Métodos de la cola:

void enqueue(Cola *nuevo) { // formar un nuevo en la cola
  if (primero) {
    Cola *ultimo = primero;
    while (ultimo->anterior)
      ultimo = ultimo->anterior;
    ultimo->anterior = nuevo;
  } else
    primero = nuevo;
}

Cola *dequeue() { // sacar al primero de la cola
  Cola *por_salir = primero;
  primero = primero ? primero->anterior : nullptr;
  return por_salir;
}

bool clear() {
  if (primero) {
    Cola *a_limpiar;
    do {
      a_limpiar = dequeue();
      delete a_limpiar;
    } while (primero);
    return true;
  } else
    return false;
}

bool print() {
  if (primero) {
    Cola *actual = primero;
    while (actual != nullptr) {
      cout << "[" << actual << "]: " << actual->nombre << endl;
      cout << "(Adelante de " << (actual->anterior ? actual->anterior->nombre : "ninguno") << ")\n\n";
      actual = actual->anterior;
    }
    return true;
  } else
    return false;
}

// Métodos del main:

void despedida() {
  if (clear())
    cout << "¡Cola no vacia! Se ha vaciado automáticamente" << endl;
  else
    cout << "¡Hasta pronto!" << endl;
}

void mostrar_menu() {
  cout << "\nIngrese opcion: " << endl;
  cout << "1. Ingresar elemento a la cola" << endl;
  cout << "2. Mostrar la cola" << endl;
  cout << "3. Quitar el primer elemento" << endl;
  cout << "4. Limpiar cola" << endl;
  cout << "5. Salir" << endl;
}

Cola *get_nuevo_elemento() {
  Cola *nuevo = new Cola;
  nuevo->anterior = nullptr;
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
  }
  return opcion;
}

int main() {
  int opcion;
  do {
    mostrar_menu();
    opcion = recibir_opcion_valida();
    switch (opcion) {
    case 1:
      enqueue(get_nuevo_elemento());
      break;
    case 2:
      if (!print())
        cout << "¡Cola vacia!";
      break;
    case 3:
      delete dequeue();
      break;
    case 4:
      if (!clear())
        cout << "!Cola vacia!";
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
