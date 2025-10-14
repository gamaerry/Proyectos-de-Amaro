#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

typedef struct Cola {
  struct Cola *anterior;
  string nombre;
} Cola;

Cola *primero = NULL;

Cola *newCola(string nombre) {
  Cola *nueva = new Cola;
    // malloc(sizeof(Cola) + strlen(nombre) + 1);
  nueva->anterior = NULL;
  nueva->nombre = nombre;
  return nueva;
}

Cola *get_last() {
  Cola *ultimo = primero;
  if (primero)
    while (ultimo->anterior != primero)
      ultimo = ultimo->anterior;
  return ultimo;
}

void enqueue(Cola *nuevo) { // formar un nuevo en la cola
  if (primero) {
    Cola *ultimo = get_last();
    nuevo->anterior = primero;
    ultimo->anterior = nuevo;
  } else {
    primero = nuevo;
    primero->anterior = primero;
  }
}

Cola *dequeue() {
  if (!primero)
    return NULL;
  Cola *por_salir = primero;
  if (primero->anterior == primero)
    primero = NULL;
  else {
    primero = primero->anterior;
    get_last()->anterior = primero;
  }
  return por_salir;
}

int clear() {
  if (primero) {
    Cola *a_limpiar;
    do {
      a_limpiar = dequeue();
      free(a_limpiar);
    } while (primero);
    return 1;
  } else
    return 0;
}

int print() {
  if (primero) {
    Cola *actual = primero;
    do {
      cout << actual << actual->nombre;
      cout << "Adelante de " << (actual->anterior ? actual->anterior->nombre : "ninguno") << "\n";
      actual = actual->anterior;
    } while(actual != primero);
    return 1;
  } else
    return 0;
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
