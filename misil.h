//
// Created by Fabricio on 9/4/2019.
//

#include <SDL2/SDL.h>
#include <stdio.h>

#ifndef PRUEBAINTERFAZ_MISIL_H
#define PRUEBAINTERFAZ_MISIL_H

typedef struct Misil Misil;

 struct Misil{
    int x1,y1;
    int vy;
    Misil *siguiente;
};

void MisilAvanza (Misil *misil);
void EliminarMisiles(Misil *misiles,SDL_Rect *bunker1,SDL_Rect *bunker2,SDL_Rect *bunker3);
int colisiones(SDL_Rect *rect1, SDL_Rect *rect2);
SDL_Rect crearRectanguloMisil(Misil *misil);

#endif //PRUEBAINTERFAZ_MISIL_H
