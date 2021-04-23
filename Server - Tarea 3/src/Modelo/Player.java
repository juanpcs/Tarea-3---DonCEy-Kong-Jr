package Modelo;

/**
 * Clase del jugador
 * @author Juan Pablo
 */
public class Player {
    private java.lang.Integer posX;
    private java.lang.Integer posY;
    private java.lang.Integer speed;
    private java.lang.Integer points;
    private java.lang.Integer lifes;
    private java.lang.Boolean state;

    public Player() { }

    /**
     * Constructor del jugador
     * @param posX posicion en x
     * @param posY posicion en y
     * @param points puntaje del jugador
     * @param lifes cantidad de vidas
     */
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

    /**
     * Función que aumenta la posicion en x del jugador
     * @param pasos cantidad de pixel que se va a mover el jugador
     * @return string con la posicion en x del jugador
     */
    public java.lang.String modificarPosX(java.lang.Integer pasos){
        posX += pasos;
        return posX +";";
    }

    /**
     * Función que aumenta la posicion en y del jugador
     * @param pasos cantidad de pixeles que aumenta o decrementa
     * @return string con la posición actualizada en y
     */
    public java.lang.String modificarPosY(java.lang.Integer pasos){
        posY += pasos;
        return posY +";";
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

    /**
     * Funcion que aumenta los puntos del jugador por cada furta obtenida
     * @param points cantidad de puntos obtenidos
     */
    public void addPoints(java.lang.Integer points){
        this.points += points;
    }

    public void addLifes(){
        this.lifes += 1;
    }

    /**
     * Función encargada de eliminar vidas al jugador
     */
    public void loseLifes(){
        this.lifes -=1;
        this.posX =0;
        this.posY =0;
    }

    /**
     * Da una vida extra al jugador.
     */
    public void aumentarVidas(){
        this.lifes++;
    }
}
