#include <stdlib.h>
#include <SDL_render.h>
#include "invader.h"
#include "misil.h"

//
// Created by jose on 08/04/19.
//
Invader* createInvader(char tipo, int posX, int posY, int ID){
    Invader* alien = malloc(sizeof(Invader));
    alien->tipo = tipo;
    alien->x = posX;
    alien->y = posY;
    alien->ID = ID;
    alien->misiles = NULL;
    if(tipo == 'a'){
        alien->puntos = 10;
        alien->vida = 1;
    }else if(tipo == 'b'){
        alien->puntos = 20;
        alien->vida = 2;
    }else{
        alien->puntos = 40;
        alien->vida = 3;
    }
    return alien;
}


void InvaderAvanza(Invader* invader){
    invader->y += 10;
}


//Función que dispara los misiles de la nave
void InvaderDispara(Invader* invader)
{
    if(invader->misiles == NULL){
        invader->misiles = (Misil *) SDL_malloc(sizeof(Misil));
        invader->misiles->x1 = invader->x;
        invader->misiles->y1 = invader->y;
        invader->misiles->vy = 20;
        invader->misiles->siguiente = NULL;
    }
    else{
        Misil *nuevoMisil = invader->misiles;
        while(nuevoMisil->siguiente != NULL){
            nuevoMisil = nuevoMisil->siguiente;
        }
        nuevoMisil->siguiente = (Misil *) SDL_malloc(sizeof(Misil));
        nuevoMisil = nuevoMisil->siguiente;
        nuevoMisil->x1 = invader->x;
        nuevoMisil->y1 = invader->y;
        nuevoMisil->vy = 20;
        nuevoMisil->siguiente = NULL;
    }
}

