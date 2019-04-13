//
// Created by Fabricio on 9/4/2019.
//

#include "nave.h"

//Función que mueve la nave a la derecha
void NaveAvanzaDer(Nave *nave){
    if(nave->x1 >= 900){
        return;
    }
    else{
        nave->x1 += nave->vx;
    }
}

//Función que mueve la nave a la izquierda
void NaveAvanzaIzq(Nave *nave){
    if(nave->x1 <= 20){
        return;
    }
    else{
        nave->x1 -= nave->vx;
    }
}

//Función que dispara los misiles de la nave
void NaveDispara(Nave *nave)
{
    if(nave->misiles == NULL){
        nave->misiles = (Misil *) SDL_malloc(sizeof(Misil));
        nave->misiles->x1 = nave->x1;
        nave->misiles->y1 = nave->y1;
        nave->misiles->vy = -MISIL_VEL;
        nave->misiles->siguiente = NULL;
    }
    else{
        Misil *nuevoMisil = nave->misiles;
        while(nuevoMisil->siguiente != NULL){
            nuevoMisil = nuevoMisil->siguiente;
        }
        nuevoMisil->siguiente = (Misil *) SDL_malloc(sizeof(Misil));
        nuevoMisil = nuevoMisil->siguiente;
        nuevoMisil->x1 = nave->x1;
        nuevoMisil->y1 = nave->y1;
        nuevoMisil->vy = -MISIL_VEL;
        nuevoMisil->siguiente = NULL;
    }
}

void DibujarNave_Misiles(Nave *nave, SDL_Renderer *renderer, SDL_Texture *texture1, SDL_Texture *texture2)
{
    //Dibujar Misiles
    Misil *nuevoMisil = nave->misiles;
    while(nuevoMisil != NULL){
        MisilAvanza(nuevoMisil);
        SDL_Rect textureMisil;
        textureMisil.x = nuevoMisil->x1;
        textureMisil.y = nuevoMisil->y1;
        textureMisil.w = 30;
        textureMisil.h = 30;
        SDL_RenderCopy(renderer, texture1, NULL, &textureMisil);
        nuevoMisil = nuevoMisil->siguiente;
    }

    //Dibujar Nave del usuario
    SDL_Rect textureNave;
    textureNave.x = nave->x1;
    textureNave.y = nave->y1;
    textureNave.w = 90;
    textureNave.h = 90;
    SDL_RenderCopy(renderer, texture2, NULL, &textureNave);
}
