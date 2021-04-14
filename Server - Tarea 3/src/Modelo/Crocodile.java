package Modelo;

public class Crocodile {
    int PosX;
    int PosY;
    int Speed;
    String Tipo;

    public Crocodile() { }

    public Crocodile(int posX, int posY, int speed, String tipo) {
        PosX = posX;
        PosY = posY;
        Speed = speed;
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

    public int getSpeed() {
        return Speed;
    }

    public void setSpeed(int speed) {
        Speed = speed;
    }

    public String getTipo() {
        return Tipo;
    }

    public void setTipo(String tipo) {
        Tipo = tipo;
    }
}
