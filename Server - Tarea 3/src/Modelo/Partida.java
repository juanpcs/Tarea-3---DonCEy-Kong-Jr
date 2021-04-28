package Modelo;

import java.util.ArrayList;
import java.util.List;

/**
 * Clase encargada de manejar la partida
 */
public class Partida {
    private Player jugador;
    private List<Fruit> frutas;
    private List<Crocodile> cocodrilos;
    private java.lang.Integer espectadores;
    private java.lang.Integer numCroc;
    private java.lang.Integer numFrut;
    private java.lang.Integer speed= 1;

    /**
     * Constructor de la clase
     */
    public Partida(){
        this.jugador = new Player(150,800,0,3);
        this.frutas = new ArrayList<Fruit>();
        this.frutas.add(new Fruit(1,25,50,0,100));
        this.frutas.add(new Fruit(2,158,20,0,100));
        this.frutas.add(new Fruit(3,200,200,0,200));
        this.cocodrilos = new ArrayList<Crocodile>();
        this.cocodrilos.add(new Crocodile(1,415,280,0,speed));
        this.cocodrilos.add(new Crocodile(2,525,280,1,speed));
        this.espectadores =0;
        this.numCroc=2;
        this.numFrut=3;
    }

    /**
     * Obtiene la posicion en x  y y del jugador, separado por punto y coma
     * @return string con la posicion del jugador separada por punto y coma
     */
    public java.lang.String getPosJugador() {
        java.lang.String result= "";
        result = jugador.getPosX() +";"+jugador.getPosY();
        return result;
    }

    /**
     * Retorna la cantidad de vidas del jugador
     * @return String con las vidas restantes
     */
    public java.lang.String getHearts(){
        return jugador.getLifes()+";";
    }

    /**
     * Funcion que retorna el puntaje
     * @return string del puntaje del jugador
     */
    public java.lang.String getPuntaje(){
        return jugador.getPoints()+";";
    }

    /**
     * Metodo que devuelve una fruta en especifico
     * @param numFrut id de la fruta
     * @return objeto Fruit que es la fruta especificada
     */
    public Fruit getFruta(java.lang.Integer numFrut) {
        Fruit frut = null;
        for (java.lang.Integer i =0; i< this.numFrut;i++){
            if(numFrut == (frutas.get(i).num)){
                frut = frutas.get(i);
                break;
            }
        }
        return frut;
    }
    public java.lang.String getVidas(){
        return jugador.getLifes()+";";
    }

    public void setFrutas(List<Fruit> frutas) {
        this.frutas = frutas;
    }

    /**
     * Metodo que retorna un cocodrilo en especifico
     * @param numCroc id del cocodrilo
     * @return objeto de tipo Crocodile que es el cocodrilo deseado
     */
    public Crocodile getCocodrilo(java.lang.Integer numCroc) {
        Crocodile croc = null;
        for (java.lang.Integer i =0; i< this.numCroc;i++){
            if(numCroc == (cocodrilos.get(i).num)){
                croc = cocodrilos.get(i);
                break;
            }
        }
        return croc;
    }

    /**
     * Metodo que devuelve la posicion del jugador en x aumentada en 10
     * @return posicion en X
     */
    public java.lang.String moverDere(){
        return jugador.modificarPosX(10);
    }
    /**
     * Metodo que devuelve la posicion del jugador en x decrementada en 10
     * @return posicion en X
     */
    public java.lang.String moverIzq(){
        return jugador.modificarPosX(-10);
    }
    /**
     * Metodo que devuelve la posicion del jugador en y aumentada en 10
     * @return posicion en y
     */
    public java.lang.String moverArriba(){
        return jugador.modificarPosY(-10);
    }
    /**
     * Metodo que devuelve la posicion del jugador en y decrementada en 10
     * @return posicion en y
     */
    public java.lang.String moverAbajo(){
        return jugador.modificarPosY(10);
    }
    public void setCocodrilos(List<Crocodile> cocodrilos) {
        this.cocodrilos = cocodrilos;
    }

    /**
     * Devuele la cantidad de espectadores del jugador
     * @return cantidad de espectadores del jugador
     */
    public java.lang.Integer getEspectadores() {
        return espectadores;
    }

    /**
     * Aumenta en 1 los espectadores
     */
    public void setEspectadores() {
        this.espectadores +=1;
    }

    /**
     * desconecta un espectador de la partida
     */
    public void desconEspec(){
        espectadores -=1;
    }
    public java.lang.Integer getNumCroc() {
        return numCroc;
    }

