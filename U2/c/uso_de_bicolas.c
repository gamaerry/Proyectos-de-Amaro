#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cola {
  struct Cola *anterior;
  char nombre[];
} *primero;

int al_inicio = 0;

struct Cola *newCola(char *nombre) {
  struct Cola *nueva = malloc(sizeof(struct Cola) + strlen(nombre) + 1);
  nueva->anterior = NULL;
  nombre[strcspn(nombre, "\n")] = '\0';
  strcpy(nueva->nombre, nombre);
  return nueva;
}

struct Cola *get_last(int to_delete) {
  struct Cola *ultimo = primero;
  struct Cola *penultimo;
  if (primero) {
    while (ultimo->anterior){
      penultimo = ultimo;
      ultimo = penultimo->anterior;
    }
    if (to_delete)
      penultimo->anterior = NULL;
  }
  return ultimo;
}

void enqueue(struct Cola *nuevo) { // formar un nuevo en la cola
  if (primero) {
    if (al_inicio) {
      nuevo->anterior = primero;
      primero = nuevo;
    } else {
      struct Cola *ultimo = get_last(0);
      ultimo->anterior = nuevo;
    }
  } else
    primero = nuevo;
}

struct Cola *dequeue() { // sacar al primero de la cola
  struct Cola *por_salir;
  if (al_inicio) {
    por_salir = primero;
    primero = primero ? primero->anterior : NULL;
  } else
    por_salir = get_last(1);
  return por_salir;
}

int clear() {
  if (primero) {
    struct Cola *a_limpiar;
    do {
      a_limpiar = dequeue();
      free(a_limpiar);
    } while (primero);
    return 1;
  } else
    return 0;
}

int print() {
  if (primero) {
    struct Cola *actual = primero;
    while (actual) {
      printf("[%p]: %s\n", (void *)actual, actual->nombre);
      printf("(Adelante de %s)\n\n", actual->anterior ? actual->anterior->nombre : "ninguno");
      actual = actual->anterior;
    }
    return 1;
  } else
    return 0;
}

// Métodos del main:

void despedida() {
  if (clear())
    printf("¡Cola no vacia! Se ha vaciado automáticamente\n");
  else
    printf("¡Hasta pronto!\n");
}

void mostrar_menu() {
  printf("\nIngrese opcion:\n");
  printf("1. Ingresar elemento\n");
  printf("2. Mostrar la cola\n");
  printf("3. Quitar elemento\n");
  printf("4. Limpiar cola\n");
  printf("5. Salir\n");
}

void ignore() {
  while (getchar() != '\n')
    ;
}

char *get_line() {
  char *nueva_linea;
  size_t tamano;
  getline(&nueva_linea, &tamano, stdin);
  return nueva_linea;
}

struct Cola *get_nuevo_elemento() {
  char *nombre;
  printf("Ingrese nombre del nuevo elemento: ");
  ignore();
  return newCola(get_line());
}

int recibir_opcion_valida() {
  int opcion;
  int scanf_result = scanf("%d", &opcion);
  if (scanf_result != 1) {
    ignore();
    opcion = -1;
  }
  return opcion;
}

int main() {
  int opcion;
  do {
    mostrar_menu();
    opcion = recibir_opcion_valida();
    if (opcion == 1 || opcion == 3) {
      printf("Indique (0) si es al final o (cualquier otro digito) si es al inicio: ");
      al_inicio = recibir_opcion_valida();
      opcion = al_inicio == -1 ? -1 : opcion;
    }
    switch (opcion) {
    case 1:
      enqueue(get_nuevo_elemento());
      break;
    case 2:
      if (!print())
        printf("¡Cola vacia!");
      break;
    case 3:
      free(dequeue());
      break;
    case 4:
      if (!clear())
        printf("!Cola vacia!");
      break;
    case 5:
      despedida();
      break;
    case -1:
      printf("¡No ingresó dígito válido! ");
    default:
      printf("No se realizó ninguna operación\n");
    }
  } while (opcion != 5);
  return 0;
}
