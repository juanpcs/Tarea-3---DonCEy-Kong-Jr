/*
	Create a TCP socket
*/

#include<stdio.h>
#include<winsock2.h>
#include "cliente.h"

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

/*
Nombre: crearSocket
autor: Microsoft
Adaptación: Sebastian Moya
Descripción: función que crea un socket cliente
out: socket cliente
*/
SOCKET crearSocket(){
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");


	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 54000 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	return s;
}
/*
Nombre: enviar
Descrpción: función que envia un mensaje al servidor
In: socket cliente, puntero con el mensaje a enviar, puntero a la respuesta
out: void
*/
void enviar(SOCKET s, char *message,char *response){
	//char server_reply[2000];
	int recv_size;
	if( send(s , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
	}
	puts("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , response , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	response[recv_size] = '\0';
}

//int main(int argc , char *argv[])
//{
//	//Asi se crea el socket cliente
//	SOCKET s = crearSocket();
//	// se debe crear este buff para guardar la respuesta del servidor
//	char response[2000];
//	// así se debe crear el mensaje que se desea enviar, no olvidar la vuelta de carro
//	char mensaje[]= "nueva\n";
//	char mensaje2[]="getFrutas1\n";
//	//así se hace la consulta al servidor
//	enviar(s,mensaje,response);
//	//imprime la respuesta del servidor
//	printf("%s\n", &response);
//	enviar(s,mensaje2,response);
//	printf("%s\n", &response);
//
//	return 0;
//}
