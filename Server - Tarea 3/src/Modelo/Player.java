package Modelo;

public class Player {
    int PosX;
    int PosY;
    float Speed;
    int Points;
    int Lifes;
    String State = "vivo";

    public Player() { }

    public Player(int posX,int posY,float speed,int points,int lifes, String state){
        PosX = posX;
        PosY = posY;
        Speed = speed;
        Points = points;
        Lifes = lifes;
        State = state;
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

    public float getSpeed() {
        return Speed;
    }

    public void setSpeed(float speed) {
        Speed = speed;
    }

    public int getPoints() {
        return Points;
    }

    public void setPoints(int points) {
        Points = points;
    }

    public int getLifes() {
        return Lifes;
    }

    public void setLifes(int lifes) {
        Lifes = lifes;
    }

    public String getState() {
        return State;
    }

    public void setState(String state) {
        State = state;
    }

    public void add_Points(int points){
        setPoints(getPoints() + points);
    }

    public void add_Lifes(int lifes){
        setLifes(getLifes() + lifes);
    }

    public void lose_Lifes(int lifes){
        setLifes(getLifes() - lifes);
    }

    public void Die(){
        if(getLifes()<1){
            setState("muerto");
        }
        setState("vivo");
    }
}
