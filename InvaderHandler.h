//
// Created by jose on 11/04/19.
//

#ifndef SPACEINVADERS_INVADERHANDLER_H
#define SPACEINVADERS_INVADERHANDLER_H

#include "linkedList.h"

typedef struct InvaderHandler{
    Node* invaderList;
    unsigned int IDcounter;


}InvaderHandler;

InvaderHandler* createHandler();

void newEnemies(InvaderHandler* handler);

void MoverInvaders(InvaderHandler* handler);

void DispararInvaders(InvaderHandler* handler);

void DibujarMisiles_Invaders(InvaderHandler* handler,SDL_Renderer *renderer,SDL_Texture *texture1,SDL_Texture *texture2,SDL_Texture *texture3);

void EnemyBulletHandler(InvaderHandler* handler,SDL_Rect *bunker1,SDL_Rect *bunker2,SDL_Rect *bunker3);

#endif //SPACEINVADERS_INVADERHANDLER_H
