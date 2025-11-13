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
int numero_de_nodos = 0;

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

int objeto_encontrado = -1;

void busqueda_binaria(Nodo* raiz, int a_buscar) {
  if(raiz && nivel_actual < numero_de_nodos){
    nivel_actual++;
    if (raiz->valor == a_buscar) {
      objeto_encontrado = nivel_actual;
    } else {
      busqueda_binaria(raiz->menor, a_buscar);
      busqueda_binaria(raiz->mayor, a_buscar);
    }
  }
}

// Métodos del main

int get_aleatorio() {
  return rand() % 100;
}

Nodo* llenar_arbol() {
  int valor_aleatorio = get_aleatorio();
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
  return raiz;
}

void buscar_numero(Nodo* raiz) {
  int a_buscar;
  cout << "Ingrese número a buscar: ";
  cin >> a_buscar;
  busqueda_binaria(raiz, a_buscar);
  if (objeto_encontrado < 0)
    cout << "¡Objeto no encontrado!";
  else
    cout << "¡Objeto encontrado en el nivel " << (objeto_encontrado - 1) << "!";
}

void imprimir_arbol(Nodo* raiz) {
  cout << endl;
  nivel_actual = 0;
  printNodo(raiz);
  nivel_actual = 0;
}

int main() {
  Nodo* raiz;
  srand(time(NULL));
  raiz = llenar_arbol();
  buscar_numero(raiz);
  imprimir_arbol(raiz);
  return 0;
}
