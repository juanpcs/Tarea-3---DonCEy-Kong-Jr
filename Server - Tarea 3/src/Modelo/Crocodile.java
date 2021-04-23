package Modelo;

/**
 * Clase enccargada que guarda los datos de cada cocodrilo
 * @author Juan Pablo C
 */
public class Crocodile extends Objeto{
    /**
     * Constructor de la clase
     * @param num numero de cocodrilo
     * @param posX posicion en x del cocodrilo
     * @param posY posicion en y del cocodrilo
     * @param tipo tipo de cocodrilo (rojo o azul)
     * @param esp atributo especial que indica la velocidad del cocodrilo
     */
    public Crocodile(java.lang.Integer num, java.lang.Integer posX,java.lang.Integer posY,java.lang.String tipo,java.lang.Integer esp) {
        super(num,posX,posY,tipo, esp);
    }
}
