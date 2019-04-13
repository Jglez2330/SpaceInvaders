//
// Created by jose on 08/04/19.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"
#include "cJSON.h"
int numeroLista = 0;
Node* createList(){
    Node* head = NULL;
    return head;
}

void add(Node** head, Invader* data){
    Node* actual = *head;
    Node* newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = NULL;

    if(!*head){
        *head = newNode;
    } else{
        while (actual->next != NULL){
            actual = actual->next;
        }
        actual->next = newNode;
    }

}

void printList(Node *head){
    Node* actual = head;
    while(actual!=NULL){
        printf("[%d\t|\t%p]->\n", actual->data->ID, actual->next);
        actual = actual->next;
    }
    printf("NULL \n");
}

void delete(Node** head, int target){
    Node* actual = *head;

    Node* previous = NULL;

    while(actual != NULL){
        if(actual->data->ID == target){
            if(previous == NULL){
                *head = actual->next;
            }else{
                previous->next = actual->next;
            }
            free(actual);
            break;
        }
        previous = actual;
        actual = actual->next;
    }
}

void deleteList(Node** head){
    Node* actual = *head;
    Node* previous = *head;

    while(previous != NULL){
        actual = previous;
        previous = actual->next;
        if (previous != NULL){
            free(actual);
        }
    }
}

cJSON* LtoJ(Node** head){
    Node* actual = *head;
    cJSON* lista = cJSON_CreateObject();
    cJSON* listaArray = cJSON_CreateArray();
    while (actual != NULL){
        cJSON_AddItemToArray(listaArray,ItoJ(actual->data));
        actual = actual->next;

    }

    cJSON_AddItemToObject(lista,"lista",listaArray);
    return lista;

}

