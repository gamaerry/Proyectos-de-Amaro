import java.io.IOException;
import java.io.InputStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;
import java.util.Stack;

public class App {
  static Stack<Tazo> tazos = new Stack<>();
  static int[] marcador = new int[2];
  static int puntajeActual = 0;
  static int random = 0;
  static int jugadorActual = 1;

  public static void main(String[] args) throws Exception {
    llenarPilaDeTazos();
    jugar();
  }

  static void llenarPilaDeTazos() {
    tazos.add(new Tazo("Normal", 1));
    tazos.add(new Tazo("Normal", 1));
    tazos.add(new Tazo("Dorado", 3));
    tazos.add(new Tazo("Plateado", 2));
    tazos.add(new Tazo("Normal", 1));
    tazos.add(new Tazo("Plateado", 2));
    tazos.add(new Tazo("Normal", 1));
    tazos.add(new Tazo("Normal", 1));
    tazos.add(new Tazo("Dorado", 3));
    tazos.add(new Tazo("Normal", 1));
  }

  static void jugar() throws Exception {
    // System.out.println(tazos.size());
    imprimirPilaActualDeTazos();
    while (!tazos.isEmpty()) {
      puntajeActual = 0;
      jugadorActual = (jugadorActual + 1) % 2;
      esperarAlJugador();
      random = (int) (Math.random() * 6);
      anunciarResultados();
      if (random == 0 || random == 5)
        System.out.println("(*o*) Tiro fallido ++0 tazos");
      else
        popTazo(random == 3 && tazos.size() > 3);
      System.out.println();
      imprimirPilaActualDeTazos();
      actualizarMarcador();
    }
    mostrarResultados();
  }

  static void imprimirPilaActualDeTazos() throws URISyntaxException, IOException {
    String contenido = "¡Pila de tazos vacía, fin del juego!";
    if (!tazos.isEmpty()) {
      URI uri = App.class.getResource("/tazo" + tazos.size() + ".txt").toURI();
      contenido = Files.readString(Path.of(uri));
    }
    System.out.println(contenido);
  }

  static void mostrarResultados() {
    boolean gano1 = marcador[0] > marcador[1];
    String resultado = marcador[0] == marcador[1] ? "Empate" : (gano1 ? "Gano Jugador 1" : "Gano Jugador 2");
    System.out.println(resultado);
  }

  static void actualizarMarcador() {
    marcador[jugadorActual] += puntajeActual;
    System.out.println("\tMARCADOR ACTUAL\nJugador1: " + marcador[0] + "pts\nJugador2: " + marcador[1] + "pts");
  }

  static void anunciarResultados() throws IOException, InterruptedException {
    limpiarPantalla();
    System.out.print("Resultado del jugador " + (jugadorActual + 1) + ":");
  }

  static void esperarAlJugador() throws IOException {
    System.out.print("\n(" + tazos.size() + " tazos restantes) Turno del jugador " + (jugadorActual + 1) + ":");
    System.in.read();
  }

  static Tazo popTazo(boolean critico) {
    Tazo ganado;
    if (critico) {
      System.out.println("(^_^) Tiro critico ++3 tazos");
      ganado = tazos.pop();
      System.out.print("("+ganado.tipo+") ");
      puntajeActual += ganado.valor;
      ganado = tazos.pop();
      System.out.print("("+ganado.tipo+") ");
      puntajeActual += ganado.valor;
    } else 
      System.out.println("('-') Tiro acertado ++1 tazo");
    puntajeActual++;
    ganado = tazos.pop();
    System.out.print("("+ganado.tipo+") ");
    puntajeActual += ganado.valor;
    return ganado;
  }

  static void limpiarPantalla() throws IOException, InterruptedException {
    new ProcessBuilder("clear").inheritIO().start().waitFor();
  }
}

class Tazo {
  String tipo;
  int valor;

  Tazo(String tipo, int valor) {
    this.tipo = tipo;
    this.valor = valor;
  }
}
