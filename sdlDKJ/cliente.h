/*
	Create a TCP socket
*/

#include<stdio.h>
#include<winsock2.h>


SOCKET crearSocket();

void enviar(SOCKET s, char *message,char *response);
