#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include<winsock2.h>
#include <stdio.h>
#include "cocodrilo.c"

int life=0;
Croco *crocos[10]={NULL};

void lifes(SOCKET s){
    char* response[2000];
    char mensaje[]= "getVidas1\n";
    enviar(s,mensaje,response);
    char *tocken = strtok(response,";");
    int vida=charToInt(tocken,getLargo(tocken));
    life=vida;
}
void lifes2(SOCKET s){
    char* response[2000];
    char mensaje[]= "getVidas2\n";
    enviar(s,mensaje,response);
    char *tocken = strtok(response,";");
    int vida=charToInt(tocken,getLargo(tocken));
    life=vida;
}
void cargarCroc1(SOCKET s){
    char* response[2000];
    char mensaje[]= "getCocodrilos1\n";
    enviar(s,mensaje,response);
    int i=0;
    char *tocken= strtok(response,";");
    int largo=charToInt(tocken,getLargo(tocken));
    tocken= strtok(NULL,";");
    while(i<largo){
        //obtención de datos
        int x=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");
        int y=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");
        int tipo=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");

        if(crocos[i]==NULL){
                //asignación de datos
                crocos[i]=malloc(sizeof(Croco));
                crocos[i]->y=y;
                crocos[i]->x=x;
                crocos[i]->tipo=tipo;
                crocos[i]->direccion=1;
                crocos[i]->cargado=0;
        }
        i+=1;
    };
    };

void cargarCroc2(SOCKET s){
    char* response[2000];
    char mensaje[]= "getCocodrilos2\n";
    enviar(s,mensaje,response);
    int i=0;
    char *tocken= strtok(response,";");
    int largo=charToInt(tocken,getLargo(tocken));
    tocken= strtok(NULL,";");
    while(i<largo){
        //obtención de datos
        int x=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");
        int y=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");
        int tipo=charToInt(tocken,getLargo(tocken));
        tocken= strtok(NULL,";");

        if(crocos[i]==NULL){
                //asignación de datos
                crocos[i]=malloc(sizeof(Croco));
                crocos[i]->y=y;
                crocos[i]->x=x;
                crocos[i]->tipo=tipo;
                crocos[i]->direccion=1;
                crocos[i]->cargado=0;
        }
        i+=1;
    };
    };

void removeCroc(){
    for(int i=0;i<11;i++){
        free(crocos[i]);
        crocos[i]= NULL;
    }
}

void moverCroc(Croco* croc){
    if(croc->tipo==1){//cocodrilo rojo
        if (croc->y>= 700){
            croc->direccion=2;
        }
        if (croc->y<= 280){
            croc->direccion=1;
        }
        if(croc->y<700 && croc->direccion==1)
            croc->y+=10*life;
        if(croc->y>280 && croc->direccion==2)
            croc->y-=10*life;
    }
    if(croc->tipo==0){//cocodrilo azul
        if(croc->y<910){
            croc->y+=10*life;
        }
    }

}
void posmono(Junior *mon,SOCKET s){
    char* response[2000];
    char mensaje[]= "getJugador1\n";
    enviar(s,mensaje,response);


    char *tocken = strtok(response,";");
    int x=charToInt(tocken,getLargo(tocken));
    mon->x=x;
    tocken= strtok(NULL,";");
    int y=charToInt(tocken,getLargo(tocken));
    mon->y=y;
}
void posmono2(Junior *mon,SOCKET s){
    char* response[2000];
    char mensaje[]= "getJugador2\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    char *tocken = strtok(response,";");
    int x=charToInt(tocken,getLargo(tocken));
    mon->x=x;
    tocken= strtok(NULL,";");
    int y=charToInt(tocken,getLargo(tocken));
    mon->y=y;
}
int eventosEspectador(SDL_Window *window)
{

  SDL_Event event;
  int done = 0;

  //Funci�n que esta atenta a los eventos principamente usada para revisar si se cierra la ventana
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

    //carga de texturas
    SDL_Texture *bcocoTexture;
    SDL_Texture *rcocoTexture;
    bcocoTexture = SDL_CreateTextureFromSurface(renderer, bcroco);
    rcocoTexture = SDL_CreateTextureFromSurface(renderer, rcroco);

    int done=0;
    Junior mono;
    posmono(&mono,s);


    //asignaci�n de textura de objetos
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
        done = eventosEspectador(window);
        posmono(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);
        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);
        lifes(s);
        if(life==0){
            done=1;
            continue;
        }
        cargarCroc1(s);
        printf("cargados pete");
        for(int i = 0; i < 11; i++){
                if (crocos[i]!=NULL){
                    //printf("%d",crocs[i]->x);
                    moverCrocs(crocos[i]);
                    if (colidCoc(&mono,crocos[i],s)==1){
                        removeCroc();
                        cargarCroc1(s);
                    }
                    if(crocos[i]->tipo==1)
                        {
                        SDL_Rect cocoRect = {crocos[i]->x, crocos[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,rcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }

                    if(crocos[i]->tipo==0)
                        {
                        SDL_Rect cocoRect = {crocos[i]->x, crocos[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,bcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }
                }
            }

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

void espectador2(SOCKET s){

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

    //carga de texturas
    SDL_Texture *bcocoTexture;
    SDL_Texture *rcocoTexture;
    bcocoTexture = SDL_CreateTextureFromSurface(renderer, bcroco);
    rcocoTexture = SDL_CreateTextureFromSurface(renderer, rcroco);

    int done=0;
    Junior mono;
    posmono(&mono,s);


    //asignaci�n de textura de objetos
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
        done = eventosEspectador(window);
        posmono2(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);
        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        lifes(s);
        if(life==0){
            done=1;
            continue;
        }
        cargarCroc2(s);
        printf("cargados pete");
        for(int i = 0; i < 11; i++){
                if (crocos[i]!=NULL){
                    //printf("%d",crocs[i]->x);
                    moverCrocs(crocos[i]);
                    if (colidCoc(&mono,crocos[i],s)==1){
                        removeCroc();
                        cargarCroc2(s);
                    }
                    if(crocos[i]->tipo==1)
                        {
                        SDL_Rect cocoRect = {crocos[i]->x, crocos[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,rcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }

                    if(crocos[i]->tipo==0)
                        {
                        SDL_Rect cocoRect = {crocos[i]->x, crocos[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,bcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }
                }
            }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }

    char* response[2000];
    char mensaje[]= "DescEsp2\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
};
