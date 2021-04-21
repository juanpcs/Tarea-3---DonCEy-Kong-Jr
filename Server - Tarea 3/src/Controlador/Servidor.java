package Controlador;

import Modelo.Partida;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Servidor {
    Socket socket;
    ServerSocket serverSocket;
    List<Partida> partidas;

    public Servidor() {
        this.socket = null;
        this.serverSocket = null;
        this.partidas = new ArrayList<>();
    }
    public void iniciar(){
        System.out.println("Server Listening......");
        try{
            serverSocket = new ServerSocket(54000); // can also use static final PORT_NUM , when defined

        }
        catch(IOException e){
            e.printStackTrace();
            System.out.println("Server error");

        }

        while(true){
            try{
                socket= serverSocket.accept();
                System.out.println("connection Established");
                ServerThread st=new ServerThread(socket);
                st.start();

            }

            catch(Exception e){
                e.printStackTrace();
                System.out.println("Connection Error");

            }
        }
    }
}