    /**
     * Metodo que obtiene todas la fruta y sus atibutos y los convierte en string
     * @return total de las frutas separadas por , y ;
     */
    public java.lang.String getFrutas(){
        java.lang.String respuesta = "";
        for (java.lang.Integer i=0; i<frutas.size();i++){
            Fruit fruta = frutas.get(i);
            respuesta += fruta.num + ";"+fruta.posX +";"+ fruta.posY+";"+fruta.atributoEsp+";"+fruta.tipo+";";
        }
        return respuesta;
    }
    /**
     * Metodo que obtiene todas los cocodrilos y sus atibutos y los convierte en string
     * @return total de los cocodrilos separadas por , y ;
     */
    public java.lang.String getCocodrilos(){
        java.lang.String respuesta = "";
        java.lang.Integer largo=0;
        for (java.lang.Integer i=0; i<cocodrilos.size();i++){
            Crocodile croc = cocodrilos.get(i);
            largo++;
            respuesta += croc.posX +";"+ croc.posY+";"+croc.tipo+";";
        }
        respuesta=largo+";"+respuesta;
        return respuesta;
    }
    /**
     * Metodo que obtiene los atributos del jugador
     * @return string con todos los atributos del jugador separados por ;
     * */
    public java.lang.String getJugador(){
        java.lang.String result = jugador.getPosX() +";"+jugador.getPosY()+";"+jugador.getLifes()+";"+jugador.getPoints()+";"+jugador.getState()+";"+jugador.getSpeed()+";";
        return result;
    }

    /**
     * Metodo que elimina un cocodrilo por su id
     * @param numCroc id del cocodrilo
     */
    public void eliminarCroc(java.lang.Integer numCroc){
        cocodrilos.remove(getCocodrilo(numCroc));
        java.lang.Integer i =1;
        for(Crocodile c : cocodrilos){
            c.setNum(i);
            i++;
        }
        numCroc --;
    }

    /**
     * Metodo que elimina las frutas por su id
     * @param numFrut id de la fruta deseada
     */
    public void eliminarFruit(java.lang.Integer numFrut){
        jugador.addPoints(getFruta(numFrut).getAtributoEsp());
        frutas.remove(getFruta(numFrut));
        java.lang.Integer i =1;
        for(Fruit f : frutas){
            f.setNum(i);
            i++;
        }
        numFrut --;
    }
    public java.lang.String getVidPunt(){
        return jugador.getLifes()+";"+jugador.getPoints()+";";
    }

    /**
     * Metodo que elimina el una vida del jugador al ser atacado por un cocodrilo y lo devuelve al inicio
     * @return posicion del jugador con las vidas restantes
     */
    public java.lang.String attackCroc(){
        if(jugador.getLifes()>0) {
            jugador.loseLifes();
            java.lang.String respuesta = jugador.getPosX() + ";" + jugador.getPosY() + ";" + jugador.getLifes();
            return respuesta;
        }else{
            return "GameOver";
        }

    }

    /**
     * Metodo que crea un nuevo cocodrilo en la partida
     * @param posx pos en x del cocodrilo
     * @param posy pos en y del cocodrilo
     * @param tipo tipo de cocodrilo
     * @param speed velocidad del cocodrilo
     */
    public void crearCocodrilo(java.lang.Integer posx,java.lang.Integer posy,java.lang.Integer tipo,java.lang.Integer speed ){
        numCroc +=1;
        cocodrilos.add(new Crocodile(numCroc,posx,posy,tipo,speed));
    }

    /**
     * Metodo que resetea el juego
     */
    private void reset(){
        this.jugador.setPosX(150);
        this.jugador.setPosY(800);
        frutas.clear();
        cocodrilos.clear();
        this.frutas.add(new Fruit(1,25,50,0,100));
        this.frutas.add(new Fruit(2,158,20,0,100));
        this.frutas.add(new Fruit(3,200,200,0,200));
        this.cocodrilos = new ArrayList<Crocodile>();
        this.cocodrilos.add(new Crocodile(1,180,280,0,speed));
        this.cocodrilos.add(new Crocodile(2,375,280,1,speed));
    }

    /**
     * Metodo que aplica cuando gana el jugador, le da una vida y lo devuelve al inicio.
     */
    public void win(){
        this.jugador.aumentarVidas();
        speed +=1;
        reset();
    }
}
