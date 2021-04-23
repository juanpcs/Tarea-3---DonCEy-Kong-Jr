package Vista;
import Modelo.Partida;
import Controlador.Servidor;


public class Main {
    public static Partida[] part = new Partida[2];
    public static void main(String[] args) {
        //System.out.println(partida.getPosJugador());
        //System.out.println(partida.attackCroc());*/
        Servidor server = new Servidor();
        server.iniciar();
       /*Controlador C = new Controlador();
        Fruit fruta1 = new Fruit(1,1,C.get_random_points(),C.get_random_fruit());
        Fruit fruta2 = new Fruit();
        System.out.println(fruta1.getTipo());
        System.out.println(fruta1.getPoints());*/
    }

}



