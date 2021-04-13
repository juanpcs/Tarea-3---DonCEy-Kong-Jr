package Modelo;

public class Crocodile {
    int PosX=0;
    int PosY=0;
    int Speed=1;
    String Color = "azul";

    public Crocodile(int posX, int posY, int speed, String color) {
        PosX = posX;
        PosY = posY;
        Speed = speed;
        Color = color;
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

    public String getColor() {
        return Color;
    }

    public void setColor(String color) {
        Color = color;
    }
}
