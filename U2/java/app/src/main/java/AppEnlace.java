import com.sun.jna.Library;
import com.sun.jna.Native;

interface MiLibreria extends Library {
    MiLibreria INSTANCE = Native.load("practica7", MiLibreria.class);
    void saludo();
    void saludoConNombre(String nombre);
}

public class AppEnlace {
    public static void main(String[] args) {
        MiLibreria.INSTANCE.saludo();
        MiLibreria.INSTANCE.saludoConNombre("Luis");
    }
}
