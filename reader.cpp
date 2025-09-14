#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const size_t tamano_del_shm = 1024;
const char *nombre_del_shm = "/MiMemoriaCompartida";
int mi_fd;
char *datos;
string aviso_de_datos = "Datos de la memoria compartida:";

int main() {
  // Abrir el objeto de memoria compartida existente
  int mi_fd = shm_open(nombre_del_shm, O_RDONLY, 0666);
  if (mi_fd == -1) {
    perror("Error al abrir la memoria compartida");
    return 1;
  }

  // Mapear la memoria compartida
  datos = (char *)mmap(0, tamano_del_shm, PROT_READ, MAP_SHARED, mi_fd, 0);
  if (datos == MAP_FAILED) {
    perror("Error al mapear la memoria compartida");
    close(mi_fd);
    return 1;
  }

  // Leer datos de la memoria compartida
  cout << aviso_de_datos << endl;
  cout << datos << endl;

  // Limpiar recursos
  munmap(datos, tamano_del_shm);
  close(mi_fd);

  return 0;
}
