#include "constantes.h"
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>

using namespace std::chrono;
using namespace std;

// Variables necesarias
int mi_fd;
int *datos;
int *posicion = (int *)malloc(2 * sizeof(int));
const regex patron_movimiento("^[0-9wasdWASD]+$");
const regex patron_salir("^[qQ]$");
const string direcciones_validas = "wasdWASD";
string input_actual = ""; //input cualquiera
string linea = ""; //comando de movimiento
string fragmento = ""; //una direccion de movimiento
int restantes = 0; //cuantos pasos
char direccion_actual = 'd'; // hacia esta direccion

void wait_control() { 
  auto dur = std::chrono::system_clock::now().time_since_epoch();
  auto reloj_control = time_point<system_clock>(
      (duration_cast<milliseconds>(dur).count() / 1000 + 1) * 1000ms + 500ms // mitad de segundo
  );
  std::this_thread::sleep_until(reloj_control);
}

void terminar_juego() {
  posicion[0] = -1;
}

void mover_jugador() {
  cout << "moviendo esta direccion: " << direccion_actual<< " con esto de restante: "<< restantes<< endl;
  restantes--;
  switch (direccion_actual) {
    case 'w':
    case 'W':
      if (posicion[0] > 0)
        posicion[0]--;
      break;
    case 's':
    case 'S':
      if (posicion[0] < LARGO_TOTAL - 1)
        posicion[0]++;
      break;
    case 'a':
    case 'A':
      if (posicion[1] > 0)
        posicion[1]--;
      break;
    case 'd':
    case 'D':
      if (posicion[1] < ANCHO_TOTAL - 1)
        posicion[1]++;
      break;
  }
}

void set_posicion_inicial() {
  posicion[0] = i_inicial_jugador;
  posicion[1] = j_inicial_jugador;
  memcpy(datos, posicion, 2 * sizeof(int));
}

bool esta_detenido() {
  return fragmento.empty() && linea.empty() && restantes == 0;
}

void interpretar_fragmento() {
  cout << "interpretando este fragmento: " << fragmento << endl;
  direccion_actual = fragmento.back();
  string tmp = fragmento.substr(0, fragmento.size() - 1);
  restantes = tmp.empty() ? 1 : stoi(tmp);
  fragmento = "";
}

void interpretar_linea() {
  cout << "interpretando esta linea: " << linea << endl;
  size_t posicion = linea.find_first_of(direcciones_validas);
  if (posicion != string::npos) {
    fragmento = linea.substr(0, posicion + 1);
    linea.erase(0, posicion + 1);
  } else { // si encontro solo num. ent. por defecto se moverá a d
    fragmento = linea + 'd';
  }
}

void caminar_un_paso() {
  if(fragmento.empty() && restantes == 0)
    interpretar_linea();
  else if (restantes == 0)
    interpretar_fragmento();
  else
    mover_jugador();
  cout <<"linea actual: " <<linea << endl;
  cout <<"fragmento actual: "<< fragmento << endl;
  cout <<"restantes actual: "<< restantes << endl;
}

void read_controles() {
  if (filesystem::exists("death.txt")) {
    set_posicion_inicial();
    remove("death.txt");
  } else if (!esta_detenido()){
    cout << "Caminando..." << endl;
    caminar_un_paso();
  } else {
    cout << "a" << endl;
    getline(cin, input_actual);
    cout << "b" << endl;
    if (regex_match(input_actual, patron_movimiento)){
      linea = input_actual;
    } else if (regex_match(input_actual, patron_salir))
      terminar_juego();
    else
      cout << "¡Comando inválido!" << endl;
  }
}

int *init_datos() {
  // Crear el objeto de memoria compartida fd: file descriptor
  mi_fd = shm_open(nombre_del_shm.data(), O_CREAT | O_RDWR, 0666);

  // Asignar tamaño a objeto de memoria compartida
  ftruncate(mi_fd, tamano_del_shm);

  // Mapear la memoria compartida
  return (int *)mmap(0, tamano_del_shm, PROT_READ | PROT_WRITE, MAP_SHARED, mi_fd, 0);
}

int main() {
  datos = init_datos();
  set_posicion_inicial();
  // cin.get(); //pausa
  while (!filesystem::exists("finished.txt")) {
    read_controles();
    memcpy(datos, posicion, 2 * sizeof(int));
    wait_control();
  }
  // Limpiar recursos
  remove("finished.txt");
  munmap(datos, tamano_del_shm);
  close(mi_fd);
  shm_unlink(nombre_del_shm.data());
  return 0;
}
