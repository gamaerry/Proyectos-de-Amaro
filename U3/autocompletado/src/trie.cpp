#include "trie.hpp"

Trie::Trie() {
  raiz = new NodoTrie();
}

Trie::~Trie() {
  destruir(raiz);
}

void Trie::insertar(const std::string &palabra, int frecuencia) {
  NodoTrie *actual = raiz;
  for (char c : palabra) {
    if (!actual->hijos.count(c)) // si count da 0
      actual->hijos[c] = new NodoTrie();
    actual = actual->hijos[c];
  }
  actual->fin_de_palabra = true;
  // Acumula frecuencia si ya existía
  actual->frecuencia += frecuencia;
}

NodoTrie *Trie::buscar_prefijo(const std::string &prefijo) const {
  NodoTrie *actual = raiz;
  for (char c : prefijo) {
    auto it = actual->hijos.find(c);
    if (it == actual->hijos.end())
      return nullptr;
    actual = it->second;
  }
  return actual;
}

void Trie::destruir(NodoTrie *nodo) {
  if (!nodo)
    return;
  for (auto &par : nodo->hijos)
    destruir(par.second); // par.second es el puntero al hijo
  delete nodo;
}

// Métodos poco eficientes:
void Trie::recolectar(NodoTrie *nodo, const std::string &prefijo, std::vector<std::pair<std::string, int>> &resultados) const {
  if (!nodo)
    return;
  if (nodo->fin_de_palabra)
    resultados.push_back({prefijo, nodo->frecuencia}); // se hara push al vector resultados solo cuando llegue al final
  std::string nueva_palabra = prefijo;
  nueva_palabra.reserve(prefijo.size() + 20); // otros 20 caracteres adicionales
  for (const auto &hijo : nodo->hijos) {
    nueva_palabra = prefijo;
    nueva_palabra += hijo.first;
    recolectar(hijo.second, nueva_palabra, resultados);
  }
}

std::vector<std::pair<std::string, int>> Trie::obtener_sugerencias(const std::string &prefijo, int limite = 5) const {
  std::vector<std::pair<std::string, int>> resultados;
  NodoTrie *nodo = buscar_prefijo(prefijo);
  if (!nodo)
    return resultados; // prefijo no existe
  recolectar(nodo, prefijo, resultados);
  // Ordenar por frecuencia descendente
  std::partial_sort(resultados.begin(), resultados.begin() + std::min(limite, (int)resultados.size()), resultados.end(), [](const auto &a, const auto &b) {
    return a.second > b.second;
  });
  if (resultados.size() > limite)
    resultados.resize(limite);
  return resultados;
}

// Métodos más optimizado (hacen lo mismo que recolectar() y obtener_sugerencias() pero delimitado a un k, ie. más eficientes):
std::vector<std::pair<int, std::string>> Trie::obtener_topk(const std::string &prefijo, int k) const {
  NodoTrie *nodo = buscar_prefijo(prefijo);
  if (!nodo)
    return {};
  using Elem = std::pair<int, std::string>;
  std::priority_queue<Elem, std::vector<Elem>, std::greater<>> cola_de_prioridad;
  std::string palabra = prefijo;
  recolectar_topk(nodo, palabra, cola_de_prioridad, k);
  // Convertir y ordenar de mayor a menor
  std::vector<std::pair<int, std::string>> resultado;
  resultado.reserve(cola_de_prioridad.size());
  while (!cola_de_prioridad.empty()) {
    resultado.push_back(cola_de_prioridad.top());
    cola_de_prioridad.pop();
  } // el resultado es un par<frecuencia, palabra>
  std::reverse(resultado.begin(), resultado.end());
  return resultado;
}

void Trie::recolectar_topk(
    NodoTrie *nodo,
    std::string &prefijo,
    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>, // este es un contenedor interno para los pares (protocolo de creación de un priority_queue)
        std::greater<> // esto hace que automaticamente con pop() se saque al peor "greater"!!! (ie. al menos frecuente)
    > &cola_de_prioridad, // esta cola tiene a lo mucho k elementos
    int k) const {
  if (!nodo)
    return;
  if (nodo->fin_de_palabra) {
    if ((int)cola_de_prioridad.size() < k) // si la cola no está llena, se mete la palabra con su frecuencia
      cola_de_prioridad.emplace(nodo->frecuencia, prefijo); // emplace es un enqueue eficiente
    else if (nodo->frecuencia > cola_de_prioridad.top().first) { // como el peor siempre está al inicio
      cola_de_prioridad.pop(); // si el actual es mas frecuente que el top, se saca el top
      cola_de_prioridad.emplace(nodo->frecuencia, prefijo); // y se mete al end de la cola
    }
  }
  // recorrer hijos
  for (auto &[c, hijo] : nodo->hijos) { // las tres lineas siguientes son patrón universal de backtracking
    prefijo.push_back(c);
    recolectar_topk(hijo, prefijo, cola_de_prioridad, k);
    prefijo.pop_back(); // muy eficiente, se restaura el estado
  }
}
