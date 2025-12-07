# Autocompletado Gamaerry

Sistema de autocompletado personalizado para editores de texto entrenado con tus propios textos en español/inglés.

## Características

- **Entrenamiento personalizado**: Aprende del vocabulario de tus propios archivos `.txt`
- **Soporte completo UTF-8**: Maneja acentos (áéíóúñü) correctamente
- **Capitalización inteligente**: 
  - `ga` → gato, ganar, galleta
  - `Ga` → Gato, Ganar, Galleta  
  - `GA` → GATO, GANAR, GALLETA
- **LSP nativo**: Se integra con cualquier editor de texto moderno como cualquier language server
- **Frecuencia de uso**: Sugiere primero las palabras más usadas
- **Trie optimizado**: Búsquedas O(m) donde m = longitud del prefijo
- **Extensión propia .gama**: El autocompletado puede usar para archivos .txt o cualquier otra extensión personalizada

## Estructura del Proyecto
```
autocompletado/
├── src/
│   ├── lsp_server.cpp                   # Servidor LSP principal
│   ├── trie.hpp / trie.cpp              # Estructura de datos Trie
│   ├── entrenador.hpp / entrenador.cpp  # Tokenizador y entrenamiento
│   ├── utf8_es.hpp                      # Utilidades UTF-8 para español
│   ├── json.hpp                         # nlohmann/json (external)
│   ├── test_autocompletado.cpp          # CLI interactivo de prueba
│   ├── test_top_palabras.cpp            # Mostrar palabras más frecuentes
│   └── out/                             # Binarios compilados
└── data/
    └── *.txt                            # Tus archivos de entrenamiento
```

##  Instalación

### Requisitos
- Código fuente de este proyecto (directorio `autocompletado/`)
- **Compilador**: g++ con soporte C++17 o superior

### Agregar Textos de Entrenamiento

Coloca tus archivos `.txt` en el directorio `data/`:
```bash
cp ~/mis_textos/*.txt data/
```

Mientras más texto agregues, mejores serán las sugerencias.

### Compilar el LSP Server
```bash
cd src
g++ -std=c++17 lsp_server.cpp utf8_es.hpp trie.cpp entrenador.cpp -o out/autocompletado-lsp -O2
```

## Configuración (Helix como ejemplo)

Edita `~/.config/helix/languages.toml`:
```toml
[language-server.autocompletado-gamaerry]
command = "/ruta/absoluta/a/autocompletado/src/out/autocompletado-lsp"

[[language]]
name = "gama"
scope = "source.txt"
file-types = ["gama", "txt"]
language-servers = ["autocompletado-gamaerry"]
```


Por defecto funciona con `.gama` y `.txt`. Para agregar más extensiones:
```toml
[[language]]
name = "gama"
scope = "source.txt"
file-types = ["gama", "txt", "notes"]
language-servers = ["autocompletado-gamaerry"]
```

### Ajustar Número de Sugerencias

En `src/lsp_server.cpp`
```cpp
auto sugerencias = trie.obtener_topk(prefijo_lower, 10);  // Cambiar el 10
```

### Re-entrenar con Nuevos Textos

1. Agrega más archivos `.txt` en `data/`
2. Reinicia Helix (no necesitas recompilar el LSP)

El entrenamiento ocurre al iniciar el LSP.

Asegúrate de usar extensión `.gama` o `.txt`

## Tokenización

El sistema extrae palabras considerando:

 Alfanuméricos (a-z, A-Z, 0-9)  
 Acentos (áéíóúñü)  
 Guiones (`auto-completado`, `y/o`)  
 Apóstrofes (`can't`)  
 Palabras de 3+ caracteres 

##  Autor

Desarrollado por @gamaerry como proyecto educativo de Estructuras de Datos.

---

