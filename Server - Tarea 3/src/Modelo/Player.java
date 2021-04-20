package Modelo;

public class Player {
    java.lang.Integer posX;
    java.lang.Integer posY;
    java.lang.Integer speed;
    java.lang.Integer points;
    java.lang.Integer lifes;
    java.lang.Boolean state;

    public Player() { }

    public Player(java.lang.Integer posX,java.lang.Integer posY,java.lang.Integer points,java.lang.Integer lifes){
        this.posX = posX;
        this.posY = posY;
        this.speed = 1;
        this.points = points;
        this.lifes = lifes;
        this.state = true;
}

    public java.lang.Integer getPosX() {
        return posX;
    }

    public void setPosX(java.lang.Integer posX) {
        this.posX = posX;
    }

    public java.lang.Integer getPosY() {
        return posY;
    }

    public void setPosY(java.lang.Integer posY) {
        this.posY = posY;
    }

    public java.lang.Integer getSpeed() {
        return speed;
    }

    public void setSpeed(java.lang.Integer speed) {
        this.speed = speed;
    }

    public java.lang.Integer getPoints() {
        return points;
    }

    public void setPoints(java.lang.Integer points) {
        this.points = points;
    }

    public java.lang.Integer getLifes() {
        return lifes;
    }

    public void setLifes(java.lang.Integer lifes) {
        this.lifes = lifes;
    }

    public java.lang.Boolean getState() {
        return state;
    }

    public void muerte() {
        this.state = false;
    }

    public void addPoints(java.lang.Integer points){
        this.points += points;
    }

    public void addLifes(){
        this.lifes += 1;
    }

    public void loseLifes(){
        this.lifes -=1;
        this.posX =0;
        this.posY =0;
    }
}
