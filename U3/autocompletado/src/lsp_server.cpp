// lsp_server.cpp
#include "entrenador.hpp"
#include "json.hpp"
#include "trie.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using json = nlohmann::json; // mini librería que nos permite usar json en cpp

class LSPServer {
private:
  Trie trie;
  bool inicializado;
  // Cache de documentos abiertos
  std::unordered_map<std::string, std::string> documentos;

  std::string leer_mensaje() { // recibe el mensaje del editor y regresa el JSON de la petición
    std::string linea;
    int longitud = 0;
    // Leer linea del cin
    while (std::getline(std::cin, linea)) {
      if (linea == "\r" || linea == "\r\n" || linea.empty())
        break; // fin de mensaje
      if (linea.find("Content-Length:") == 0)
        longitud = std::stoi(linea.substr(16)); // encuentre longitud en el mensaje
    }
    if (longitud == 0)
      return "";
    std::string contenido(longitud, '\0');     // reserva un str de esa longitud
    std::cin.read(contenido.data(), longitud); // lo guarda en contenido y lo retorna
    return contenido;
  }

  void enviar_mensaje(const json &mensaje) { // envia una respuesta json con el formato lsp correcto
    std::string contenido = mensaje.dump();
    std::cout << "Content-Length: " << contenido.length() << "\r\n\r\n";
    std::cout << contenido << std::flush; // el flush hace que el editor reciba el mensaje inmediatamente
  }

  // Maneja el request "initialize"
  void manejar_initialize(const json &peticion) {
    json respuesta = {// este es un mensaje de inicialización donde se le pasan algunos parametros iniciales al editor
                      {"jsonrpc", "2.0"},
                      {"id", peticion["id"]},
                      {"result", {{"capabilities", {{"textDocumentSync", 1}, {"completionProvider", {{"resolveProvider", false}}}}}, {"serverInfo", {{"name", "autocompletado-gamaerry"}, {"version", "1.0.0"}}}}}};
    enviar_mensaje(respuesta);
    inicializado = true;
    std::cerr << "Servidor inicializado" << std::endl;
  }

  void manejar_did_open(const json &notificacion) { // maneja notificación de documento abierto y lo guarda en documentos
    try {                                           // no necesario pero por seguridad ante un JSON mal formado
      auto params = notificacion["params"];
      std::string uri = params["textDocument"]["uri"];
      std::string texto = params["textDocument"]["text"];
      documentos[uri] = texto;
      std::cerr << "Documento abierto: " << uri << std::endl;
    } catch (const std::exception &e) {
      std::cerr << "Error en didOpen: " << e.what() << std::endl;
    }
  }

  void manejar_did_change(const json &notificacion) { // maneja la notificación "textDocument/didChange"
    try {                                             // no necesario pero por seguridad ante un JSON mal formado
      auto params = notificacion["params"];
      std::string uri = params["textDocument"]["uri"];
      auto cambios = params["contentChanges"];
      if (!cambios.empty() && cambios[0].contains("text")) {
        documentos[uri] = cambios[0]["text"]; // reemplaza todo el doc con la nueva versión
        std::cerr << "Documento actualizado: " << uri << std::endl;
      }
    } catch (const std::exception &e) {
      std::cerr << "Error en didChange: " << e.what() << std::endl;
    }
  }

  // Extrae la palabra antes del cursor
  std::string extraer_prefijo(const std::string &linea, int columna) {
    if (linea.empty() || columna == 0)
      return "";
    int inicio = columna - 1;
    // Retroceder mientras haya caracteres de palabra
    bool caracter_valido;
    while (inicio >= 0) {
      unsigned char c = linea[inicio];
      // Si es letra, número, guion, apóstrofe o parte de UTF-8
      caracter_valido = std::isalnum(c) || c == '-' || c == '\'' || c == '/' || c == '@' || c == '_' || c & 0x80;
      if (caracter_valido) // c & 0x80 cualquier char multibyte es detectado
        inicio--;
      else
        break;
    }
    inicio++; // Ajustar al primer carácter válido
    if (inicio >= columna)
      return "";
    return linea.substr(inicio, columna - inicio);
  }

  int utf16_to_utf8_index(const std::string &s, int col16) { // regresa el indice de acuerdo a longitud
    int i = 0, count16 = 0;
    while (i < s.size() && count16 < col16) {
      unsigned char c = s[i];
      int bytes = (c < 0x80) ? 1 : ((c & 0xE0) == 0xC0) ? 2
                               : ((c & 0xF0) == 0xE0)   ? 3
                               : ((c & 0xF8) == 0xF0)   ? 4
                                                        : 1;
      i += bytes;
      count16 += (bytes == 4) ? 2 : 1;
    }
    return i;
  }

