package Vista;
import Modelo.Partida;
import Controlador.Servidor;


public class Main {
    public static Partida[] part = new Partida[2];
    public static void main(String[] args) {
        Servidor server = new Servidor();
        server.iniciar();
    }

}



