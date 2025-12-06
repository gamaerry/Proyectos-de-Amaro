#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>


struct NodoTrie {
  std::unordered_map<char, NodoTrie *> hijos;
  bool fin_de_palabra = false;
  int frecuencia = 0;
  NodoTrie() = default;
};

class Trie {
private:
  NodoTrie *raiz;
  void destruir(NodoTrie* nodo);
  // Función recursiva para recolectar palabras desde un nodo dado
  void recolectar(NodoTrie *nodo, const std::string &prefijo, std::vector<std::pair<std::string, int>> &resultados) const;

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
  std::vector<std::pair<std::string, int>>obtener_sugerencias(const std::string &prefijo, int limite) const;
};

#endif // TRIE_HPP
