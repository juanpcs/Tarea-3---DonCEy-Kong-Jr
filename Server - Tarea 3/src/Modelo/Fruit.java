package Modelo;

/**
 * Clase encargada de la creacón de frutas
 * @author Juan Pablo C
 */
public class Fruit extends Objeto {
    /**
     * Constructor de la clase
     * @param num numero de fruta
     * @param posX posicion en x
     * @param posY posicion en y
     * @param tipo tipo de fruta
     * @param esp puntaje de fruta
     */
    public Fruit(java.lang.Integer num, java.lang.Integer posX,java.lang.Integer posY,java.lang.String tipo,java.lang.Integer esp) {
        super(num,posX,posY,tipo, esp);
    }
}



