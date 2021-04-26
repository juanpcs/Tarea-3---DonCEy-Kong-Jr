#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include "cliente.h"
#include<winsock2.h>


void gravedad(int x,int y);
int colitPlat(int x,int y);
int colitLiana(int x);
const SOCKET s ;
char* response[2000];
int processEvents(SDL_Window *window, Junior *mono);
void jugador1();
