import java.util.Scanner;

public class AppEnlace {
  public static void main(String[] args) {
    System.out.println("Plataforma: " + System.getProperty("os.name") + " - " + System.getProperty("os.arch"));
    // testPractica7();
    UsoDePilas.main();
  }

  // métodos del hello world:
  static void testPractica7() {
    Practica7.INSTANCE.saludo();
    Practica7.INSTANCE.saludoConNombre(" Luis");
  }

}
