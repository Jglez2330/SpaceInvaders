//
// Created by Fabricio on 9/4/2019.
//

#include "misil.h"

//Función que va cambiando las posiciones de los misiles disparados por el usuario
void MisilAvanza(Misil *misil)
{
    misil->y1 += misil->vy;
}

//Función que libera la memoria de los misiles que salen del rango de la pantalla
void EliminarMisiles(Misil *misiles,SDL_Rect *bunker1,SDL_Rect *bunker2,SDL_Rect *bunker3)
{
    Misil *misil = misiles;
    if(misil == NULL){
        return;
    }

    Misil *auxMisil;
    while (misil->siguiente != NULL){
        SDL_Rect rectMisil = crearRectanguloMisil(misil->siguiente);
        if((misil->siguiente->y1 < 0) | (colisiones(&rectMisil,bunker1) == 1) | (colisiones(&rectMisil,bunker2) == 1)
           | (colisiones(&rectMisil,bunker3) == 1)){
            auxMisil = misil->siguiente->siguiente;
            SDL_free(misil->siguiente);
            misil->siguiente = auxMisil;
        }
        else{
            misil = misil->siguiente;
        }
    }

}

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

//Funci�n que crea un rect�ngulo de un misil dado
SDL_Rect crearRectanguloMisil(Misil *misil)
{
    SDL_Rect retorno;
    retorno.x = misil->x1;
    retorno.y = misil->y1;
    retorno.w = 90;
    retorno.h = 90;
    return retorno;

}
