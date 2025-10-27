#include <cstdlib>
#include <iostream>

using namespace std;

struct Nodo {
  string cancion;
  Nodo *sig, *ant;
};

Nodo *primero, *ultimo;
int total = 0;

void agregar() {
  total++;
  Nodo *nuevo = new Nodo;
  cout << "Introduce la cancion: ";
  getline(cin >> ws, nuevo->cancion);
  nuevo->sig = NULL;
  nuevo->ant = NULL;

  if (primero == NULL) {
    primero = nuevo;
    ultimo = nuevo;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
  } else {
    ultimo->sig = nuevo;
    nuevo->sig = NULL;
    nuevo->ant = ultimo;
    ultimo = nuevo;
  }
}

void imprimir() {
  Nodo *aux = primero;
  while (aux != NULL) {
    cout << " | " << aux->ant << " |\t" << aux->cancion << " (" << aux << ")" << "\t| " << aux->sig << " | " << endl;
    aux = aux->sig;
  }
  cout << "\n\tElementos: " << total << "\n"
       << endl;
}

void llenar(int n) {
  for (int i = 0; i < n; i++) {
    agregar();
  }
  imprimir();
}

void vaciar() {
  Nodo *aux = primero;
  while (aux != NULL) {
    Nodo *temp = aux;
    aux = aux->sig;
    delete temp;
  }
  primero = NULL;
  ultimo = NULL;
  total = 0;

  cout << "\nLista vacia\n"
       << endl;
}

void menu() {
  int opcion = 4;
  do {
    cout << "\nMenu" << endl;
    cout << "1. Llenar" << endl;
    cout << "2. Agregar" << endl;
    cout << "3. Imprimir" << endl;
    cout << "4. Vaciar" << endl;
    cout << "5. Salir" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cin.ignore();
    if (opcion == 1) {
      int numElementos = 0;
      cout << "Ingrese la cantidad de elementos a llenar: ";
      cin >> numElementos;
      llenar(numElementos);
    } else if (opcion == 2) {
      agregar();
    } else if (opcion == 3) {
      imprimir();
    } else if (opcion == 4) {
      vaciar();
    } else if (opcion == 5) {
      if (total == 0) {
        cout << "Lista vacia" << endl;
        break;
      } else {
        cout << "Lista no vacia" << endl;
      }
    }

  } while (true);
}

int main() {
  menu();

  return 0;
}
