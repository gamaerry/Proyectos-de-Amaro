#ifndef UTF8_ES_HPP
#define UTF8_ES_HPP

#include <cctype>
#include <string>
#include <string_view>

//  ENUM: patrón de capitalización
enum class PatronCapitalizacion {
  MINUSCULAS,
  MAYUSCULAS,
  TITULO,
  MIXTO
};

//  Detecta patrón de un prefijo (2+ caracteres)
inline PatronCapitalizacion detectar_patron(std::string_view prefijo) {
  if (prefijo.size() < 2)
    return PatronCapitalizacion::MINUSCULAS;
  bool may0 = std::isupper(static_cast<unsigned char>(prefijo[0]));
  bool may1 = std::isupper(static_cast<unsigned char>(prefijo[1]));
  if (may0 && may1)
    return PatronCapitalizacion::MAYUSCULAS;
  if (may0)
    return PatronCapitalizacion::TITULO;
  return PatronCapitalizacion::MINUSCULAS;
}

//  longitud de un carácter UTF-8 desde primer byte
constexpr size_t utf8_char_length(unsigned char c) noexcept {
  if (c < 0x80)
    return 1;
  if ((c & 0xE0) == 0xC0)
    return 2;
  if ((c & 0xF0) == 0xE0)
    return 3;
  if ((c & 0xF8) == 0xF0)
    return 4;
  return 1;
}

//  Cuenta caracteres UTF-8 (no bytes)
inline size_t contar_caracteres_utf8(std::string_view s) noexcept {
  size_t count = 0;
  for (size_t i = 0; i < s.size();) {
    i += utf8_char_length(static_cast<unsigned char>(s[i]));
    count++;
  }
  return count;
}

//  Cuenta unidades UTF-16
inline size_t utf8_to_utf16_length(std::string_view s) noexcept {
  size_t count = 0;
  for (size_t i = 0; i < s.size();) {
    unsigned char c = s[i];
    size_t len = utf8_char_length(c);
    i += len;
    count += (len == 4) ? 2 : 1; // 4 bytes = surrogate pair
  }
  return count;
}

//  Convierte índice UTF-16 a índice UTF-8 (bytes)
inline size_t utf16_to_utf8_index(std::string_view s, size_t col16) noexcept {
  size_t i = 0;
  size_t count16 = 0;
  while (i < s.size() && count16 < col16) {
    unsigned char c = s[i];
    size_t len = utf8_char_length(c);
    i += len;
    count16 += (len == 4) ? 2 : 1;
  }
  return i;
}

//  Conversión a mayúsculas (soporte a español)
inline std::string utf8_to_upper_es(std::string_view palabra) {
  std::string resultado;
  resultado.reserve(palabra.size());
  for (size_t i = 0; i < palabra.size();) {
    unsigned char c = palabra[i];
    size_t len = utf8_char_length(c);
    // ASCII simple
    if (len == 1) {
      resultado.push_back(std::toupper(c));
      i++;
      continue;
    }
    // UTF-8 de 2 bytes: caracteres latinos (á, é, í, ó, ú, ñ, ü)
    if (len == 2 && i + 1 < palabra.size()) {
      unsigned char c1 = c;
      unsigned char c2 = palabra[i + 1];
      // Rango de minúsculas latinas con acento: 0xC3 0xA0-0xBF
      // Convertir a mayúsculas: restar 0x20 al segundo byte
      if (c1 == 0xC3 && c2 >= 0xA0 && c2 <= 0xBF) {
        resultado.push_back(c1);
        resultado.push_back(c2 - 0x20);
      } else
        resultado.append(palabra.substr(i, 2));
      i += 2;
      continue;
    }
    // Otros casos: copiar sin cambios
    resultado.append(palabra.substr(i, len));
    i += len;
  }
  return resultado;
}

//  Conversión a minúsculas (español completo)
inline std::string utf8_to_lower_es(std::string_view palabra) {
  std::string resultado;
  resultado.reserve(palabra.size());
  for (size_t i = 0; i < palabra.size();) {
    unsigned char c = palabra[i];
    size_t len = utf8_char_length(c);
    // ASCII simple
    if (len == 1) {
      resultado.push_back(std::tolower(c));
      i++;
      continue;
    }
    // UTF-8 de 2 bytes: caracteres latinos (Á, É, Í, Ó, Ú, Ñ, Ü)
    if (len == 2 && i + 1 < palabra.size()) {
      unsigned char c1 = c;
      unsigned char c2 = palabra[i + 1];
      // Rango de mayúsculas latinas con acento: 0xC3 0x80-0x9F
      // Convertir a minúsculas: sumar 0x20 al segundo byte
      if (c1 == 0xC3 && c2 >= 0x80 && c2 <= 0x9F) {
        resultado.push_back(c1);
        resultado.push_back(c2 + 0x20);
      } else {
        resultado.append(palabra.substr(i, 2));
      }
      i += 2;
      continue;
    }
    // Otros casos: copiar sin cambios
    resultado.append(palabra.substr(i, len));
    i += len;
  }
  return resultado;
}

//  Aplica el patrón deseado a una palabra UTF-8
inline std::string aplicar_patron(std::string_view palabra, PatronCapitalizacion patron) {
  switch (patron) {
  case PatronCapitalizacion::MINUSCULAS:
    return utf8_to_lower_es(palabra);
  case PatronCapitalizacion::MAYUSCULAS:
    return utf8_to_upper_es(palabra);
  case PatronCapitalizacion::TITULO: {
    if (palabra.empty())
      return std::string(palabra);
    std::string resultado;
    resultado.reserve(palabra.size());
    // Primera letra en mayúscula
    size_t first_len = utf8_char_length(static_cast<unsigned char>(palabra[0]));
    resultado = utf8_to_upper_es(palabra.substr(0, first_len));
    // Resto en minúsculas
    if (first_len < palabra.size())
      resultado += utf8_to_lower_es(palabra.substr(first_len));
    return resultado;
  }
  case PatronCapitalizacion::MIXTO:
  default:
    return std::string(palabra);
  }
}

#endif // UTF8_ES_HPP
