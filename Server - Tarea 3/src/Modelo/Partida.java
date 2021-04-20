package Modelo;

import java.util.ArrayList;
import java.util.List;

public class Partida {
    Player jugador;
    List<Fruit> frutas;
    List<Crocodile> cocodrilos;
    java.lang.Integer espectadores;
    java.lang.Integer numCroc;
    java.lang.Integer numFrut;

    public Partida(){
        this.jugador = new Player(0,0,0,3);
        this.frutas = new ArrayList<Fruit>();
        this.frutas.add(new Fruit(1,25,50,"banano",100));
        this.frutas.add(new Fruit(2,158,20,"uva",100));
        this.frutas.add(new Fruit(3,200,200,"manzana",200));
        this.cocodrilos = new ArrayList<Crocodile>();
        this.cocodrilos.add(new Crocodile(1,0,20,"rojo",2));
        this.cocodrilos.add(new Crocodile(2,20,20,"azul",2));
        this.espectadores =0;
        this.numCroc=2;
        this.numFrut=3;
    }

    public java.lang.String getPosJugador() {
        java.lang.String result= "";
        result = jugador.getPosX() +";"+jugador.getPosY();
        return result;
    }
    public java.lang.String getHearts(){
        return jugador.getLifes()+";";
    }
    public java.lang.String getPuntaje(){
        return jugador.getPoints()+";";
    }

    public Fruit getFrutas(java.lang.Integer numFrut) {
        Fruit frut = null;
        for (java.lang.Integer i =0; i< this.numFrut;i++){
            if(numFrut == (frutas.get(i).num)){
                frut = frutas.get(i);
                break;
            }
        }
        return frut;
    }

    public void setFrutas(List<Fruit> frutas) {
        this.frutas = frutas;
    }

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

    public void setCocodrilos(List<Crocodile> cocodrilos) {
        this.cocodrilos = cocodrilos;
    }

    public java.lang.Integer getEspectadores() {
        return espectadores;
    }

    public void setEspectadores(java.lang.Integer espectadores) {
        this.espectadores = espectadores;
    }

    public java.lang.Integer getNumCroc() {
        return numCroc;
    }

    public void setNumCroc(java.lang.Integer numCroc) {
        this.numCroc = numCroc;
    }

    public java.lang.Integer getNumFrut() {
        return numFrut;
    }

    public void setNumFrut(java.lang.Integer numFrut) {
        this.numFrut = numFrut;
    }
    public void addCroc(java.lang.Integer posX,java.lang.Integer posY, java.lang.String tipo, java.lang.Integer speed){
        this.numCroc +=1;
        this.cocodrilos.add(new Crocodile(numCroc,posX,posY,tipo,speed));
    }
    public void addFruit(java.lang.Integer posX,java.lang.Integer posY, java.lang.String tipo, java.lang.Integer puntos){
        this.numFrut +=1;
        this.frutas.add(new Fruit(numFrut,posX,posY,tipo,puntos));
    }
    public void eliminarCroc(java.lang.Integer numCroc){
        cocodrilos.remove(getCocodrilo(numCroc));
    }
    public void eliminarFruit(java.lang.Integer numFrut){
        frutas.remove(getFrutas(numFrut));
    }
    public java.lang.String attackCroc(){
        jugador.loseLifes();
        java.lang.String respuesta= jugador.getPosX() +";"+jugador.getPosY()+";"+jugador.getLifes();
        return respuesta;
    }
}
