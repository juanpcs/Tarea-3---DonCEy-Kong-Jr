package Vista;
import Modelo.Partida;
import Controlador.Servidor;

import java.util.ArrayList;
import java.util.List;


public class Main {

    public static List<Partida> partidas = new ArrayList<>();
    public static void main(String[] args) {
        Partida partida = new Partida();
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



