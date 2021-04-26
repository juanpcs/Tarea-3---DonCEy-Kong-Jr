#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include <winsock2.h>
#include "cliente.h"
#include "cocodrilo.c"
#include "stdlib.h"


int mov=10;
Croco* gencroco(){
    int random;
    random=rand()%3;
    int xpos[]={180,375,510,565,622,750,790,980,1030};
    if(random==0){
        Croco croco;
        croco.x=xpos[rand()%9];
        croco.y=280;
        croco.tipo=rand()%3;
        return &croco;
    }
    if(random==2){
        Croco croco;
        croco.x=180;
        croco.y=280;
        croco.tipo=1;
        return &croco;
    }

}
void gravedad(Junior* mono,SOCKET s){
    if ((colitLiana(mono->x)==0) && (colitPlat(mono->x,mono->y)==0) && (mono->y<800)){
        mono->y +=mov;
        //SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "Abajo2\n";
        enviar(s,mensaje,response);
    }
};

//Funcion que compara la posicion en x y la posicion y del mono para saber si esta en contacto con una plataforma
int colitPlat(int x,int y){
    if((y<=509 && y>=494) && (x>=186 && x<=351))
        return 1;
    if((y<=322 && y>=309) && (x>=426 && x<=492))
        return 1;
    if((y<=322 && y>=309) && (x>=665 && x<=732))
        return 1;
    if((y<=501 && y>=494) && (x>=828 && x<=984))
        return 1;
    return 0;
};

//Funcion que compara la posicion en x del mono para saber si esta en contacto con una liana
int colitLiana(int x,int y){
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
    if(x>=745 && x<=810)
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
int processEvents(SDL_Window *window, Junior *mono,SOCKET s)
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
        mono->x -= mov;
        printf("izquierda.\n");
        char* response[2000];
        char mensaje[]= "izquierda1\n";
        enviar(s,mensaje,response);
    }

    //movimiento a la derecha
    if(state[SDL_SCANCODE_RIGHT]){
        mono->x += mov;
        printf("derecha.\n");
        char* response[2000];
        char mensaje[]= "derecha1\n";
        enviar(s,mensaje,response);
    }

    //movimiento hacia abajo
    if(state[SDL_SCANCODE_DOWN]){
            if(mono->y<800 && colitLiana(mono->x,mono->y)){
                mono->y += mov;
                printf("abajo.\n");
                char* response[2000];
                char mensaje[]= "Abajo1\n";
                enviar(s,mensaje,response);
            }


    }

    //Movimiento hacia arriba
    if(state[SDL_SCANCODE_UP]){
            if(mono->y>280 && colitLiana(mono->x,mono->y)){
                mono->y -= mov;
                printf("Arriba1\n");
                char* response[2000];
                char mensaje[]= "Arriba1\n";
                enviar(s,mensaje,response);
                printf("%c\n", &response);
            }
            if(mono->x>975 && colitLiana(mono->x,mono->y)){
                mono->y -= mov;
                printf("Arriba1\n");
                char* response[2000];
                char mensaje[]= "Arriba1\n";
                enviar(s,mensaje,response);
                printf("%c\n", &response);
            }

    }
    return done;
}


void jugador1(int vidas,SOCKET s){

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


    int done = 0;
    int xpos[]={180,375,510,565,622,750,790,980,1030};
    Junior mono;
    mono.x=150;
    mono.y=800;
    //Croco *crocos[3];
    //int ran=rand()%2;
    //crocos[0]->x=xpos[rand()%9];
    //crocos[0]->y=280;
    //crocos[0]->tipo=ran;
    //if (rand==0)
    //    crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //if (rand==1)
    //    crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,rcroco);


    //asignación de textura de objetos
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);

    //crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //for(int i=0;i<6;i++){
    //    if (crocos[i]->tipo==0){
    //        crocos[i]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //    }
    //    if (crocos[i]->tipo==1){
    //        crocos[i]->sheetTexture=SDL_CreateTextureFromSurface(renderer,rcroco);
    //    }
    //}
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);

    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);
    //SDL_FreeSurface(bcroco);
    //SDL_FreeSurface(rcroco);


    while (!done)
    {
        if(mono.y<185){

            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            jugador1(vidas++,s);
        }
        gravedad(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);

        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        //dibuja los cocodrilo
        //SDL_Rect rect2 = { crocos[1]->x, crocos[1]->y, 21, 40 };
        //SDL_RenderCopyEx(renderer, crocos[1]->sheetTexture, NULL, &rect2, 0, NULL, 0);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }


    char* response[2000];
    //char mensaje[]= "Finalizar1\n";
    //enviar(s,mensaje,response);
    //printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

};



