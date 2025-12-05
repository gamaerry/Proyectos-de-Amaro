#include <cctype>
#include <string>
#include <vector>

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

  for (size_t i = 0; i < n; i++) {
    unsigned char c = texto[i];

    // 1. Acentos españoles (C3 xx)
    if (c == 0xC3 && i + 1 < n) {
      palabra += c;
      palabra += texto[++i];
      continue;
    }

    // 2. ASCII letra/número/guion/apóstrofe/punto válido
    caracter_valido = std::isalnum(c) || c == '-' || c == '\'' || c == '/';
    punto_valido = c == '.' && i > 0 && i + 1 < n && std::isalnum(texto[i - 1]) && std::isalnum(texto[i + 1]);
    dos_puntos = c == ':' && i > 0 && i + 1 < n && (texto[i + 1] == '\'' || texto[i + 1] == '/');
    if (caracter_valido || punto_valido || dos_puntos) {
      palabra += c;
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

#include <iostream>

int main() {
  std::string test = R"(¿¡Realmente podrás tokenizar correctamente este texto?! —preguntó María—. 
'¡Claro que sí!', respondió él. 
El pingüino soñoliento comió piña, ñoquis y tomó café con azúcar. 
Programación-orientada-a-objetos es diferente de programación funcional; 
sin embargo, ambos paradigmas coexisten en 2025.

Además: «¿cuántas palabras separarás aquí, eh?»; palabras como “rápido”, “niña”, “año”, “pingüino”, "vergüenza" y "maíz" deben mantenerse íntegras.
También hay casos extraños: emojis 😊😂🔥, símbolos matemáticos (≈ ≤ ≥ ± ÷ ×), 
y otros caracteres unicode que NO deben formar palabras: © ® ™ § ¶ † ‡ · • ¥ € £.

¿Y qué pasa con direcciones como https://ejemplo.com/test?id=123 o e-mails como correo.prueba+utf8@dominio.es?
¿O con números mezclados, como 4x4, 3.1416, 1. y 2.?

Finalmente… ¡prueba-extrema-final-del-tokenizador-español!)";
  auto palabras = tokenizar(test);

  for (const auto &palabra : palabras) {
    std::cout << palabra << std::endl;
  }
}
