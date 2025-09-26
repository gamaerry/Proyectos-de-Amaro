#include "fruta.h"

const char MSJ_PEDIR_NOMBRE[] = "Ingrese el nombre de la fruta: ";

struct Fruta *push(struct Fruta *ultima_fruta) {
  struct Fruta *nueva_fruta;
  char temp[100];

  nueva_fruta = malloc(sizeof(struct Fruta));
  printf("%s", MSJ_PEDIR_NOMBRE);

  /* Limpiar buffer - equivalente a cin.ignore() */
  while (getchar() != '\n')
    ;

  fgets(temp, sizeof(temp), stdin);
  /* Eliminar el \n que deja fgets */
  temp[strcspn(temp, "\n")] = '\0';
  strcpy(nueva_fruta->nombre, temp);

  nueva_fruta->fruta_trasera = ultima_fruta;
  return nueva_fruta;
}

struct Fruta *pop(struct Fruta *ultima_fruta) {
  struct Fruta *penultima_fruta;

  if (!ultima_fruta)
    return NULL;

  penultima_fruta = ultima_fruta->fruta_trasera;
  free(ultima_fruta);
  return penultima_fruta;
}

struct Fruta *clear(struct Fruta *ultima_fruta) {
  while (ultima_fruta != NULL)
    ultima_fruta = pop(ultima_fruta);
  return NULL;
}

int is_empty(struct Fruta *ultima_fruta) {
  return !ultima_fruta;
}

void show(struct Fruta *ultima_fruta) {
  struct Fruta *a_mostrar = ultima_fruta;

  while (a_mostrar != NULL) {
    printf("======================================\n");
    printf("‖ Nombre de la fruta: %s\n", a_mostrar->nombre);
    printf("‖ Direccion en memoria: %p\n", (void *)a_mostrar);
    printf("‖\n");
    printf("‖ (Encima de %s)\n",
           (a_mostrar->fruta_trasera ? a_mostrar->fruta_trasera->nombre : "Nulo"));
    printf("======================================\n");
    a_mostrar = a_mostrar->fruta_trasera;
  }
}