/////////////
//jugador 2//
/////////////

void gravedad2(Junior* mono,SOCKET s){
    if (colitLiana(mono->x,mono->y)==0 && colitPlat(mono->x,mono->y)==0 && mono->y<800){
        mono->y +=mov;
        char* response[2000];
        char mensaje[]= "Abajo2\n";
        enviar(s,mensaje,response);
    }
};

int processEvents2(SDL_Window *window, Junior *mono,SOCKET s)
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
        mono->x -= mov;
        printf("izquierda.\n");
        //SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "izquierda2\n";
        enviar(s,mensaje,response);
    }

    //movimiento a la derecha
    if(state[SDL_SCANCODE_RIGHT]){
        mono->x += mov;
        printf("derecha.\n");
        //SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "derecha2\n";
        enviar(s,mensaje,response);
    }

    //movimiento hacia abajo
    if(state[SDL_SCANCODE_DOWN]){
            if(mono->y<800 && colitLiana(mono->x,mono->y) ){
                mono->y += mov;
                printf("abajo.\n");
                //SOCKET s = crearSocket();
                char* response[2000];
                char mensaje[]= "Abajo2\n";
                enviar(s,mensaje,response);
            }


    }

    //Movimiento hacia arriba
    if(state[SDL_SCANCODE_UP]){
            if(mono->y>280 && colitLiana(mono->x,mono->y)){
                mono->y -= mov;
                printf("Arriba2\n");
                char* response[2000];
                char mensaje[]= "Arriba2\n";
                enviar(s,mensaje,response);
                printf("%c\n", &response);
            };
            if(mono->x>975 && colitLiana(mono->x,mono->y)){
                mono->y -= mov;
                printf("Arriba2\n");
                char* response[2000];
                char mensaje[]= "Arriba2\n";
                enviar(s,mensaje,response);
                printf("%c\n", &response);
            };

    };
    return done;
};


void jugador2(int vidas,SOCKET s){

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


    int done = 0;
    int xpos[]={180,375,510,565,622,750,790,980,1030};
    Junior mono;
    mono.x=150;
    mono.y=800;
    //Croco *crocos[3];
    //int ran=rand()%2;
    //crocos[0]->x=xpos[rand()%9];
    //crocos[0]->y=280;
    //crocos[0]->tipo=ran;
    //if (rand==0)
    //    crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //if (rand==1)
    //    crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,rcroco);


    //asignación de textura de objetos
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);

    //crocos[0]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //for(int i=0;i<6;i++){
    //    if (crocos[i]->tipo==0){
    //        crocos[i]->sheetTexture=SDL_CreateTextureFromSurface(renderer,bcroco);
    //    }
    //    if (crocos[i]->tipo==1){
    //        crocos[i]->sheetTexture=SDL_CreateTextureFromSurface(renderer,rcroco);
    //    }
    //}
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);

    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);
    //SDL_FreeSurface(bcroco);
    //SDL_FreeSurface(rcroco);


    while (!done)
    {
        if(mono.y<185){

            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            jugador1(vidas++,s);
        }
        gravedad2(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents2(window,&mono,s);

        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        //dibuja los cocodrilo
        //SDL_Rect rect2 = { crocos[1]->x, crocos[1]->y, 21, 40 };
        //SDL_RenderCopyEx(renderer, crocos[1]->sheetTexture, NULL, &rect2, 0, NULL, 0);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }


    char* response[2000];
    char mensaje[]= "Finalizar2\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

};
