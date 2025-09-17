#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const size_t tamano_del_shm = 1024;
const char *nombre_del_shm = "/MiMemoriaCompartida";
int mi_fd;
int *datos;
string aviso_de_datos = "Datos recibidos:";

int main() {
  // Abrir el objeto de memoria compartida existente
  int mi_fd = shm_open(nombre_del_shm, O_RDONLY, 0666);
  if (mi_fd == -1) {
    perror("Error al abrir la memoria compartida");
    return 1;
  }

  // Mapear la memoria compartida
  datos = (int *)mmap(0, tamano_del_shm, PROT_READ, MAP_SHARED, mi_fd, 0);
  if (datos == MAP_FAILED) {
    perror("Error al mapear la memoria compartida");
    close(mi_fd);
    return 1;
  } else {
    // Leer datos de la memoria compartida
    cout << aviso_de_datos << endl;
    int tamano_del_mensaje = datos[0];
    cout << "arreglo de " << tamano_del_mensaje << " caracteres recibido:" << endl;
    for (int i = 1; i < tamano_del_mensaje + 1; i++) {
      cout << datos[i] << " ";
    }
    cout << endl
         << "Traducción: " << endl;
    for (int i = 1; i < tamano_del_mensaje + 1; i++) {
      cout << (char)datos[i] << " ";
    }
    cout << endl;
  }

  // Limpiar recursos
  munmap(datos, tamano_del_shm);
  close(mi_fd);

  return 0;
}
