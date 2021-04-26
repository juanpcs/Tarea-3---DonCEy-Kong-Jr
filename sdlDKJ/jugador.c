#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "mono.c"

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

    if(state[SDL_SCANCODE_LEFT]){
        mono->x -= 3;
        printf("izquierda.\n");
    }
    if(state[SDL_SCANCODE_RIGHT]){
        mono->x += 3;
        printf("derecha.\n");
    }
    if(state[SDL_SCANCODE_DOWN]){
        mono->y += 3;
        printf("abajo.\n");
    }

    if(state[SDL_SCANCODE_UP]){
        mono->y -= 3;
        printf("arriba\n");
    }
    return done;
}

int globalTime = 0;
void jugador1(){
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
        done=processEvents(window,&mono);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
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
