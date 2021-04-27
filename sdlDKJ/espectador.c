#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include<winsock2.h>
#include <stdio.h>

int charToInt(char *a, int largo){
    int num =0;
    int in = 1;
    for(int i=largo-1; i>=0; i--){
        num += (a[i]-'0')*in;
        in = in *10;
    }
    return num;
}
int getLargo(char *cadena){
    int i = 0;
    while(*cadena != '\0'){
        i ++;
        cadena ++;
    }
    return i;
}
void posmono(Junior *mon,SOCKET s){
    char* response[2000];
    char mensaje[]= "getJugador1\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    char *tocken = strtok(response,";");
    int x=charToInt(tocken,getLargo(tocken));
    mon->x=x;
    tocken= strtok(NULL,";");
    int y=charToInt(tocken,getLargo(tocken));
    mon->y=y;
}

int eventosEspectador1(SDL_Window *window)
{

  SDL_Event event;
  int done = 0;

  //Función que esta atenta a los eventos principamente usada para revisar si se cierra la ventana
  //o si
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

    if(state[SDL_SCANCODE_KP_1]){
        done = 1;
    }

    return done;
}

void espectador1(SOCKET s){

    //Inicio de SDL y carga de ventana
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);
    SDL_Window * window = SDL_CreateWindow("DK Junior",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 907, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    //Carga de sprites
    SDL_Surface * fondo = IMG_Load("imgs/bg.png");
    SDL_Surface * mono_img = IMG_Load("imgs/jr.png");
    SDL_Surface * bcroco = IMG_Load("imgs/bluecroco.png");
    SDL_Surface * rcroco = IMG_Load("imgs/redcroco.png");


    int done=0;
    //int xpos[]={180,375,510,565,622,750,790,980,1030};

    Junior mono;
    posmono(&mono,s);

    //Croco rcroc;
    //rcroc.direccion=1;
    //rcroc.x=565;
    //rcroc.y=280;
    //rcroc.tipo=1;

    //asignación de textura de objetos
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);
    //rcroc.sheetTexture=SDL_CreateTextureFromSurface(renderer,rcroco);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);

    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);
    SDL_FreeSurface(bcroco);
    SDL_FreeSurface(rcroco);


    while (!done)
    {
        done = eventosEspectador1(window);
        //if(vida==0){
        //    done=1;
        //    }
        //if(mono.y<185){
        //   mono.x=150;
        //    mono.y=800;
        //    vida+=1;
        //    char* response[2000];
        //    char mensaje[]= "Win1\n";
        //    enviar(s,mensaje,response);
        //    printf("%c\n", &response);
        //}
        //moverCroc(&rcroc);
        //gravedad(&mono,s);
        //colidCoc(&mono,&rcroc,s);

        //Actualiza la posción del mono
        posmono(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);

        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        //dibuja el cocodrilo
        //SDL_Rect rect2 = { rcroc.x, rcroc.y, 21, 40 };
        //SDL_RenderCopyEx(renderer, rcroc.sheetTexture, NULL, &rect2, 0, NULL, 0);


        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }

    char* response[2000];
    char mensaje[]= "DescEsp1\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
};
