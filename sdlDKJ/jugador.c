#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include <winsock2.h>

#include "cocodrilo.c"
#include "stdlib.h"


int mov=10;
int vida=1;
Croco *crocs[10]={NULL};


//Función que pide la lista de cocodrilos al servidor y los agraga al array de cocodrilos.
void cargarCrocs1(SOCKET s){
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

        if(crocs[i]==NULL){
                //asignación de datos
                crocs[i]=malloc(sizeof(Croco));
                crocs[i]->y=y;
                crocs[i]->x=x;
                crocs[i]->tipo=tipo;
                crocs[i]->direccion=1;
                crocs[i]->cargado=0;
        }
        i+=1;
    };
    };

void removeCrocs(){
    for(int i=0;i<11;i++){
        free(crocs[i]);
        crocs[i]= NULL;
    }
}

//función encargada crear un efecto de gravedad en el mono y hacer que este baje si no esta en una liana o plataforma
void gravedad(Junior* mono,SOCKET s){
    if ((colitLiana(mono->x)==0) && (colitPlat(mono->x,mono->y)==0) && (mono->y<800)){
        mono->y +=mov;
        //SOCKET s = crearSocket();
        char* response[2000];
        char mensaje[]= "Abajo1\n";
        enviar(s,mensaje,response);
    }
};

void moverCrocs(Croco* croc){
    if(croc->tipo==1){//cocodrilo rojo
        if (croc->y>= 700){
            croc->direccion=2;
        }
        if (croc->y<= 280){
            croc->direccion=1;
        }
        if(croc->y<700 && croc->direccion==1)
            croc->y+=10*vida;
        if(croc->y>280 && croc->direccion==2)
            croc->y-=10*vida;
    }
    if(croc->tipo==0){//cocodrilo azul
        if(croc->y<910){
            croc->y+=10*vida;
        }
    }

}

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
//recibe la posición x y y del mono
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

//Función que detecta si el mono y algun cocodrilo se tocaron
//retorna un int, 1 si se tocaron 0 si no lo hicieron
int colidCoc(Junior* mon,Croco* croc,SOCKET s){
    if (mon->x >= croc->x-40 && mon->x <= croc->x+21){
        if(mon->y >= croc->y-40 && mon->y-50 <= croc->y){
            mon->x=150;
            mon->y=800;
            vida -=1;
            char* response[2000];
            char mensaje[]= "choque1\n";
            enviar(s,mensaje,response);
            return 1;
            }
        return 0;
    }
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

    if(state[SDL_SCANCODE_KP_1] | state[SDL_SCANCODE_1]){
        done = 1;
    }
    //movimiento a la izquierda
    if(state[SDL_SCANCODE_LEFT]){
            if(mono->x>100){
                mono->x -= mov;
                printf("izquierda");
                char* response[2000];
                char mensaje[]= "izquierda1\n";
                enviar(s,mensaje,response);
            }

    }

    //movimiento a la derecha
    if(state[SDL_SCANCODE_RIGHT]){
        if(mono->x < 1070){
            mono->x += mov;
            printf("derecha");
            char* response[2000];
            char mensaje[]= "derecha1\n";
            enviar(s,mensaje,response);
        }
    }

    //movimiento hacia abajo
    if(state[SDL_SCANCODE_DOWN]){
            if(mono->y<800 && colitLiana(mono->x,mono->y)){
                mono->y += mov;
                printf("abajo");
                char* response[2000];
                char mensaje[]= "Abajo1\n";
                enviar(s,mensaje,response);
            }


    }

    //Movimiento hacia arriba
    if(state[SDL_SCANCODE_UP]){
            if(mono->y>280 && colitLiana(mono->x,mono->y)){
                    if (mono->y<800 || mono->x<170){
                            mono->y -= mov;
                            printf("Arriba1\n");
                            char* response[2000];
                            char mensaje[]= "Arriba1\n";
                            enviar(s,mensaje,response);
                            printf("%c\n", &response);

                    }
            }
            if(mono->x>975 && colitLiana(mono->x,mono->y)){
                    mono->y -= mov;
                    printf("Arriba");
                    char* response[2000];
                    char mensaje[]= "Arriba1\n";
                    enviar(s,mensaje,response);
                    printf("%c\n", &response);
            }

    }
    return done;
}


