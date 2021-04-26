#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "cliente.h"

#include "jugador.h"




int main(int argc, char ** argv)
{
    SOCKET s = crearSocket();
    char* response[2000];


    int respuesta;
    printf("Introduzca un numero entero: ");
    printf("Ingrese 1 para jugador 1\n");
    printf("Ingrese 2 para jugador 2 \n");
    printf("Ingrese 3 para expectar al jugador 1 \n");
    printf("Ingrese 4 para expectar al jugador 2 \n");
    scanf("%d", &respuesta);
    if(respuesta==1){
            char mensaje[]= "Partida1";
            enviar(s,mensaje,response);
            printf("sali");
            printf(response);
            jugador1();
    }


    return 0;
}


