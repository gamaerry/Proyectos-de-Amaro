#include "entrenador.hpp"
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
namespace fs = std::filesystem;

std::vector<std::string> tokenizar(const std::string &texto) {
  std::vector<std::string> palabras;
  std::string palabra;
  auto guardar = [&]() {
    if (palabra.size() >= 3)
      palabras.push_back(std::move(palabra));
    palabra.clear();
  };
  const size_t n = texto.size();
  bool punto_valido, caracter_valido, dos_puntos;
  unsigned char siguiente_de_acentos;
  for (size_t i = 0; i < n; i++) {
    unsigned char c = texto[i];
    // 1. Acentos españoles (C3 xx)
    if (c == 0xC3 && i + 1 < n) {
      palabra += c;
      siguiente_de_acentos = texto[++i];
      if (siguiente_de_acentos >= 0x81 && siguiente_de_acentos <= 0x9C) // si es mayúscula
        siguiente_de_acentos += 0x20;                                   // 0x20 es la distancia de su correspondiente minúscula
      palabra += siguiente_de_acentos;
      continue;
    }
    // 2. ASCII letra/número/guion/apóstrofe/punto válido
    caracter_valido = std::isalnum(c) || c == '-' || c == '\'' || c == '/' || c == '@' || c == '_';
    punto_valido = c == '.' && i > 0 && i + 1 < n && std::isalnum(texto[i - 1]) && std::isalnum(texto[i + 1]);
    dos_puntos = c == ':' && i > 0 && i + 1 < n && (texto[i + 1] == '\'' || texto[i + 1] == '/');
    if (caracter_valido || punto_valido || dos_puntos) {
      palabra += std::tolower(c);
      continue;
    }
    // 3. UTF-8 multibyte no deseado (saltar bytes y cerrar palabra)
    if (c & 0x80) { // esto es igual a (c & 0x80) != 0
      guardar();
      if ((c & 0xE0) == 0xC0)
        i += 1; // 2 bytes
      else if ((c & 0xF0) == 0xE0)
        i += 2; // 3 bytes
      else if ((c & 0xF8) == 0xF0)
        i += 3; // 4 bytes
      continue;
    }
    // 4. Separador ASCII
    guardar();
  }
  guardar();
  return palabras;
}

void procesar_archivo(const std::string &ruta, std::unordered_map<std::string, int> &frecuencias) {
  std::ifstream archivo(ruta);
  if (!archivo.is_open()) {
    std::cerr << "Error abriendo: " << ruta << std::endl;
    return;
  }
  std::string linea;
  while (std::getline(archivo, linea)) {
    std::vector<std::string> palabras = tokenizar(linea);
    for (const auto &palabra : palabras) {
      frecuencias[palabra]++;
    }
  }
  archivo.close();
}

std::unordered_map<std::string, int> entrenar_desde_archivos() {
  std::unordered_map<std::string, int> frecuencias;
  // Procesar todos los .txt en la carpeta "textos/"
  for (const auto &entrada : fs::directory_iterator("/home/lg/Documents/EstructuraDeDatos/U3/autocompletado/data/")) {
    if (entrada.path().extension() == ".txt") {
      std::cout << "Procesando: " << entrada.path() << std::endl;
      procesar_archivo(entrada.path().string(), frecuencias);
    }
  }
  return frecuencias;
}
