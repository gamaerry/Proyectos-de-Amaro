#include <bits/stdc++.h>
using namespace std;

struct Persona {
  string nombre;
  int edad;
  float estatura;
} person; // truco de cpp: de esta manera se crean variables globales con ese
          // nombre

int main() {
  Persona persona;
  persona.nombre = "Gera";
  persona.edad = 25;
  persona.estatura = 1.70;
  string nombre = "Gera";
  cout << "Hola " << persona.nombre << endl;

  int x = 10;
  int *puntero = &x;
  x = 20; // esta linea cambia tanto a x como a *puntero

  // Esto:
  cout << puntero << endl;
  cout << *puntero << endl;
  // es equivalente a:
  cout << &x << endl;
  cout << x << endl;

  return 0;
}
