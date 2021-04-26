#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "cliente.h"
#include "jugador.h"




int main(int argc, char ** argv)
{
    int respuesta;
    printf("Introduzca un numero entero: ");
    printf("Ingrese 1 para jugador 1\n");
    printf("Ingrese 2 para jugador 2 \n");
    printf("Ingrese 3 para expectar al jugador 1 \n");
    printf("Ingrese 4 para expectar al jugador 2 \n");
    scanf("%d", &respuesta);
    if(respuesta==1){
            jugador1(1);
    }
    return 0;
}


