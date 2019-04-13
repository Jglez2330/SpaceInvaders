//Se importan las bibliotecas necesarias para el programa

//Macros del programa
#include <SDL.h>
#include "nave.h"
#include "InvaderHandler.h"
#include "misil.h"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define XSIZE  800 //Macro del tamaño de la pantalla en X
#define YSIZE  600 //Macro del tamaño de la pantalla en Y
#define NAVEY  540 //Macro de la posición inicial de la nave en Y
#define NAVEVEL 20 //Macro de la velocidad de la nave
#define MS 10 // Macro de los milisegundos


int PORT = 5555;
char buffer[4096];
char* IP = "192.168.1.130";
int main( int argc, char* args[] )
{

    /*int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        exit(0);
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(IP);
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        exit(0);
    }
*/
    //Se inicializa la biblioteca SDL, en caso de fallar se muestra un mensaje de error
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error al inicializar SDL",SDL_GetError(),NULL);
        SDL_Quit();
        return -1;
    }
    //Se declaran algunas variables importantes
    int gameOver = 0; // Entero que mantiene el ciclo principal del juego
    int typeEvent; //Entero que almacena el tipo de evento que se presenta en la pantalla
    const unsigned char *keys = SDL_GetKeyboardState(NULL); //Arreglo de las teclas
    SDL_Window *window; //Puntero que almacena ventana creada
    SDL_Renderer *renderer; // Puntero que almacena el renderer creado
    SDL_Event event; // Variable que almacena el evento generado en la panatalla
    Nave nave = {XSIZE/2,NAVEY,XSIZE/2-20,NAVEY+20,XSIZE/2+20,NAVEY+20,NAVEVEL,5,0,NULL}; // Se crea la estructura de la nave del usuario

    InvaderHandler* handler = createHandler();

    window = SDL_CreateWindow("Space Invaders",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,
    SDL_WINDOW_SHOWN); // Se crea la ventana principal del juego

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Renderer del juego




    unsigned short iterations = 0;


    //Ciclo principal del juego
    while (!gameOver){

        // Se obtienen los eventos generados
        if(SDL_PollEvent(&event)){

            typeEvent = event.type;

            if(typeEvent == SDL_QUIT){ // Se cierra la ventana principal del juego
                gameOver = 1;
            }
            else if(typeEvent == SDL_KEYDOWN){ // Se presiona una tecla

                if(keys[SDL_SCANCODE_LEFT]){
                    NaveAvanzaIzq(&nave);

                }
                else if(keys[SDL_SCANCODE_RIGHT]){
                    NaveAvanzaDer(&nave);
                }
                else if(keys[SDL_SCANCODE_SPACE]){
                    NaveDispara(&nave);
                }
            }
        }

        if(handler->invaderList == NULL||iterations == 1200){
            newEnemies(handler);
            iterations = 0;
            nave.vida+=1;
        }else if(handler->invaderList->data->y1 >= 560){
            gameOver = 1;
        }else{
            EliminarMisiles(&nave,handler);
            gameOver = EliminarMisilesInvaders(&nave,handler);
        }
        if(iterations % 160 == 0){
            DispararInvaders(handler);
        }else if(iterations % 35 == 0){
            MoverInvaders(handler);
        }



        //Se libera la memoria de los misiles que salen de la pantalla



        //Se dibuja en la pantalla

        cJSON* b = LtoJ(&handler->invaderList);

        cJSON_AddItemToObject(b,"opcode",cJSON_CreateNumber(0));
        char * a = cJSON_Print(b);

//        send(sockfd,a,strlen(a),0);


        //read(sockfd,buffer,4096);

        free(a);
        cJSON_Delete(b);

        SDL_SetRenderDrawColor(renderer,0,0,0,0);// RGB del color negro
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,0);//RGB del color blanco
        DibujarNave_Misiles(&nave,renderer); //Se dibuja la nave del usuario y los misiles que dispara


        if(handler->invaderList != NULL){
            DibujarInvaders(handler,renderer);
        }


        SDL_RenderPresent(renderer);
        SDL_Delay(MS); // Tiempo de espera en milisegundos

        iterations++;




    }

    //Se libera la memoria dinámica del programa
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}