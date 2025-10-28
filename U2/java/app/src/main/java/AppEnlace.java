import java.util.Scanner;

public class AppEnlace {
  public static void main(String[] args) {
    System.out.println("Plataforma: " + System.getProperty("os.name") + " - " + System.getProperty("os.arch"));
    // testPractica7();
    UsoDePilas.main();
  }

  // métodos de la practica 7:
  static void testPractica7() {
    LibreriaPractica7.INSTANCE.saludo();
    LibreriaPractica7.INSTANCE.saludoConNombre(" Luis");
  }
}
