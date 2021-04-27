package Controlador;

import Modelo.Partida;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import Vista.Main;

import static Vista.Main.part;

/**
 * Clase encargada de manejar el hilo de cada cliente
 * @author Sebastian Moya Monge
 */
public class ServerThread extends Thread{

    String line=null;
    BufferedReader is = null;
    PrintWriter os=null;
    Socket s=null;

    /**
     * Constructor de la clase
     * @param s socket cliente
     */
    public ServerThread(Socket s){
        this.s=s;
    }

    /**
     * Método encargado de poner en ejecucion el socket
     */
    public void run() {
        try{
            is= new BufferedReader(new InputStreamReader(s.getInputStream()));
            os=new PrintWriter(s.getOutputStream());

        }catch(IOException e){
            System.out.println("IO error in server thread");
        }

        try {
            line=is.readLine();
            java.lang.String respuesta ="";
            while(line.compareTo("QUIT")!=0){
                respuesta = solicitarAccion(line);
                os.println(respuesta);
                os.flush();
                System.out.println("Response to Client  :  "+respuesta);
                line=is.readLine();
            }
        } catch (IOException e) {

            line=this.getName(); //reused String line for getting thread name
            System.out.println("IO Error/ Client "+line+" terminated abruptly");
        }
        catch(NullPointerException e){
            line=this.getName(); //reused String line for getting thread name
            System.out.println("Client "+line+" Closed");
        }

        finally{
            try{
                System.out.println("Connection Closing..");
                if (is!=null){
                    is.close();
                    System.out.println(" Socket Input Stream Closed");
                }

                if(os!=null){
                    os.close();
                    System.out.println("Socket Out Closed");
                }
                if (s!=null){
                    s.close();
                    System.out.println("Socket Closed");
                }

            }
            catch(IOException ie){
                System.out.println("Socket Close Error");
            }
        }//end finally
    }

    /**
     * Método que valida el mensaje enviado por el cliente y devuelve la respuesta correspondiente
     * @param mensaje string que se envió desde el cliente
     * @return respuesta del servidor
     */
    public java.lang.String solicitarAccion(java.lang.String mensaje) {
        java.lang.String respuesta = "";
        if (mensaje.equals("choque1")) {
            respuesta = part[0].attackCroc();
            if(respuesta.equals("GameOver")){
                part[0]=null;
                respuesta = "close";
            }
        } else if (mensaje.equals("choque2")) {
            respuesta = part[1].attackCroc();
            if(respuesta.equals("GameOver")){
                part[1]=null;
                respuesta = "close";
            }
        } else if (mensaje.equals("nueva")) {
            if(part[0] == null){
                part[0]= new Partida();
                respuesta= "Partida1";
            }else if(part[1]== null){
                part[1]= new Partida();
                respuesta ="partida2";
            }else{
                respuesta = "Demasiados jugadores";
            }
        } else if (mensaje.equals("pos1")) {
            respuesta = part[0].getPosJugador();
        } else if (mensaje.equals("pos2")) {
            respuesta = part[1].getPosJugador();
        } else if (mensaje.equals("vidas1")) {
            respuesta = part[0].getHearts();
        } else if (mensaje.equals("vidas2")) {
            respuesta = part[1].getHearts();
        } else if (mensaje.equals("Arriba1")) {
            respuesta = part[0].moverArriba();
        } else if (mensaje.equals("Arriba2")) {
            respuesta = part[1].moverArriba();
        } else if (mensaje.equals("Abajo1")) {
            respuesta = part[0].moverAbajo();
        } else if (mensaje.equals("Abajo2")) {
            respuesta = part[1].moverAbajo();
        } else if (mensaje.equals("derecha1")) {
            respuesta = part[0].moverDere();
        } else if (mensaje.equals("derecha2")) {
            respuesta = part[1].moverDere();
        } else if (mensaje.equals("izquierda1")) {
            respuesta = part[0].moverIzq();
        } else if (mensaje.equals("izquierda2")) {
            respuesta = part[1].moverIzq();
        } else if (mensaje.equals("espectadorP1")) {
            if (part[0].getEspectadores() < 2) {
                part[0].setEspectadores();
                respuesta = "Viendo Jugador1";
            } else {
                respuesta = "Demasiados espectadores";
            }
        } else if (mensaje.equals("espectadorP2")) {
            if (part[1].getEspectadores() < 2) {
                part[1].setEspectadores();
                respuesta = "Viendo Jugador2";
            } else {
                respuesta = "Demasiados espectadores";
            }
        } else if (mensaje.equals("DescEsp1")) {
            part[0].desconEspec();
            respuesta = "espectador desconectado";
        } else if (mensaje.equals("DescEsp2")) {
            part[1].desconEspec();
            respuesta = "espectador desconectado";
        } else if (mensaje.equals("getJugador1")) {
            respuesta = part[0].getJugador();
        } else if (mensaje.equals("getJugador2")) {
            respuesta = part[1].getJugador();
        } else if (mensaje.equals("getCocodrilos1")) {
            respuesta = part[0].getCocodrilos();
        } else if (mensaje.equals("getCocodrilos2")) {
            respuesta = part[1].getCocodrilos();
        } else if (mensaje.equals("getFrutas1")) {
            respuesta = part[0].getFrutas();
        } else if (mensaje.equals("getFrutas2")) {
            respuesta = part[1].getFrutas();
        }else if (mensaje.equals("Win1")){
            part[0].win();
            respuesta = "Ha ganado";
        }else if (mensaje.equals("Win2")){
            part[1].win();
            respuesta = "Ha ganado";
        }else if(mensaje.equals("Finalizar1")){
            part[0]=null;
            respuesta = "close";
            System.out.println("Partida 1 finalizada");
        }else if(mensaje.equals("Finalizar2")){
            part[1]=null;
            respuesta = "close";
            System.out.println("Partida 2 finalizada");
        }else if(mensaje.equals("Vidas_Puntos1")){
            respuesta = part[0].getVidPunt();
        }
        else{
            respuesta = analizPiezas(mensaje);
        }
        return respuesta;
    }

    /**
     * Metodo que analiza el mensaje cuando ese posee multiples parametros
     * @param mensaje string separado por comas
     * @return respuesta del servidor
     */
    private java.lang.String analizPiezas(java.lang.String mensaje){
        String respuesta = "";
        java.lang.String[] palabras = mensaje.split(",");
        if (palabras[0].equals("cocodrilo1")){
            part[0].crearCocodrilo(Integer.parseInt(palabras[1]),Integer.parseInt(palabras[2]),Integer.parseInt(palabras[3]),Integer.parseInt(palabras[4]));
            respuesta = "Cocodrilo creado en partida1";
        }else if(palabras[0].equals("cocodrilo2")) {
            part[1].crearCocodrilo(Integer.parseInt(palabras[1]), Integer.parseInt(palabras[2]), Integer.parseInt(palabras[3]), Integer.parseInt(palabras[4]));
            respuesta = "Cocodrilo creado en partida2";
        }else if(palabras[0].equals("EleCoco1")){
            part[0].eliminarCroc(Integer.parseInt(palabras[1]));
        }else if(palabras[0].equals("EleCoco2")){
           part[1].eliminarCroc(Integer.parseInt(palabras[1]));
        }else if(palabras[0].equals("EleFrut1")){
            part[0].eliminarFruit(Integer.parseInt(palabras[1]));
        }else if(palabras[0].equals("EleFrut2")){
            part[1].eliminarFruit(Integer.parseInt(palabras[1]));
        }
        return respuesta;
    }
}
