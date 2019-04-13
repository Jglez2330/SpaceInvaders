//
// Created by Fabricio on 9/4/2019.
//

#include "misil.h"

#ifndef PRUEBAINTERFAZ_NAVE_H
#define PRUEBAINTERFAZ_NAVE_H

#define MISIL_VEL 5

typedef struct Nave Nave;

 struct Nave{
    int x1,y1;
    int vx;
    Misil *misiles;
};

void DibujarNave_Misiles(Nave *nave, SDL_Renderer *renderer, SDL_Texture *texture1, SDL_Texture *texture2);
void NaveAvanzaDer(Nave *nave);
void NaveAvanzaIzq(Nave *nave);
void NaveDispara(Nave *nave);

#endif //PRUEBAINTERFAZ_NAVE_H
