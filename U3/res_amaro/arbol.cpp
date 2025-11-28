#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

using namespace std;

struct Node {
  int value;
  Node *left;
  Node *right;
};

Node *mainRoot;
int contador1 = 0;
int contador2 = 0;
int contador3 = 0;

void insert(Node *&root, int value) {
  if (root == NULL) {
    root = new Node;
    root->value = value;
    root->left = NULL;
    root->right = NULL;
  } else if (value < root->value)
    insert(root->left, value);
  else if (value > root->value)
    insert(root->right, value);
}

void preoOrder(Node *root) {
  if (root != NULL) {
    cout << "[" << root << "] Value: " << root->value << endl;
    preoOrder(root->left);
    preoOrder(root->right);
  }
}

void inOrder(Node *root) {
  if (root != NULL) {
    inOrder(root->left);
    cout << "[" << root << "] Value: " << root->value << endl;
    inOrder(root->right);
  }
}

void postOrder(Node *root) {
  if (root != NULL) {
    postOrder(root->left);
    postOrder(root->right);
    cout << "[" << root << "] Value: " << root->value << endl;
  }
}

void print(Node *root) {
  cout << "\n\t[" << root << "] Value: " << root->value << endl;
  if (root->left != NULL)
    cout << "L: [" << root->left << "] Value: " << root->left->value;
  if (root->right != NULL)
    cout << "\t\tR: [" << root->right << "] Value: " << root->right->value << endl;
}

void busquedaPreorder(int n, Node *root) {
  if (root != NULL) {
    // cout << "[" << root << "] Value: " << root->value << endl;
    contador1++;
    if (n == root->value) {
      cout << "Numero de iteraciones preorder: " << contador1 << endl;
      return;
    }
    busquedaPreorder(n, root->left);
    busquedaPreorder(n, root->right);
  }
}

void busquedaInorder(int n, Node *root) {
  if (root != NULL) {
    // cout << "[" << root << "] Value: " << root->value << endl;
    contador2++;
    busquedaInorder(n, root->left);
    if (n == root->value) {
      cout << "Numero de iteraciones inorder: " << contador2 << endl;
      return;
    }
    busquedaInorder(n, root->right);
  }
}

void busquedaPostorder(int n, Node *root) {
  if (root != NULL) {
    contador3++;
    busquedaPostorder(n, root->left);
    busquedaPostorder(n, root->right);
    if (n == root->value) {
      cout << "Numero de iteraciones postorder: " << contador3 << endl;
      print(root);
      return;
    }
  }
}
int main() {
  srand(time(NULL));

  cout << "Ingrese el valor de la raiz del arbol: ";
  mainRoot = new Node;
  mainRoot->left = NULL;
  mainRoot->right = NULL;
  cin >> mainRoot->value;

  int n, value;
  cout << "Ingrese el numero de valores a insertar: ";
  cin >> n;
  for (int i = 0; i < n; i++) {
    value = rand() % 100;
    insert(mainRoot, value);
  }

  int opcion = 0;
  cout << "Ingrese en que orden: (0 Preorder, 1 Inorder, 2 Postorder): " << endl;
  cin >> opcion;
  switch (opcion) {
  case 0:
    cout << "\nPreorder: " << endl;
    preoOrder(mainRoot);
    break;
  case 1:
    cout << "\nInorder: " << endl;
    inOrder(mainRoot);
    break;
  case 2:
    cout << "\nPostorder: " << endl;
    postOrder(mainRoot);
    break;
  default:
    cout << "\nOrden no correcto (no imprimio)" << endl;
    return 0;
  }
  cout << "Ingrese la busqueda" << endl;
  int busqueda;
  cin >> busqueda;
  busquedaPreorder(busqueda, mainRoot);
  busquedaInorder(busqueda, mainRoot);
  busquedaPostorder(busqueda, mainRoot);
}
