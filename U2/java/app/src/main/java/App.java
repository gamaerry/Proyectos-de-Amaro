import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Path;

public class App {
  public static void main(String[] args) throws IOException, URISyntaxException {
    // Obtiene la ruta del recurso
    var uri = App.class.getResource("/tazo1.txt").toURI();
    var path = Path.of(uri);
    
    // Lee todo el archivo en un String
    var contenido = Files.readString(path);

    // Imprime
    System.out.println(contenido);
  }
}
