#include "Fruta.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

const string MSJ_PEDIR_NOMBRE = "Ingrese el nombre de la fruta: ";

Fruta *push(Fruta *ultima_fruta) {
  Fruta *nueva_fruta = (Fruta *)malloc(sizeof(Fruta));
  cout << MSJ_PEDIR_NOMBRE;
  cin.ignore();
  cin.getline(nueva_fruta->nombre, TAMANO_MAXIMO);
  nueva_fruta->fruta_trasera = ultima_fruta;
  return nueva_fruta;
}

Fruta *pop(Fruta *ultima_fruta) {
  Fruta *penultima_fruta = ultima_fruta->fruta_trasera;
  free(ultima_fruta);
  // delete ultima_fruta; // es mejor usar delete?
  return penultima_fruta;
}

Fruta *clear(Fruta *ultima_fruta) {
  while (ultima_fruta != nullptr)
    ultima_fruta = pop(ultima_fruta);
  return nullptr;
}

bool is_empty(Fruta *ultima_fruta) {
  return !ultima_fruta;
}

void show(Fruta *ultima_fruta) {
  Fruta *a_mostrar = ultima_fruta;
  cout << "======================================" << endl;
  while (a_mostrar != nullptr) {
    cout << "‖" << endl;
    cout << "‖ Nombre de la fruta: " << a_mostrar->nombre << endl;
    cout << "‖ Direccion en memoria: " << a_mostrar << endl;
    cout << "‖" << endl;
    cout << "‖ (Encima de " << (a_mostrar->fruta_trasera ? a_mostrar->fruta_trasera->nombre : "ninguno") << ")" <<endl;
    cout << "======================================" << endl;
    a_mostrar = a_mostrar->fruta_trasera;
  }
}
