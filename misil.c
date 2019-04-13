//
// Created by Fabricio on 9/4/2019.
//

#include "misil.h"

//Función que va cambiando las posiciones de los misiles disparados por el usuario
void MisilAvanza(Misil *misil)
{
    misil->y1 += misil->vy;
    misil->y2 += misil->vy;
}

//Función que libera la memoria de los misiles que salen del rango de la pantalla


int colisiones(SDL_Rect *rect1, SDL_Rect *rect2)
{
    if(rect1->y >= rect2->y + rect2->h){
        return 0;
    }
    else if(rect1->x >= rect2->x + rect2->w){
        return 0;
    }
    else if(rect1->y + rect1->h <= rect2->y){
        return 0;
    }
    else if(rect1->x + rect1->w <= rect2->x){
        return 0;
    }
    else{
        return 1;
    }

}

SDL_Rect crearRectanguloMisil(Misil *misil)
{
    SDL_Rect retorno;
    retorno.x = misil->x1;
    retorno.y = misil->y1;
    retorno.w = 3;
    retorno.h = 3;
    return retorno;

}

