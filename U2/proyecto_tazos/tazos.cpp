#include <cstdlib>
#include <iostream>
#include <new>
#include <string>
extern unsigned char tazo10_txt[];
extern unsigned int tazo10_txt_len;
extern unsigned char tazo9_txt[];
extern unsigned int tazo9_txt_len;
extern unsigned char tazo8_txt[];
extern unsigned int tazo8_txt_len;
extern unsigned char tazo7_txt[];
extern unsigned int tazo7_txt_len;
extern unsigned char tazo6_txt[];
extern unsigned int tazo6_txt_len;
extern unsigned char tazo5_txt[];
extern unsigned int tazo5_txt_len;
extern unsigned char tazo4_txt[];
extern unsigned int tazo4_txt_len;
extern unsigned char tazo3_txt[];
extern unsigned int tazo3_txt_len;
extern unsigned char tazo2_txt[];
extern unsigned int tazo2_txt_len;
extern unsigned char tazo1_txt[];
extern unsigned int tazo1_txt_len;

using namespace std;

struct Tazo {
  string name;
  string type;
  int value;
  Tazo *bottom;
};

int restantes = 0;
int puntaje_actual = 0;

Tazo *push(Tazo *last, string name, string type, int value) {
  Tazo *newTazo = new Tazo;
  restantes++;
  newTazo->name = name;
  newTazo->type = type;
  newTazo->value = value;
  newTazo->bottom = last;
  return newTazo;
}

Tazo *pop(Tazo *last) {
  restantes--;
  Tazo *newLast = last->bottom;
  cout << "("<< last->type << ") ";
  puntaje_actual += last->value;
  delete last;
  return newLast;
}

void print() {
  switch (restantes) {
  case 10:
    printf("%.*s\n", tazo10_txt_len, tazo10_txt);
    break;
  case 9:
    printf("%.*s\n", tazo9_txt_len, tazo9_txt);
    break;
  case 8:
    printf("%.*s\n", tazo8_txt_len, tazo8_txt);
    break;
  case 7:
    printf("%.*s\n", tazo7_txt_len, tazo7_txt);
    break;
  case 6:
    printf("%.*s\n", tazo6_txt_len, tazo6_txt);
    break;
  case 5:
    printf("%.*s\n", tazo5_txt_len, tazo5_txt);
    break;
  case 4:
    printf("%.*s\n", tazo4_txt_len, tazo4_txt);
    break;
  case 3:
    printf("%.*s\n", tazo3_txt_len, tazo3_txt);
    break;
  case 2:
    printf("%.*s\n", tazo2_txt_len, tazo2_txt);
    break;
  case 1:
    printf("%.*s\n", tazo1_txt_len, tazo1_txt);
    break;
  }
}

Tazo *fill() {
  Tazo *last = nullptr;
  last = push(last, "Tazo1", "Normal", 1);
  last = push(last, "Tazo2", "Normal", 1);
  last = push(last, "Tazo3", "Dorado", 3);
  last = push(last, "Tazo4", "Plateado", 2);
  last = push(last, "Tazo5", "Normal", 1);
  last = push(last, "Tazo6", "Plateado", 2);
  last = push(last, "Tazo7", "Normal", 1);
  last = push(last, "Tazo8", "Normal", 1);
  last = push(last, "Tazo9", "Dorado", 3);
  last = push(last, "Tazo10", "Normal", 1);
  return last;
}

void jugar(Tazo *last) {
  int scores[2] = {};
  int actual = 1;
  int random;
  print();
  while (last != nullptr) {
    puntaje_actual = 0;
    random = rand() % 6;
    actual = (actual + 1) % 2;
    cout << "\n(" << restantes << " tazos restantes) Turno del Jugador " << (actual + 1) << " (Enter)";
    getchar();
    system("clear");
    cout << "Resultado del jugador " << (actual + 1) << ": ";
    if (random == 0 || random == 5)
      cout << "(*o*) Tiro fallido ++0 tazos" << endl;
    else if (random == 3 && restantes > 3) {
      cout << "(^_^) Tiro critico ++3 tazos" << endl;
      last = pop(last);
      last = pop(last);
      last = pop(last);
    } else {
      cout << "('-') Tiro acertado ++1 tazo" << endl;
      last = pop(last);
    }
    cout << endl;
    print();
    scores[actual] += puntaje_actual;
    cout << "\tMARCADOR ACTUAL\nJugador1: " << scores[0] << "pts \nJugador2: " << scores[1] << "pts" << endl;
  }
  string falso_ganador = scores[0] > scores[1] ? "1" : "2";
  string resultado = scores[0] == scores[1] ? "\nEmpate" : "\nGanó Jugador " + falso_ganador ;
  cout << resultado << endl;
}

int main() {
  srand(time(NULL)); // semilla distinta cada vez
  Tazo *last = fill();
  jugar(last);
  return 0;
}
