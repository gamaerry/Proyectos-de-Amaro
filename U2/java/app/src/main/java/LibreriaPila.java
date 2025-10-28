import com.sun.jna.Library;
import com.sun.jna.Native;

public interface LibreriaPila extends Library {
  LibreriaPila INSTANCE = Native.load("LibreriaPila", LibreriaPila.class);

  int empty();

  void push(String nombre);

  void pop();

  void clear();

  void show();

}
