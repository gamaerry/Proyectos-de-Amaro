#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
  int valor;
  Nodo *menor;
  Nodo *mayor;
};

int nivel_actual = 0;

// Métodos del arbol

Nodo *newNodo(int valor) {
  Nodo *nuevo = new Nodo;
  nuevo->valor = valor;
  cout << valor << ", ";
  nuevo->menor = NULL;
  nuevo->mayor = NULL;
  return nuevo;
}

void printNodo(Nodo *raiz) {
  if (raiz) {
    string menor = "", mayor = "";
    if (raiz->menor)
      menor = to_string(raiz->menor->valor);
    if (raiz->mayor)
      mayor = to_string(raiz->mayor->valor);
    cout << "\n(NIVEL " << nivel_actual++ << ") [" << raiz << "]: " << raiz->valor << "\n(MENOR) [" << raiz->menor << "]: " << menor << " ~ (MAYOR) [" << raiz->mayor << "]: " << mayor << endl;
    printNodo(raiz->menor);
    printNodo(raiz->mayor);
  }
}

// Métodos del main

int get_aleatorio() {
  return rand() % 100;
}

int main() {
  srand(time(NULL));
  int numero_de_nodos, valor_aleatorio = get_aleatorio();
  cout << "Ingrese el número de nodos: ";
  cin >> numero_de_nodos;
  cout << "Números generados: ";
  Nodo *raiz = newNodo(valor_aleatorio);
  Nodo *actual = raiz;
  for (int i = 1; i < numero_de_nodos; i++) {
    valor_aleatorio = get_aleatorio();
    if (valor_aleatorio <= actual->valor) {
      actual->menor = newNodo(valor_aleatorio);
      actual = actual->menor;
    } else {
      actual->mayor = newNodo(valor_aleatorio);
      actual = actual->mayor;
    }
  }
  cout << endl;
  printNodo(raiz);
  return 0;
}
