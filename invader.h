//
// Created by jose on 08/04/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H




#include "misil.h"

typedef struct Invader{
    char tipo; //'a' calamar, 'b' cangrejo, 'c' pulpo
    int vida, puntos;
    int ID;
    int x,y;

    Misil *misiles;

}Invader;

Invader* createInvader(char tipo, int posX, int posY,int ID);

void InvaderAvanza(Invader* invader);

void InvaderDispara(Invader* invader);


#endif //SPACEINVADERS_INVADER_H
