//
// Created by Fabricio on 12/4/2019.
//


#ifndef SDL2TUT_BUNKER_H
#define SDL2TUT_BUNKER_H

#include <SDL2/SDL_image.h>


typedef struct Bunker{

    int x1,y1;
    struct Bunker *siguiente;

}Bunker;

Bunker* crearBunkers();

void dibujarBunkers (Bunker *bunker, SDL_Renderer *renderer,SDL_Texture *texture);


#endif //SDL2TUT_BUNKER_H
