package Vista;
import Modelo.Fruit;
import Controlador.Controlador;

public class Main {
    public static void main(String[] args) {
        Controlador C = new Controlador();
        Fruit fruta1 = new Fruit(1,1,C.get_random_points(),C.get_random_fruit());
        Fruit fruta2 = new Fruit();
        System.out.println(fruta1.getTipo());
        System.out.println(fruta1.getPoints());
    }
}