  // Maneja el request "textDocument/completion"
  void manejar_completion(const json &peticion) {
    try {
      auto params = peticion["params"];
      std::string uri = params["textDocument"]["uri"];
      int linea = params["position"]["line"];
      int columna = params["position"]["character"];
      std::cerr << "Completion request: " << uri
                << " línea:" << linea
                << " col:" << columna << std::endl;
      // Obtener el documento del cache
      if (documentos.find(uri) == documentos.end()) {
        std::cerr << "Documento no encontrado en cache" << std::endl;
        json respuesta = {
            {"jsonrpc", "2.0"},
            {"id", peticion["id"]},
            {"result", {"items", json::array()}}};
        enviar_mensaje(respuesta);
        return;
      }
      std::string texto_completo = documentos[uri];
      // Dividir en líneas
      std::vector<std::string> lineas;
      std::istringstream stream(texto_completo);
      std::string linea_actual;
      while (std::getline(stream, linea_actual)) {
        lineas.push_back(linea_actual);
      }
      // Obtener la línea específica
      if (linea >= lineas.size()) {
        std::cerr << "Línea fuera de rango" << std::endl;
        json respuesta = {
            {"jsonrpc", "2.0"},
            {"id", peticion["id"]},
            {"result", {"items", json::array()}}};
        enviar_mensaje(respuesta);
        return;
      }
      std::string texto_linea = lineas[linea];
      int byte_index = utf16_to_utf8_index(texto_linea, columna);
      // Extraer prefijo
      std::string prefijo = extraer_prefijo(texto_linea, byte_index);
      std::cerr << "Prefijo extraído: '" << prefijo << "'" << std::endl; // prints utiles durante el debugueo
      // Obtener sugerencias del Trie
      auto sugerencias = trie.obtener_topk(prefijo, 10);
      std::cerr << "Sugerencias encontradas: " << sugerencias.size() << std::endl;
      // Construir items de completion
      json items = json::array();
      for (const auto &[freq, palabra] : sugerencias) {
        items.push_back({{"label", palabra},
                         {"kind", 1}, // 1 = Text
                         {"detail", "freq: " + std::to_string(freq)},
                         {"textEdit", {{"range", {{"start", {{"line", linea}, {"character", columna - (int)prefijo.length()}}}, {"end", {{"line", linea}, {"character", columna}}}}}, {"newText", palabra}}}});
      }
      json respuesta = {
          {"jsonrpc", "2.0"},
          {"id", peticion["id"]},
          {"result", {{"isIncomplete", true}, {"items", items}}}};
      enviar_mensaje(respuesta);
    } catch (const std::exception &e) {
      std::cerr << "Error en completion: " << e.what() << std::endl;
      json respuesta = {
          {"jsonrpc", "2.0"},
          {"id", peticion["id"]},
          {"result", {"items", json::array()}}};
      enviar_mensaje(respuesta);
    }
  }

public:
  LSPServer() {
    // Cargar y entrenar al iniciar
    std::cerr << "Cargando textos..." << std::endl;
    auto frecuencias = entrenar_desde_archivos();
    std::cerr << "Construyendo Trie con " << frecuencias.size()
              << " palabras..." << std::endl;
    for (const auto &[palabra, freq] : frecuencias)
      trie.insertar(palabra, freq);
    std::cerr << "LSP Server listo." << std::endl;
  }

  void run() {
    while (true) {
      std::string mensaje = leer_mensaje();
      if (mensaje.empty())
        break; // EOF o error
      try {
        json request = json::parse(mensaje);
        std::string metodo = request["method"];
        std::cerr << "Recibido: " << metodo << std::endl;
        // Manejar notificaciones (sin "id")
        if (!request.contains("id")) {
          if (metodo == "textDocument/didOpen") {
            manejar_did_open(request);
          } else if (metodo == "textDocument/didChange") {
            manejar_did_change(request);
          } else if (metodo == "initialized") {
            std::cerr << "Cliente inicializado" << std::endl;
          }
          continue;
        }
        // Manejar requests (con "id")
        if (metodo == "initialize")
          manejar_initialize(request);
        else if (metodo == "textDocument/completion")
          manejar_completion(request);
        else if (metodo == "shutdown") {
          json respuesta = {
              {"jsonrpc", "2.0"},
              {"id", request["id"]},
              {"result", nullptr}};
          enviar_mensaje(respuesta);
          break;
        }
      } catch (const std::exception &e) {
        std::cerr << "Error procesando mensaje: " << e.what() << std::endl;
      }
    }
  }
};

int main() {
  LSPServer server;
  server.run();
  return 0;
}
