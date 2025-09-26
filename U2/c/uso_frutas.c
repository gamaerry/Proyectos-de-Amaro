#include "fruta.h"

void despedida(struct Fruta *ultima_fruta) {
  if (ultima_fruta) {
    printf("Pila no vacia! Se ha vaciado automáticamente\n");
    ultima_fruta = clear(ultima_fruta);
  }
  printf("¡Hasta pronto!\n");
}

void mostrar_menu() {
  printf("\nIngrese opcion: \n");
  printf("1. Ingresar elemento a la pila\n");
  printf("2. Mostrar la pila\n");
  printf("3. Quitar el ultimo elemento\n");
  printf("4. Limpiar pila\n");
  printf("5. Salir\n");
}

int main() {
  struct Fruta *ultima_fruta = NULL;
  int opcion;
  int scanf_result;
  do {
    mostrar_menu();
    scanf_result = scanf("%d", &opcion);
    if (scanf_result != 1) {
      printf("¡No ingresó dígito válido! ");
      while (getchar() != '\n')
        ;          /* Limpia buffer */
      opcion = -1; /* Forzar opción inválida */
    }
    if (opcion == 1)
      ultima_fruta = push(ultima_fruta);
    else if (opcion == 2 && ultima_fruta)
      show(ultima_fruta);
    else if (opcion == 3 && ultima_fruta)
      ultima_fruta = pop(ultima_fruta);
    else if (opcion == 4 && ultima_fruta)
      ultima_fruta = clear(ultima_fruta);
    else if (opcion == 5)
      despedida(ultima_fruta);
    else
      printf("No se realizó ninguna operación\n");
  } while (opcion != 5);

  return 0;
}
