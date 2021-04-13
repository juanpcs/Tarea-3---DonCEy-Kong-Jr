package Modelo;

public class Fruit {
    int PosX = 0;
    int PosY = 0;
    int Points = 100;
    String Tipo = "manzana";

    public Fruit(int posX, int posY, int points, String tipo) {
        PosX = posX;
        PosY = posY;
        Points = points;
        Tipo = tipo;
    }

    public int getPosX() {
        return PosX;
    }

    public void setPosX(int posX) {
        PosX = posX;
    }

    public int getPosY() {
        return PosY;
    }

    public void setPosY(int posY) {
        PosY = posY;
    }

    public int getPoints() {
        return Points;
    }

    public void setPoints(int points) {
        Points = points;
    }

    public String getTipo() {
        return Tipo;
    }

    public void setTipo(String tipo) {
        Tipo = tipo;
    }

    public void create_random_fruit(){
        /* Por definir */;
    }

    public void delete_fruit(){
        /* Por definir */;
    }
}

