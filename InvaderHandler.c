//
// Created by jose on 11/04/19.
//

#include "InvaderHandler.h"


InvaderHandler* createHandler(){
    InvaderHandler* handler = malloc(sizeof(InvaderHandler));
    handler->invaderList=createList();
    return handler;
}

void newEnemies(InvaderHandler* handler){
    char tipo;
    for(int i = 0; i < 7; i++){
        if(handler->IDcounter % 3 == 0){
            tipo = 'a';
        }else if(handler->IDcounter % 3 == 1){
            tipo = 'b';
        }else{
            tipo = 'c';
        }

        Invader* invader = createInvader(tipo,i*100+100,100,handler->IDcounter);
        add(&handler->invaderList, invader);

        handler->IDcounter++;


    }
}


void DibujarMisiles_Invaders(InvaderHandler* handler,SDL_Renderer *renderer,SDL_Texture *texture1,SDL_Texture *texture2,SDL_Texture *texture3){
    Node* temp = handler->invaderList;
    while (temp != NULL){

        Misil *nuevoMisil = temp->data->misiles;
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

        SDL_Rect textureInvader;
        textureInvader.x = temp->data->x;
        textureInvader.y = temp->data->y;
        textureInvader.w = 65;
        textureInvader.h = 65;
        if(temp->data->tipo == 'a'){
            SDL_RenderCopy(renderer, texture1, NULL, &textureInvader);
        }

        else if(temp->data->tipo == 'b'){
            SDL_RenderCopy(renderer, texture2, NULL, &textureInvader);
        }

        else{
            SDL_RenderCopy(renderer, texture3, NULL, &textureInvader);
        }


        temp = temp->next;
    }
}

void MoverInvaders(InvaderHandler* handler){
    Node* temp = handler->invaderList;
    while (temp != NULL){


        InvaderAvanza(temp->data);

        temp = temp->next;
    }
}

void DispararInvaders(InvaderHandler* handler){
    Node* temp = handler->invaderList;
    while (temp != NULL){

        InvaderDispara(temp->data);

        temp = temp->next;
    }
}

void EnemyBulletHandler(InvaderHandler* handler,SDL_Rect *bunker1,SDL_Rect *bunker2,SDL_Rect *bunker3){
    Node* temp = handler->invaderList;
    while (temp != NULL){

        EliminarMisiles(temp->data->misiles,bunker1,bunker2,bunker3);

        temp = temp->next;
    }
}