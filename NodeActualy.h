#ifndef NODE_ACTUALLY_H
#define NODE_ACTUALLY_H
#include "NodeGame.h"

typedef enum NodeType{
    MOTHER_NODE,
    WORKER_NODE,
    FIGHTER_NODE,
}NodeType;

typedef struct Node{
    int posx;
    int posy;
    int player;
    char name;
    struct Node* ConnectedNodes[3];
    int ConnectedNodesCount;
    NodeType type;
    int resources[TILE_TYPE_AMOUNT];
}Node;

typedef enum TileType{
    GOLD_TILE,
    WOOD_TILE,
}TileType;

typedef struct Tile{
    TileType resource;
    int amount;
}Tile;



#endif