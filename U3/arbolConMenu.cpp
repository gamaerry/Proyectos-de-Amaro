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

  cout << "\nPreorder: " << endl;
  preoOrder(mainRoot);

  cout << "\nInorder: " << endl;
  inOrder(mainRoot);

  cout << "\nPostorder: " << endl;
  postOrder(mainRoot);

  return 0;
}
