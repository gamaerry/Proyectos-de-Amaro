#include <iostream>

using namespace std;

int _multiplicar(int a, int b){
  if (b == 1)
    return a;
  else 
    return _multiplicar(a, b - 1) + a;
}

float _dividir(float a, float b){
  if (a == b)
    return 1;
  else
    return _dividir(a - b, b) + 1;
}

void imprimir_tabla(){
  int numero = 0;
  cout << "Ingrese la tabla a generar: ";
  cin >> numero;
  for(int i = 0; i < 10; i++){
    cout << numero << " x " << (i+1) << " = " << _multiplicar(numero, i+1) << endl;
  }
}

void multiplicacion_recursiva(){
  int a = 0, b = 0;
  cout << "Ingrese a: ";
  cin >> a;
  cout << "Ingrese b: ";
  cin >> b;
  cout << "a * b = " << _multiplicar(a, b) << endl;
}

void division_recursiva(){
  float a = 0, b = 0;
  cout << "Ingrese a: ";
  cin >> a;
  cout << "Ingrese b: ";
  cin >> b;
  cout << "a / b = " << _dividir(a, b) << endl;
}

int main(){
  int opcion = 0;
  cout << "Ingrese función requerida:\n 1) Imprimir tabla de multiplicar\n 2) División recursiva\n 3) Multiplicación recursiva" << endl;
  cin >> opcion;
  switch (opcion) {
    case 1:
      imprimir_tabla();
      break;
    case 2:
      division_recursiva();
      break;
    case 3:
      multiplicacion_recursiva();
      break;
    default:
      cout << "Opcion inválida. Terminando programa." << endl;
  }
  return 1;
}
