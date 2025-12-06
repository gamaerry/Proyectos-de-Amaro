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


// métodos poco eficientes:

void Trie::recolectar(NodoTrie *nodo, const std::string &prefijo, std::vector<std::pair<std::string, int>> &resultados) const { // TODO: recolectar solo topk con una priority_queue
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

