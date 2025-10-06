#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Cola {
  struct Cola *anterior;
  char nombre[];
} *primero;

struct Cola *newCola(char *nombre) {
  struct Cola *nueva = malloc(sizeof(struct Cola) + strlen(nombre) + 1);
  nueva->anterior = NULL;
  nombre[strcspn(nombre, "\n")] = '\0';
  strcpy(nueva->nombre, nombre);
  return nueva;
}

struct Cola *get_last() {
  struct Cola *ultimo = primero;
  if (primero)
    while (ultimo->anterior)
      ultimo = ultimo->anterior;
  return ultimo;
}

void enqueue(struct Cola *nuevo) { // formar un nuevo en la cola
  if (primero) {
    struct Cola *ultimo = get_last();
    ultimo->anterior = nuevo;
  } else
    primero = nuevo;
}

struct Cola *dequeue() { // sacar al primero de la cola
  struct Cola *por_salir = primero;
  primero = primero ? primero->anterior : NULL;
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
  printf("1. Ingresar elemento a la cola\n");
  printf("2. Mostrar la cola\n");
  printf("3. Quitar el primer elemento\n");
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
    printf("¡No ingresó dígito válido! ");
    ignore();
    opcion = -1; /* Forzar default */
  }
  return opcion;
}

int main() {
  int opcion;
  do {
    mostrar_menu();
    opcion = recibir_opcion_valida();
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
    default:
      printf("No se realizó ninguna operación");
    }
  } while (opcion != 5);
  return 0;
}
