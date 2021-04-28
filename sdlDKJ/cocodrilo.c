#include "SDL.h"

typedef struct
{
    int x;
    int y;
    int tipo;
    int direccion;// 1 para indirar abajo, 2 para indicar arriba
    int cargado;
    SDL_Texture *sheetTexture;

} Croco;

