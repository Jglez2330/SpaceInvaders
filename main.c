//Se importan las bibliotecas necesarias para el programa
#include "nave.h"
#include <SDL2/SDL_image.h>

#include "bunker.h"
#include "InvaderHandler.h"

//Macros del programa
#define XSIZE  1000 //Macro del tamaño de la pantalla en X
#define YSIZE  650 //Macro del tamaño de la pantalla en Y
#define NAVEY  550 //Macro de la posición inicial de la nave en Y
#define NAVEVEL 20 //Macro de la velocidad de la nave
#define MS 10 // Macro de los milisegundos

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

int main( int argc, char* args[] )
{
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
    Nave nave = {450,NAVEY,NAVEVEL,NULL}; // Se crea la estructura de la nave del usuario
    Bunker *bunkerPantalla = crearBunkers();//Se crean los escudos o bunkers
    window = SDL_CreateWindow("Space Invaders",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,
                              SDL_WINDOW_SHOWN); // Se crea la ventana principal del juego
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Renderer del juego

    // Se cargan las imagenes que usa el programa
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG); // Se permite cargar imagenes PNG y JPG
    SDL_Texture *fondo = initialize_texture_from_file("fondo.jpg", renderer);
    SDL_Texture *naveUsuario = initialize_texture_from_file("bob.png", renderer);
    SDL_Texture *misilUsuario = initialize_texture_from_file("pina.png",renderer);
    SDL_Texture *bunker = initialize_texture_from_file("bunker.png",renderer);
    SDL_Texture *tipoA = initialize_texture_from_file("tipoA.png",renderer);
    SDL_Texture *tipoB = initialize_texture_from_file("tipoB.png",renderer);
    SDL_Texture *tipoC = initialize_texture_from_file("tipoC.png",renderer);


    // Se obtiene el ancho y el alto de una imagen (en este caso del fondo de la pantalla)
    int image_width, image_height;
    SDL_QueryTexture(fondo, NULL, NULL, &image_width, &image_height);

    // Crea el rect�ngulo donde se dibujar� el fondo de la pantalla
    SDL_Rect textureFondo;
    textureFondo.x = 0;
    textureFondo.y = 0;
    textureFondo.w = image_width;
    textureFondo.h = image_height;

    //Rectangulos de los bunkers
    SDL_Rect textureBunker1;
    textureBunker1.x = 100;
    textureBunker1.y = 370;
    textureBunker1.w = 150;
    textureBunker1.h = 200;

    SDL_Rect textureBunker2;
    textureBunker2.x = 430;
    textureBunker2.y = 370;
    textureBunker2.w = 150;
    textureBunker2.h = 200;

    SDL_Rect textureBunker3;
    textureBunker3.x = 750;
    textureBunker3.y = 370;
    textureBunker3.w = 150;
    textureBunker3.h = 200;

    window = SDL_CreateWindow("Space Invaders",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,
    SDL_WINDOW_SHOWN); // Se crea la ventana principal del juego

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Renderer del juego


    unsigned short iterations = 0;
    InvaderHandler* handler = createHandler();

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

        if(handler->invaderList == NULL){
            newEnemies(handler);
        }
        if(iterations % 45 == 0){
            DispararInvaders(handler);
            iterations = 0;
        }else if(iterations % 25 == 0){
            MoverInvaders(handler);
        }




        //Se libera la memoria de los misiles que salen de la pantalla
        EliminarMisiles(nave.misiles,&textureBunker1,&textureBunker2,&textureBunker3);
        EnemyBulletHandler(handler,&textureBunker1,&textureBunker2,&textureBunker3);
        DibujarMisiles_Invaders(handler,renderer,tipoA,tipoB,tipoC);
        iterations++;




        SDL_SetRenderDrawColor(renderer,0,0,0,0);// RGB del color negro
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fondo, NULL, &textureFondo);//Se coloca el fondo de la pantalla
        dibujarBunkers(bunkerPantalla,renderer,bunker);//Se dibujan los bunkers
        DibujarNave_Misiles(&nave,renderer,misilUsuario,naveUsuario); //Se dibuja la nave del usuario y los misiles que dispara
        DibujarMisiles_Invaders(handler,renderer,tipoA,tipoB,tipoC);//Se dibujan los invaders
        SDL_RenderPresent(renderer);
        SDL_Delay(MS); // Tiempo de espera en milisegundos


        SDL_RenderPresent(renderer);
        SDL_Delay(MS); // Tiempo de espera en milisegundos


    }

    //Se libera la memoria dinámica del programa
    //Se libera la memoria din�mica del programa
    SDL_DestroyTexture(fondo);
    SDL_DestroyTexture(naveUsuario);
    SDL_DestroyTexture(misilUsuario);
    SDL_DestroyTexture(bunker);
    SDL_DestroyTexture(tipoA);
    SDL_DestroyTexture(tipoB);
    SDL_DestroyTexture(tipoC);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

//Funci�n que se encarga de inicializar una imagen y colocarla en el renderizador del programa
SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}