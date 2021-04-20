package Vista;
import Modelo.Fruit;
import Controlador.Controlador;
import Modelo.Partida;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main {
    public static void main(String[] args) {
        Partida partida = new Partida();
        System.out.println(partida.getPosJugador());
        System.out.println(partida.attackCroc());
        /*ServerSocket servidor = null;
        Socket socket = null;
        int puerto = 54000;
        ejecutarServer(servidor,socket,puerto);
        Controlador C = new Controlador();
        Fruit fruta1 = new Fruit(1,1,C.get_random_points(),C.get_random_fruit());
        Fruit fruta2 = new Fruit();
        System.out.println(fruta1.getTipo());
        System.out.println(fruta1.getPoints());*/
    }

    public static void ejecutarServer(ServerSocket servidor, Socket socket, int puerto){

        try{
            System.out.println("Servidor en marcha");
            servidor = new ServerSocket(puerto);
            socket = servidor.accept();
            BufferedReader buffer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter salida = new PrintWriter(socket.getOutputStream(),true);
            String texto;
            while ((texto = buffer.readLine())!= null){
                System.out.println(texto);
                salida.println(texto);

            }
        }catch(IOException ex){
            ex.printStackTrace();
        }
    }
}


