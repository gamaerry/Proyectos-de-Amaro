import java.util.Scanner;

public class UsoDePilas {
  static LibreriaPila lib = LibreriaPila.INSTANCE;
  public static void main() {
    Scanner escaner = new Scanner(System.in);
    int opcion;
    do {
      mostrarMenu();
      if (!escaner.hasNextInt()) {
        System.out.print("¡No ingresó dígito válido! ");
        escaner.next();
        opcion = 0;
      } else
        opcion = escaner.nextInt();
      if (opcion == 1)
        lib.push();
      else if (opcion == 2 && lib.empty() == 0)
        lib.show();
      else if (opcion == 3 && lib.empty() == 0)
        lib.pop();
      else if (opcion == 4 && lib.empty() == 0)
        lib.clear();
      else if (opcion == 5)
        despedida(lib.empty() == 0);
      else
        System.out.println("No se realizó ninguna operación");
    } while (opcion != 5);
    escaner.close();
  }

  static void despedida(boolean hayElementos) {
    if (hayElementos) {
      System.out.println("¡Pila no vacia! Se ha vaciado automáticamente");
      lib.clear();
    }
    System.out.println("¡Hasta pronto!");
  }

  static void mostrarMenu() {
    System.out.println("\nIngrese opcion: ");
    System.out.println("1. Ingresar elemento a la pila");
    System.out.println("2. Mostrar la pila");
    System.out.println("3. Quitar el utilmo elemento");
    System.out.println("4. Limpiar pila");
    System.out.println("5. Salir");
  }
}
