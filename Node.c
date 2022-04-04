#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"

#define MAX_CONNECT 3
#define NODE_FULL 0
#define NODE_INVALID 1
#define NODE_IN_USE 2

int suppress_error = 0;

PathList_E* FindShortestRoute(PathList* list){
    PathList_E* temp = list->first;
    PathList_E* shortest = temp;
    while(temp != NULL){
        if(temp->length < shortest->length){
            shortest = temp;
        }
        temp = temp->next;
    }
    return shortest;

}

void PathList_AddItem(PathList* list, Node* next, PathList_E* path){
    PathList_E* temp = list->first;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = (PathList_E*)malloc(sizeof(PathList_E));
    temp->next->length = path->length + 1;
    temp->next->next = NULL;
    temp->next->path = NodeList_Init();

    if(path->path->first == NULL){
        NodeList_AddItem(next, temp->next->path);
        return;
    }

    NodeList_E* node_list = path->path->first;

    while(node_list != NULL){
        NodeList_AddItem(node_list->node, temp->next->path);
        node_list = node_list->next;
    }
    NodeList_AddItem(next, temp->next->path);
}

void PathList_Remove(PathList* list, PathList_E* path){
    PathList_E* temp = list->first;
    if(temp == path){
        list->first = list->first->next;
        NodeList_Destroy(path->path);
        free(path);
        return;
    }

    while(temp->next != path){
        temp = temp->next;
    }

    temp->next = temp->next->next;
    NodeList_Destroy(path->path);
    free(path);
}

Node* FindClosestMotherNode(Node* start){
    if(start == NULL)
        return NULL;

    PathList* list = (PathList*)malloc(sizeof(PathList));
    list->first = (PathList_E*)malloc(sizeof(PathList_E));
    list->first->length = 0;
    list->first->next = NULL;
    list->first->path = NodeList_Init();

    int found = 0;
    while(!found){
        PathList_E* shortest = FindShortestRoute(list);

        NodeList_E* temp = shortest->path->first;
        if(temp == NULL){
            for(int i = 0; i < start->ConnectedNodesCount; i++){
                PathList_AddItem(list, start->ConnectedNodes[i], shortest);
            }
        }
        else{
            while(temp->next != NULL){
                temp = temp->next;
            }

            if(temp->node->type == MOTHER_NODE){
                Node* return_node = shortest->path->first->node;
                while(list->first != NULL){
                    PathList_Remove(list, list->first);
                }
                free(list);
                return return_node;
            }
            
            for(int i = 0; i < temp->node->ConnectedNodesCount; i++){
                PathList_AddItem(list, temp->node->ConnectedNodes[i], shortest);
            }
        }
        PathList_Remove(list, shortest);
    }

    while(list->first != NULL){
        PathList_Remove(list, list->first);
    }
    free(list);
    return NULL;

}

void NodeCreate(char name, NodeType type, int x, int y , Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player){
    if(GameArea[x][y] != NULL){
        NodeError(NODE_IN_USE);
        return;
    }

    Node* newnode = (Node*)malloc(sizeof(Node));
    if(!newnode){
        fprintf(stderr, "Failed to allocate memory");
        return;
    }

    newnode->name = name;
    newnode->ConnectedNodesCount = 0;
    newnode->type = type;
    newnode->posx = x;
    newnode->posy = y;
    newnode->player = player;

    for(int i = 0; i < TILE_TYPE_AMOUNT; i++){
        newnode->resources[i] = 0;
    }

    for(int i = 0; i < MAX_CONNECT; i++){
        newnode->ConnectedNodes[i] = NULL;
    }


    GameArea[x][y] = newnode;
    return;

}

void NodeError(int errtype){
    if(suppress_error)
        return;

    char *ErrMessages[] = {"\nNode fully saturated.", "\nInvalid node used.", "\nNode already filled."};
    fprintf(stderr, "%s", ErrMessages[errtype]);

}

void ConnectNode(Node* dest, Node* src){
    if(dest->ConnectedNodesCount >= 3 || src->ConnectedNodesCount >= 3){
        NodeError(NODE_FULL);
        return;
    }
    if(src == NULL || dest == NULL){
        NodeError(NODE_INVALID);
        return;
    }
    if(src == dest){
        NodeError(NODE_INVALID);
        return;
    }
    for(int i = 0; i < dest->ConnectedNodesCount; i++){
        if(dest->ConnectedNodes[i] == src){
            NodeError(NODE_INVALID);
            return;
        }
    }


    dest->ConnectedNodes[dest->ConnectedNodesCount] = src;
    dest->ConnectedNodesCount++;
    src->ConnectedNodes[src->ConnectedNodesCount] = dest;
    src->ConnectedNodesCount++;

}

void GameAreaDestroy(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL){
                NodeDestroy(GameArea[x][y]);
            }
        }
    }
}

void NodeDestroy(Node* node){
    free(node);
    return;
}

void AdvanceTurn(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* MotherNode, NodeList* list){
    if(NodeList_Search(list, MotherNode))
        return;

    NodeList_AddItem(MotherNode, list);
    for(int i = 0; i < MotherNode->ConnectedNodesCount; i++){
        if(MotherNode->type == WORKER_NODE)
        {
            if(GameTiles[MotherNode->posx][MotherNode->posy]->amount > 0){
                MotherNode->resources[GameTiles[MotherNode->posx][MotherNode->posy]->resource] += GameTiles[MotherNode->posx][MotherNode->posy]->amount--;
            }
                

            Node* dest = FindClosestMotherNode(MotherNode);
            for(int i = 0; i < TILE_TYPE_AMOUNT; i++){
                dest->resources[i] += MotherNode->resources[i];
                MotherNode->resources[i] = 0;
            }

        }
        if(MotherNode->ConnectedNodes[i]->type != MOTHER_NODE)
            AdvanceTurn(GameTiles, MotherNode->ConnectedNodes[i], list);
    }

}