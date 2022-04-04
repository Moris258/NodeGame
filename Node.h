#ifndef NODE_H
#define NODE_H
#include "NodeGame.h"
#include "NodeActualy.h"
#include "LinkedList.h"

typedef struct PathList_E{
    struct PathList_E* next;
    NodeList* path;
    int length;
}PathList_E;

typedef struct PathList{
    PathList_E* first;

}PathList;

extern int suppress_error;

void NodeCreate(char name, NodeType type, int x, int y, Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player);
void ConnectNode(Node* node, Node* node2);
void NodeDestroy(Node* node);
void GameAreaDestroy(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]);
void NodeError(int errtype);
Node* FindClosestMotherNode(Node* start);
void AdvanceTurn(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* MotherNode, NodeList* list);


#endif