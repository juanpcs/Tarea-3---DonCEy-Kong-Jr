#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"
#include<winsock2.h>


void espectador1(int vidas,SOCKET s){

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
        //SDL_RenderCopy(renderer,texture,NULL,NULL);
        //done=processEvents(window,&mono,s);

        //dibujar el mono
        //SDL_Rect rect = { mono.x, mono.y, 40, 50 };
        //SDL_RenderCopyEx(renderer, mono.sheetTexture, NULL, &rect, 0, NULL, 0);

        //dibuja el cocodrilo
        //SDL_Rect rect2 = { rcroc.x, rcroc.y, 21, 40 };
        //SDL_RenderCopyEx(renderer, rcroc.sheetTexture, NULL, &rect2, 0, NULL, 0);


        SDL_RenderPresent(renderer);
        SDL_Delay(50000);
        done=1;
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
