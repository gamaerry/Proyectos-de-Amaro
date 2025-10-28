import com.sun.jna.Library;
import com.sun.jna.Native;

public interface Practica7 extends Library {
  Practica7 INSTANCE = Native.load("practica7", Practica7.class);

  void saludo();

  void saludoConNombre(String nombre);
}
