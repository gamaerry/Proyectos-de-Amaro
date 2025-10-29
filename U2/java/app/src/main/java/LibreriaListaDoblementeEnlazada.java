import com.sun.jna.Library;
import com.sun.jna.Native;

public interface LibreriaListaDoblementeEnlazada extends Library {
  LibreriaListaDoblementeEnlazada INSTANCE = Native.load("LibreriaListaDoblementeEnlazada", LibreriaListaDoblementeEnlazada.class);

  boolean is_loop();

  int get_contador();

  void disable_loop();

  void enable_loop();

  boolean insert(boolean before, int indice, String nombre);

  boolean remove_in(int indice);

  boolean clear();

  String get_nombre_playlist();

  void set_nombre_playlist(String _nombre);

  boolean is_random();

  void set_random(boolean _aleatorio);

  boolean play();

}
