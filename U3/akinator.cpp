#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
  string personaje;
  string pregunta;
  Node *si;
  Node *no;
  Node(string p = "", string q = "") : personaje(p), pregunta(q), si(nullptr), no(nullptr) {}
};

// Pregunta al usuario (sí = true, no = false)
bool preguntar(const string &q) {
  cout << q << " (s/n): ";
  char r;
  cin >> r;
  return (r == 's' || r == 'S');
}

// Recorre el árbol hasta llegar a un personaje
void jugar(Node *nodo) {
  while (nodo->si || nodo->no) {
    bool r = preguntar(nodo->pregunta);
    nodo = r ? nodo->si : nodo->no;
  }
  cout << "\n¿Tu personaje es: " << nodo->personaje << "? (s/n): ";
  char c;
  cin >> c;
  if (c == 's' || c == 'S')
    cout << "¡Lo sabía! \n";
  else
    cout << "¡Rayos! \n";
}

Node *construirArbol(const vector<string> &preguntas, const vector<vector<int>> &respuestas, const vector<string> &personajes, int preguntaIndex, const vector<int> &indices) {
  if (indices.size() == 1) {
    return new Node(personajes[indices[0]], "");
  }
  if (preguntaIndex >= preguntas.size()) {
    return new Node(personajes[indices[0]], "");
  }
  Node *nodo = new Node("", preguntas[preguntaIndex]);
  vector<int> siGroup, noGroup;
  for (int i : indices) {
    if (respuestas[i][preguntaIndex] == 1)
      siGroup.push_back(i);
    else
      noGroup.push_back(i);
  }
  if (siGroup.empty())
    siGroup = noGroup;
  if (noGroup.empty())
    noGroup = siGroup;
  nodo->si = construirArbol(preguntas, respuestas, personajes, preguntaIndex + 1, siGroup);
  nodo->no = construirArbol(preguntas, respuestas, personajes, preguntaIndex + 1, noGroup);
  return nodo;
}

int main() {
  vector<string> preguntas = {
      "¿Es live action?",
      "¿Es criatura acuática?",
      "¿Es del género femenino?",
      "¿Tiene dos ojos?",
      "¿Es humano?",
      "¿Puede respirar bajo el agua?",
      "¿Vive en Fondo de Bikini?",
      "¿Es amigo cercano de Bob?",
      "¿Tiene super poderes?",
      "¿Tiene trabajo?",
      "¿Es amargado?",
      "¿Es gordito(a)?",
      "¿Es anciano(a)?",
      "¿Tiene un archienemigo?",
      "¿Habla?"};
  vector<string> personajes = {
      "Bob esponja", "Patricio", "Calamardo", "Don cangrejo", "Plancton",
      "K.A.R.E.N.", "Arenita", "Señora Puff", "Perlita", "Gary",
      "Parche el pirata", "Potty el loro", "Sirenoman", "Chico Percebe",
      "Holandés Volador", "Rey Neptuno / Poseidon", "Larry la langosta",
      "Harold Pantalones cuadrados", "Margaret Pantalones cuadrados",
      "Abuela Pantalones cuadrados", "Cabeza de pezcado", "Perca Perkins",
      "Medusa", "Mamá cangrejo", "Róbalo Burbuja", "Burbuja sucia",
      "Manta Raya", "Señora Tentaculos", "Calamarino elegante",
      "Princesa Mindy", "Dennis", "Viejo Jenkins"};
  vector<vector<int>> R = {
      {0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1}, // Bob esponja
      {0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1}, // Patricio
      {0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1}, // Calamardo
      {0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1}, // Don Cangrejo
      {0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1}, // Plancton
      {0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1}, // K.A.R.E.N.
      {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // Arenita
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1}, // Señora Puff
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // Perlita
      {0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // Gary
      {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // Parche el pirata
      {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // Potty el loro
      {0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1}, // Sirenoman
      {0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1}, // Chico Percebe
      {0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1}, // Holandés Volador
      {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1}, // Rey Neptuno / Poseidon
      {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1}, // Larry la langosta
      {0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // Harold P. Cuadrados
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // Margaret P. Cuadrados
      {0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1}, // Abuela P. Cuadrados
      {1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // Cabeza de pez
      {0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1}, // Perca Perkins
      {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // Medusa
      {0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1}, // Mamá cangrejo
      {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1}, // Róbalo Burbuja
      {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1}, // Burbuja sucia
      {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1}, // Manta Raya
      {0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1}, // Señora Tentáculos
      {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1}, // Calamarino elegante
      {0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // Princesa Mindy
      {0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // Dennis
      {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1}  // Viejo Jenkins
  };
  vector<int> indices(personajes.size());
  for (int i = 0; i < indices.size(); i++)
    indices[i] = i;
  vector<bool> usadas(preguntas.size(), false);
  cout << "Piensa en un personaje y yo lo adivinaré.\n";
  Node *raiz = construirArbol(preguntas, R, personajes, 0, indices);
  jugar(raiz);
  return 0;
}
