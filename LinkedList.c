#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

NodeList* NodeList_Init(){
    NodeList* temp = (NodeList*)malloc(sizeof(NodeList));
    temp->first = NULL;
    return temp;
}

void NodeList_AddItem(Node* item, NodeList* list){
    if(list->first == NULL){

        list->first = (NodeList_E*)malloc(sizeof(NodeList_E));
        if(!list->first){
            fprintf(stderr, "Failed to allocate memory.");
            return;
        }
        list->first->node = item;
        list->first->next = NULL;
        return;
    }

    NodeList_E* temp = list->first;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = (NodeList_E*)malloc(sizeof(NodeList_E));
    if(!temp->next){
        fprintf(stderr, "Failed to allocate memory.");
        return;
    }
    temp->next->node = item;
    temp->next->next = NULL;
}

int NodeList_Search(NodeList* list, Node* item){
    NodeList_E* temp = list->first;

    while(temp != NULL){
        if(temp->node == item){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void NodeList_Destroy(NodeList* list){
    NodeList_E* temp = list->first;
    while(temp != NULL){
        NodeList_E* temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    free(list);
}
