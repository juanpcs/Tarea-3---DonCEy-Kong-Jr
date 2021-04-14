package Controlador;

public class Controlador {

    public Controlador() {
    }

    public String get_random_fruit(){
        String[] frutas = {"banano", "manzana", "mango"};
        String fruta;
        int valorEntero = (int) Math.floor(Math.random()*3);
        fruta = frutas[valorEntero];
        return fruta;
    }

    public int get_random_points(){
        int[] Puntos = {100, 200, 300,400,500};
        int puntos;
        int valorEntero = (int) Math.floor(Math.random()*5);
        puntos = Puntos[valorEntero];
        return puntos;

    }

}
