#include "entrenador.hpp"
#include "trie.hpp"
#include <iostream>
#include <string>

int main() {
  std::cout << "Cargando textos..." << std::endl;
  std::unordered_map<std::string, int> frecuencias = entrenar_desde_archivos();
  std::cout << "Construyendo Trie..." << std::endl;
  Trie trie;
  for (const auto &[palabra, freq] : frecuencias)
    trie.insertar(palabra, freq);
  std::cout << "Listo. Escribe un prefijo (o 'salir'):\n\n";
  std::string prefijo;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, prefijo);
    if (prefijo == "salir")
      break;
    if (prefijo.empty())
      continue;
    auto sugerencias = trie.obtener_topk(prefijo, 10);
    if (sugerencias.empty())
      std::cout << "  (sin sugerencias)" << std::endl;
    else
      for (const auto &[freq, palabra] : sugerencias)
        std::cout << "  " << palabra << " (" << freq << ")" << std::endl;
    std::cout << std::endl;
  }
  return 0;
}
