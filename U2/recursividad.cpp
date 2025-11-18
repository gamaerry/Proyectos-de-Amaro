#include <iostream>

using namespace std;

int fibonacci(int actual){
  if(actual == 0 || actual == 1){
    return 1;
  } else {
    return fibonacci(actual-1)+fibonacci(actual-2);
  }
}

int main(){
  int terminos = 0;
  cout << "Ingrese número de términos fibonacci: ";
  cin >> terminos;
  for(int i = 0; i<terminos; i++){
    cout << fibonacci(i) << ", ";
  }
  cout << endl;
  return 1;
}
