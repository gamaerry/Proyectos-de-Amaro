import com.sun.jna.Library;
import com.sun.jna.Native;

public interface LibreriaPractica7 extends Library {
  LibreriaPractica7 INSTANCE = Native.load("LibreriaPractica7", LibreriaPractica7.class);

  void saludo();

  void saludoConNombre(String nombre);
}
