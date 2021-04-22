package Controlador;

import Modelo.Partida;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import Vista.Main;

public class ServerThread extends Thread{

    String line=null;
    BufferedReader is = null;
    PrintWriter os=null;
    Socket s=null;

    public ServerThread(Socket s){
        this.s=s;
    }

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
    public java.lang.String solicitarAccion(java.lang.String mensaje){
        java.lang.String respuesta ="";
        if(mensaje.equals("choque1")){
            respuesta = Main.partidas.get(0).attackCroc();
        }
        else if(mensaje.equals("choque2")){
            respuesta = Main.partidas.get(1).attackCroc();
        }
        else if(mensaje.equals("nueva")){
            if(Main.partidas.size()==2){
                respuesta = "Demasiados jugadores";
            }else{
                Main.partidas.add(new Partida());
                respuesta = "Partida creada"; // enviar todos los datos de la partida.
            }
        }
        else if (mensaje.equals("pos1")){
            respuesta = Main.partidas.get(0).getPosJugador();
        }
        else if (mensaje.equals("pos2")){
            respuesta = Main.partidas.get(1).getPosJugador();
        }
        else if(mensaje.equals("vidas1")){
            respuesta = Main.partidas.get(0).getHearts();
        }
        else if(mensaje.equals("vidas2")){
            respuesta = Main.partidas.get(1).getHearts();
        }else if (mensaje.equals("Arriba1")){
            respuesta = Main.partidas.get(0).moverArriba();
        }else if (mensaje.equals("Arriba2")){
            respuesta = Main.partidas.get(1).moverArriba();
        }else if (mensaje.equals("Abajo1")){
            respuesta = Main.partidas.get(0).moverAbajo();
        }else if (mensaje.equals("Abajo2")){
            respuesta = Main.partidas.get(1).moverAbajo();
        }else if (mensaje.equals("derecha1")){
            respuesta = Main.partidas.get(0).moverDere();
        }else if (mensaje.equals("derecha2")){
            respuesta = Main.partidas.get(1).moverDere();
        }else if (mensaje.equals("izquierda1")){
            respuesta = Main.partidas.get(0).moverIzq();
        }else if (mensaje.equals("izquierda2")){
            respuesta = Main.partidas.get(1).moverIzq();
        }else if (mensaje.equals("espectadorP1")){
            if (Main.partidas.get(0).getEspectadores() <2){
                Main.partidas.get(0).setEspectadores();
                respuesta = "Viendo Jugador1";
            }else{
                respuesta = "Demasiados espectadores";
            }
        }else if (mensaje.equals("espectadorP2")){
            if (Main.partidas.get(1).getEspectadores() <2){
                Main.partidas.get(1).setEspectadores();
                respuesta = "Viendo Jugador2";
            }else{
                respuesta = "Demasiados espectadores";
            }
        }else if(mensaje.equals("DescEsp1")){
            Main.partidas.get(0).desconEspec();
            respuesta = "espectador desconectado";
        }else if(mensaje.equals("DescEsp2")){
            Main.partidas.get(1).desconEspec();
            respuesta = "espectador desconectado";
        }else if(mensaje.equals("getJugador1")){
            respuesta = Main.partidas.get(0).getJugador();
        }else if(mensaje.equals("getJugador2")){
            respuesta = Main.partidas.get(1).getJugador();
        }else if(mensaje.equals("getCocodrilos1")){
            respuesta = Main.partidas.get(0).getCocodrilos();
        }else if(mensaje.equals("getCocodrilos2")){
            respuesta = Main.partidas.get(1).getCocodrilos();
        }else if (mensaje.equals("getFrutas1")){
            respuesta = Main.partidas.get(0).getFrutas();
        }else if (mensaje.equals("getFrutas2")){
            respuesta = Main.partidas.get(1).getFrutas();
        }
        return respuesta;
    }
}
