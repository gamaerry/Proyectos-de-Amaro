#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
  int arreglo[5];
  cout << arreglo << endl;
  for (int i = 0; i < 5; i++)
    arreglo[i] = i + 1;
  for (int i = 0; i < 5; i++)
    cout << i << ": " << arreglo[i] << " Dir:" << &arreglo[i] << endl;
  return 0;
}
