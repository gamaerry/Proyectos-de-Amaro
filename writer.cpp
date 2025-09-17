#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

// Variables necesarias
const size_t tamano_del_shm = 1024; // shm: Shared Memory
const char *nombre_del_shm = "/MiMemoriaCompartida";
const string msj_introduzca = "Escriba el mensaje a enviar a la memoria compartida:";
const string msj_exito = "Mensaje escrito, presione enter para finalizar.";
string cadena_a_enviar;
int mi_fd;
char *datos;

int main() {
  // Crear el objeto de memoria compartida fd: file descriptor
  mi_fd = shm_open(nombre_del_shm, O_CREAT | O_RDWR, 0666);
  if (mi_fd == -1) {
    perror("Error al crear la memoria compartida");
    return 1;
  }

  // Asignar tamaño a objeto de memoria compartida
  if (ftruncate(mi_fd, tamano_del_shm) == -1) {
    perror("Error al configurar el tamaño");
    close(mi_fd);
    return 1;
  }

  // Mapear la memoria compartida
  datos = (char *)mmap(0, tamano_del_shm, PROT_READ | PROT_WRITE, MAP_SHARED, mi_fd, 0);
  if (datos == MAP_FAILED) {
    perror("Error al mapear la memoria compartida");
    close(mi_fd);
    return 1;
  }

  // Escribir datos en la memoria compartida
  cout << msj_introduzca << endl;
  getline(cin, cadena_a_enviar);
  int tamano_del_msj = cadena_a_enviar.size() + 1;

  // Traducir a ascii
  int* arreglo_a_enviar = (int*) malloc(tamano_del_msj * sizeof(int));
  arreglo_a_enviar[0]=cadena_a_enviar.size();
  for(int i=0; i<tamano_del_msj; i++){
    arreglo_a_enviar[i+1] = static_cast<int>(cadena_a_enviar[i]);
  }

  // Enviar al shared memory (donde lo leerá el receptor)
  memcpy((int*) datos, arreglo_a_enviar, tamano_del_msj * sizeof(int));
  cout << msj_exito << endl;
  cin.get();

  // Limpiar recursos
  munmap(datos, tamano_del_shm);
  close(mi_fd);
  shm_unlink(nombre_del_shm);

  return 0;
}