void jugador1(SOCKET s){

    //cargarCrocs1(s);

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
    int xpos[]={180,375,510,565,622,750,790,980,1030};
    Junior mono;
    mono.x=150;
    mono.y=800;


    //asignación de textura del mono y el fondo
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);



    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);
    SDL_FreeSurface(bcroco);
    SDL_FreeSurface(rcroco);



    while (!done)
    {
        if(vida==0){
            done=1;

            }
        if(mono.y<185){

            mono.x=150;
            mono.y=800;
            vida+=1;
            char* response[2000];
            char mensaje[]= "Win1\n";
            enviar(s,mensaje,response);
            printf("%c\n", &response);
        }
        gravedad(&mono,s);
        cargarCrocs1(s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);

        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        for(int i = 0; i < 11; i++){
                if (crocs[i]!=NULL){
                    //printf("%d",crocs[i]->x);
                    moverCrocs(crocs[i]);
                    if (colidCoc(&mono,crocs[i],s)==1){
                        removeCrocs();
                        cargarCrocs1(s);
                    }
                    if(crocs[i]->tipo==1)
                        {
                        SDL_Rect cocoRect = {crocs[i]->x, crocs[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,rcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }

                    if(crocs[i]->tipo==0)
                        {
                        SDL_Rect cocoRect = {crocs[i]->x, crocs[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,bcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }
                }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    char* response[2000];
    removeCrocs();
    char mensaje[]= "Finalizar1\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
};



/////////////
//jugador 2//
/////////////

//Función que pide la lista de cocodrilos al servidor y los agraga al array de cocodrilos.
void cargarCrocs2(SOCKET s){
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

        if(crocs[i]==NULL){
                //asignación de datos
                crocs[i]=malloc(sizeof(Croco));
                crocs[i]->y=y;
                crocs[i]->x=x;
                crocs[i]->tipo=tipo;
                crocs[i]->direccion=1;
                crocs[i]->cargado=0;
        }
        i+=1;
    };
    };

int colidCoc2(Junior* mon,Croco* croc,SOCKET s){
    if (mon->x >= croc->x-40 && mon->x <= croc->x+21){
        if(mon->y >= croc->y-40 && mon->y-50 <= croc->y){
            mon->x=150;
            mon->y=800;
            vida -=1;
            char* response[2000];
            char mensaje[]= "choque2\n";
            enviar(s,mensaje,response);
            return 1;
        }
    return 0;
    }
}

//función encargada crear un efecto de gravedad en el mono y hacer que este baje si no esta en una liana o plataforma
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


    if(state[SDL_SCANCODE_KP_1] | state[SDL_SCANCODE_1]){
        done = 1;
    }
    //movimiento a la izquierda
    if(state[SDL_SCANCODE_LEFT]){
            if(mono->x>100){
                mono->x -= mov;
                printf("izquierda.\n");
                char* response[2000];
                char mensaje[]= "izquierda2\n";
                enviar(s,mensaje,response);
            }

    }

    //movimiento a la derecha
    if(state[SDL_SCANCODE_RIGHT]){
        if(mono->x < 1070){
            mono->x += mov;
            printf("derecha.\n");
            char* response[2000];
            char mensaje[]= "derecha2\n";
            enviar(s,mensaje,response);
        }
    }

    //movimiento hacia abajo
    if(state[SDL_SCANCODE_DOWN]){
            if(mono->y<800 && colitLiana(mono->x,mono->y)){
                mono->y += mov;
                printf("abajo.\n");
                char* response[2000];
                char mensaje[]= "Abajo2\n";
                enviar(s,mensaje,response);
            }


    }

    //Movimiento hacia arriba
    if(state[SDL_SCANCODE_UP]){
            if(mono->y>280 && colitLiana(mono->x,mono->y)){
                    if (mono->y<800 || mono->x<170){
                            mono->y -= mov;
                            printf("Arriba1\n");
                            char* response[2000];
                            char mensaje[]= "Arriba1\n";
                            enviar(s,mensaje,response);
                    }
            }
            if(mono->x>975 && colitLiana(mono->x,mono->y)){
                    mono->y -= mov;
                    printf("Arriba2\n");
                    char* response[2000];
                    char mensaje[]= "Arriba2\n";
                    enviar(s,mensaje,response);
                    printf("%c\n", &response);
            }

    }
    return done;
};


void jugador2(SOCKET s){


    cargarCrocs1(s);

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
    int xpos[]={180,375,510,565,622,750,790,980,1030};
    Junior mono;
    mono.x=150;
    mono.y=800;


    //asignación de textura del mono y el fondo
    mono.sheetTexture= SDL_CreateTextureFromSurface(renderer,mono_img);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, fondo);

    //free surface
    SDL_FreeSurface(fondo);
    SDL_FreeSurface(mono_img);
    SDL_FreeSurface(bcroco);
    SDL_FreeSurface(rcroco);

    while (!done)
    {
        if(vida==0){
            done=1;

            }
        if(mono.y<185){

            mono.x=150;
            mono.y=800;
            vida+=1;
            char* response[2000];
            char mensaje[]= "Win2\n";
            enviar(s,mensaje,response);
            printf("%c\n", &response);
        }
        gravedad(&mono,s);
        SDL_RenderCopy(renderer,texture,NULL,NULL);
        done=processEvents(window,&mono,s);

        //dibujar el mono
        SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        for(int i = 0; i < 11; i++){
                if (crocs[i]!=NULL){
                    //printf("%d",crocs[i]->x);
                    moverCrocs(crocs[i]);
                    if (colidCoc(&mono,crocs[i],s)==1){
                        removeCrocs();
                        cargarCrocs2(s);
                    }
                    if(crocs[i]->tipo==1)
                        {
                        SDL_Rect cocoRect = {crocs[i]->x, crocs[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,rcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }

                    if(crocs[i]->tipo==0)
                        {
                        SDL_Rect cocoRect = {crocs[i]->x, crocs[i]->y, 21, 40 };
                        SDL_RenderCopyEx(renderer,bcocoTexture , NULL, &cocoRect, 0, NULL, 0);
                        }
                }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    char* response[2000];
    removeCrocs();
    char mensaje[]= "Finalizar2\n";
    enviar(s,mensaje,response);
    printf("%c\n", &response);

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

};
