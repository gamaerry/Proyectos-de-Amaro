#include <iostream>
#include <vector>

using namespace std;

// Struct para representar un nodo del grafo
struct Node {
  // Valor del vértice (un numero entero)
  int dato;
  // Puntero al siguiente vecino en la lista de adyacencia
  Node *next;
  Node(int valor) {
    dato = valor;
    next = nullptr;
  }
};

int ponderaciones[5][5];

// Clase Grafo
class Grafo {

private:
  // Número de vértices
  int V;
  // Arreglo de punteros a listas enlazadas (para tener listas de adyacencia)
  Node **listAdj;

public:
  // Constructor: crea un grafo con V vértices (0 a V-1)
  Grafo(int vertices) {
    V = vertices;
    // Arreglo de punteros a listas enlazadas (con tamaño V)
    listAdj = new Node *[V];

    for (int i = 0; i < V; i++) {
      // Cada lista empieza vacía
      listAdj[i] = nullptr;
    }
  }

  // Agregar una arista no dirigida entre u y v
  void agregarArista(int u, int v, int peso) {
    // Agregar v a la lista de u
    Node *nuevo = new Node(v);
    nuevo->next = listAdj[u];
    listAdj[u] = nuevo;
    ponderaciones[u][v]=peso;
    // Agregar u a la lista de v (porque es no dirigido)
    // nuevo = new Node(u);
    // nuevo->next = listAdj[v];
    // listAdj[v] = nuevo;
  }

  // Imprimir el grafo (lista de adyacencia)
  void imprimir() {
    cout << "Lista de adyacencia del grafo:\n";
    for (int i = 0; i < V; i++) {
      cout << i << " -> ";
      Node *actual = listAdj[i];
      while (actual != nullptr) {
        cout << actual->dato << " (" << ponderaciones[i][actual->dato] << ") ";
        actual = actual->next;
      }
      cout << endl;
    }
  }

  // Destructor para liberar memoria
  ~Grafo() {
    for (int i = 0; i < V; i++) {
      Node *actual = listAdj[i];
      while (actual != nullptr) {
        Node *aux = actual;
        actual = actual->next;
        delete aux;
      }
    }
    delete[] listAdj;
    cout << "Memoria liberada correctamente.\n";
  }
};

// Main
int main() {
  cout << "=== Ejemplo sencillo de Grafo con punteros en C++ ===\n\n";

  // Grafo con 5 vértices (0,1,2,3,4)
  Grafo g(5);

  // Agregamos algunas aristas
  g.agregarArista(0, 1, 30);
  g.agregarArista(0, 4, 20);
  g.agregarArista(1, 2, 10);
  g.agregarArista(1, 3, 5);
  g.agregarArista(1, 4, 20);
  g.agregarArista(2, 3, 40);
  g.agregarArista(3, 4, 60);

  // Imprimimos el grafo
  g.imprimir();

  return 0;
}
