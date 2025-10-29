import java.util.Scanner;

public class UsoDeListaDoblementeEnlazada {
  static LibreriaListaDoblementeEnlazada lib = LibreriaListaDoblementeEnlazada.INSTANCE;
  static Scanner sc = new Scanner(System.in);

  public static void despedida() {
    if (lib.clear())
      System.out.println("¡Playlist no vacia! Se ha vaciado automáticamente");
    else
      System.out.println("¡Hasta pronto!");
  }

  public static String menu() {
    String is_circular = lib.is_loop() ? "Quitar" : "Poner";
    String is_aleatorio = lib.is_random() ? "Quitar" : "Poner";
    String nombre = lib.get_nombre_playlist();
    return "\n" + nombre + " (" + lib.get_contador() + " canciones)\n" +
        " 1. Cambiar nombre a la playlist\n" +
        " 2. Llenar playlist\n" +
        " 3. Ingresar a la playlist(before this track)\n" +
        " 4. Ingresar a la playlist(after this track)\n" +
        " 5. Reproducir playlist\n" +
        " 6. " + is_circular + " playlist en bucle " + (lib.is_loop() ? "(Activado)" : "(Desactivado)") + "\n" +
        " 7. " + is_aleatorio + " playlist en aleatorio " + (lib.is_random() ? "(Activado)" : "(Desactivado)") + "\n" +
        " 8. Eliminar de la playlist\n" +
        " 9. Limpiar playlist\n" +
        " 0. Salir\n ";
  }

  public static String get_linea(String mensaje) {
    System.out.print(mensaje);
    return sc.nextLine();
  }

  public static int get_int_valido(String mensaje) {
    System.out.print(mensaje);
    if (!sc.hasNextInt()) {
      System.out.print("¡No ingresó dígito válido! ");
      sc.nextLine(); // limpiar entrada inválida
      return -1;
    }
    int opcion = sc.nextInt();
    sc.nextLine(); // consumir salto de línea
    return opcion;
  }

  public static String rango() {
    int canciones_actuales = lib.get_contador() - 1;
    return "[0, " + (canciones_actuales < 0 ? "0" : canciones_actuales) + "]";
  }

  public static void manage_option(int opcion, int indice) {
    switch (opcion) {
      case 1:
        lib.set_nombre_playlist(get_linea("Ingrese nuevo nombre: "));
        break;
      case 2:
        indice = get_int_valido("Ingrese el número de canciones a agregar: ");
        if (indice < 0)
          break;
        for (; indice > 0; indice--)
          lib.insert(false, lib.get_contador() - 1, get_linea("Ingrese nombre de la canción: "));
        break;
      case 3:
        indice = get_int_valido("Ingrese el índice " + rango() + ": ");
        if (indice < 0)
          break;
        if (!lib.insert(true, indice, get_linea("Ingrese nombre de la canción: "))) // before
          System.out.println("¡Índice fuera del rango! El rango de índices actual es: " + rango());
        break;
      case 4:
        indice = get_int_valido("Ingrese el índice " + rango() + ": ");
        if (indice < 0)
          break;
        if (!lib.insert(false, indice, get_linea("Ingrese nombre de la canción: "))) // after
          System.out.println("¡Índice fuera del rango! El rango de índices actual es: " + rango());
        break;
      case 5:
        if (!lib.play())
          System.out.println("¡Playlist vacía!");
        break;
      case 6:
        if (lib.is_loop()) // note que si la playlist está vacía, esto no efectua ningún cambio
          lib.disable_loop();
        else
          lib.enable_loop();
        break;
      case 7:
        lib.set_random(!lib.is_random());
        break;
      case 8:
        indice = get_int_valido("Ingrese el índice a eliminar " + rango() + ": ");
        if (indice < 0)
          break;
        if (!lib.remove_in(indice))
          System.out.println("¡Índice fuera del rango! El rango de índices actual es: " + rango());
        break;
      case 9:
        if (!lib.clear())
          System.out.println("¡Playlist vacía!");
        break;
      case 0:
        despedida();
        break;
      default:
        System.out.println("No se realizó ninguna operación");
    }
  }

  public static void main() {
    int opcion = 0;
    int indice = 0;
    do {
      opcion = get_int_valido(menu());
      manage_option(opcion, indice);
    } while (opcion != 0);
  }
}
