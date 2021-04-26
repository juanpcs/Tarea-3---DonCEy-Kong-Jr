#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include <winsock2.h>
#include "cliente.h"

void gravedad(Junior* mono){
    if (colitLiana(mono->x)==0 && colitPlat(mono->x,mono->y)==0 && mono->y<800){
        mono->y +=5;
    }
};

//Funcion que compara la posicion en x y la posicion y del mono para saber si esta en contacto con una plataforma
int colitPlat(int x,int y){
    if((y<=502 && y>=498) && (x>=186 && x<=351))
        return 1;
    if((y<=316 && y>=314) && (x>=426 && x<=492))
        return 1;
    if((y<=316 && y>=314) && (x>=665 && x<=732))
        return 1;
    if((y<=497 && y>=494) && (x>=828 && x<=984))
        return 1;
    return 0;
};

//Funcion que compara la posicion en x del mono para saber si esta en contacto con una liana
int colitLiana(int x){
    if(x>=140 && x<=170)
        {
            return 1;
        }
    if(x>=375 && x<=415)
        {
            return 1;
        }
    if(x>=500 && x<=575)
        {
            return 1;
        }
    if(x>=618 && x<=645)
        {
            return 1;
        }
    if(x>=745 && x<=798)
        {
            return 1;
        }
    if(x>=975 && x<=1050)
       {
            return 1;
        }

    return 0;
}


//Función que esta atenta a los eventos principamente usada para revisar si se cierra la ventana
//o si se presiona una tecla del teclado
int processEvents(SDL_Window *window, Junior *mono)
{

  SDL_Event event;
  int done = 0;


  while(SDL_PollEvent(&event))
  {
      switch(event.type)
      {
          case SDL_WINDOWEVENT_CLOSE:
              {
              if(window)
                {
                  SDL_DestroyWindow(window);
                  window = NULL;
                  done = 1;
                }
              }
        break;
          case SDL_KEYDOWN:
              {
                switch(event.key.keysym.sym)
                {
                  case SDLK_ESCAPE:
                    done = 1;
                  break;
                }
              }
        break;
        case SDL_QUIT:
            {
                //quit out of the game
                done = 1;
                break;
            }
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);


    //movimiento a la izquierda
    if(state[SDL_SCANCODE_LEFT]){
        mono->x -= 3;
        printf("izquierda.\n");
        SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "Abajo1\n";
        enviar(s,mensaje,response);
    }

    //movimiento a la derecha
    if(state[SDL_SCANCODE_RIGHT]){
        mono->x += 3;
        printf("derecha.\n");
        SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "derecha1\n";
        enviar(s,mensaje,response);
    }

    //movimiento hacia abajo
    if(state[SDL_SCANCODE_DOWN]){
            if(mono->y<800  ){
                mono->y += 3;
                printf("abajo.\n");
                SOCKET s = crearSocket();
                char* response[2000];
                char mensaje[]= "Abajo1\n";
                enviar(s,mensaje,response);
                printf("%d",mono->x);
                printf("%d",mono->y);

            }


    }

    //Movimiento hacia arriba
    if(state[SDL_SCANCODE_UP]){
            if(mono->y>280 && colitLiana(mono->x)){
                mono->y -= 3;
                printf("Arriba1\n");
                SOCKET s = crearSocket();
                char* response[2000];
                char mensaje[]= "Arriba1\n";
                enviar(s,mensaje,response);
                printf("%d\n", &response);
            }
            if(mono->x>975 && colitLiana(mono->x)){
                mono->y -= 3;
                printf("Arriba1\n");
                SOCKET s = crearSocket();
                char* response[2000];
                char mensaje[]= "Arriba1\n";
                enviar(s,mensaje,response);
                printf("%d\n", &response);
            }

    }
    return done;
}

int globalTime = 0;
void jugador1(int vidas){
    int done = 0;
    Junior mono;
    mono.x=150;
    mono.y=800;



    //Inicio de SDL y carga de ventana
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    SDL_Window * window = SDL_CreateWindow("DK Junior",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 907, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    //Carga de sprites
    SDL_Surface * fondo = IMG_Load("imgs/bg.png");
    SDL_Surface * mono_img = IMG_Load("imgs/jr.png");


    //asignación de textura de objetos
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);

    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);


    while (!done)
    {
        if(mono.y<185){

            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            jugador1(vidas++);
            SDL_Quit();
        }
        gravedad(&mono);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono);
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

};
