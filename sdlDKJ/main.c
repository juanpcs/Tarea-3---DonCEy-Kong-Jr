#include "SDL.h"
#include "SDL_image.h"
#include <stdbool.h>
#include "jugador.h"



SOCKET crearSocket(){
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");


	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 54000 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	return s;
}
/*
Nombre: enviar
Descrpción: función que envia un mensaje al servidor
In: socket cliente, puntero con el mensaje a enviar, puntero a la respuesta
out: void
*/
void enviar(SOCKET s, char *message,char *response){
	//char server_reply[2000];
	int recv_size;
	if( send(s , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
	}
	puts("Data Send\n");

	//Receive a reply from the server
	if((recv_size = recv(s , response , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}

	puts("Reply received\n");

	//Add a NULL terminating character to make it a proper string before printing
	response[recv_size] = '\0';
}

int eventosCrear(SDL_Window *window,SOCKET s)
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


    //envia al servidor la petición de crear cocodrilos al jugador1
    if(state[SDL_SCANCODE_KP_1] | state[SDL_SCANCODE_1]){
        char response[2000];
        char mensaje[]= "cocodrilo1,5,6,rojo,2\n";
        enviar(s,mensaje,response);
    }

    //envia al servidor la petición de crear cocodrilos al jugador 2
    if(state[SDL_SCANCODE_KP_2]|state[SDL_SCANCODE_2]){
        char response[2000];
        char mensaje[]= "cocodrilo2,5,6,rojo,2\n";
        enviar(s,mensaje,response);

    }
    return done;
}
/*
Eventos menu
Descripcion: Función que maneja los eventos de la pantalla del menu
In: ventana en ejecución
out: int con estatus del resultado
*/
int eventosMenu(SDL_Window *window)
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
    //Inciar una jugador
    if(state[SDL_SCANCODE_KP_1] | state[SDL_SCANCODE_1]){
        done = 6;
    }
    //Iniciar Jugador 2
    if(state[SDL_SCANCODE_KP_2]|state[SDL_SCANCODE_2]){
        done =2;
    }
    //Iniciar espectador a jugador 1
    if(state[SDL_SCANCODE_KP_3]|state[SDL_SCANCODE_4]){
        done = 4;
    }
    //Inciar espectador a jugador 2
    if(state[SDL_SCANCODE_KP_4]|state[SDL_SCANCODE_5]){
        done =5;
    }
    //iniciar pantalla de creacion de cocodrilos
    if(state[SDL_SCANCODE_KP_0]|state[SDL_SCANCODE_0]){
        done =7;
    }
    return done;
}
void crearCocodrilos(SOCKET s){
    char response[2000];
	// así se debe crear el mensaje que se desea enviar, no olvidar la vuelta de carro
	int done =0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *crear= SDL_CreateWindow("Menu",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,500,500,0);
    SDL_Renderer *renderer = SDL_CreateRenderer(crear, -1,0);
    SDL_Surface *fondo = IMG_Load("imgs/crear.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,fondo);
    SDL_RenderCopy(renderer, texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    while(done == 0){
        done = eventosCrear(crear,s);
        SDL_Delay(100);

    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(fondo);
    SDL_DestroyWindow(crear);
}
void crearMenu(SOCKET s){
    int done =0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window= SDL_CreateWindow("Menu",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,500,500,0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,0);
    SDL_Surface *fondo = IMG_Load("imgs/5.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,fondo);
    SDL_RenderCopy(renderer, texture,NULL,NULL);
    SDL_RenderPresent(renderer);
    int reiniciar=0;
    while(done == 0){
        done = eventosMenu(window);
        SDL_Delay(10);

    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(fondo);
    SDL_DestroyWindow(window);
    char response[2000];
    char comp[]="Partida12";
    if(done == 6){
        //crear ventana para jugador 1
        char mensaje[]= "nueva\n";
        enviar(s,mensaje,response);
        //puts(comp[1]);
        //puts(response[1]);
        if(comp[0]==response[0] && comp[7]==response[7])
        {
               reiniciar=1;
               jugador1(s);
        }


        if(comp[0]==response[0] && comp[8]==response[7])
        {
            reiniciar=1;
            jugador2(s);
        }
        if (reiniciar!=1)
            {
                puts("Maximo de jugadores alcanzado");
                crearMenu(s);
            }

        }else if(done == 2){
        // crear ventana para jugador2
        char mensaje[]= "nueva\n";
        if(comp[0]==response[0] && comp[7]==response[7])
        {
               reiniciar=1;
               jugador1(s);
        }


        if(comp[0]==response[0] && comp[8]==response[7])
        {
            reiniciar=0;
            jugador2(s);
        }
        if (reiniciar!=1)
            {
                puts("Maximo de jugadores alcanzado");
                crearMenu(s);
            }
    }else if(done == 4){
        //crear ventana para espectador del jugador 1
        char mensaje[]= "espectadorP1\n";
        enviar(s,mensaje,response);
        espectador1(s);
    }else if(done == 5 ){
        //crear ventana para especatador del jugador 2
        char mensaje2[]= "espectadorP2\n";
        enviar(s,mensaje2,response);

    }else if (done == 7){
        crearCocodrilos(s);

    }

}


int main(int argc, char ** argv)
{
    SOCKET s = crearSocket();
    crearMenu(s);
}


