#ifndef TRIE_HPP
#define TRIE_HPP

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct NodoTrie {
  std::unordered_map<char, NodoTrie *> hijos;
  bool fin_de_palabra = false;
  int frecuencia = 0;
  NodoTrie() = default;
};

class Trie {
private:
  NodoTrie *raiz;
  void destruir(NodoTrie *nodo);
  // Función recursiva para recolectar palabras desde un nodo dado
  void recolectar(NodoTrie *nodo, const std::string &prefijo, std::vector<std::pair<std::string, int>> &resultados) const;
  // el mismo de arriba pero más eficiente
  void recolectar_topk(
    NodoTrie *nodo,
    std::string &prefijo,
    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>,
        std::greater<>> &cola_de_prioridad,
    int k) const;

public:
  Trie();
  ~Trie();
  // Insertar una palabra con su frecuencia (si ya existe, suma frecuencia)
  void insertar(const std::string &palabra, int frecuencia);

  // Buscar nodo donde termina un prefijo
  // Devuelve nullptr si no existe el prefijo
  NodoTrie *buscar_prefijo(const std::string &prefijo) const;

  // Obtener sugerencias basadas en un prefijo
  // Devuelve pares (palabra, frecuencia)
  std::vector<std::pair<std::string, int>> obtener_sugerencias(const std::string &prefijo, int limite) const;
  // el mismo de arriba pero mas eficiente
  std::vector<std::pair<int, std::string>> obtener_topk(const std::string &prefijo, int k = 10) const;
};

#endif // TRIE_HPP
