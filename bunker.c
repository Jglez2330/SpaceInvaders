//
// Created by Fabricio on 12/4/2019.
//
#include "bunker.h"

Bunker* crearBunkers(){
    Bunker *bunker1 = (Bunker*) SDL_malloc(sizeof(Bunker));
    bunker1->x1 = 100;
    bunker1->y1 = 370;

    Bunker *bunker2 = (Bunker*) SDL_malloc(sizeof(Bunker));
    bunker2->x1 = 430;
    bunker2->y1 = 370;

    Bunker *bunker3 = (Bunker*) SDL_malloc(sizeof(Bunker));
    bunker3->x1 = 750;
    bunker3->y1 = 370;

    bunker1->siguiente = bunker2;
    bunker2->siguiente = bunker3;
    return bunker1;

}

void dibujarBunkers (Bunker *bunker, SDL_Renderer *renderer,SDL_Texture *texture){
    while(bunker != NULL){
        SDL_Rect textureBunker;
        textureBunker.x = bunker->x1;
        textureBunker.y = bunker->y1;
        textureBunker.w = 150;
        textureBunker.h = 200;
        SDL_RenderCopy(renderer, texture, NULL, &textureBunker);
        bunker = bunker->siguiente;
    }

}


