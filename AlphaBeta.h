#ifndef ALPHABETA_H
#define ALPHABETA_H
#include "Tile.h"

typedef enum Operation_Type{
    ADD_WORKER_NODE,
    CONNECT_NODES,
}Operation_Type;

typedef struct ABTree{
    struct ABTree** Children;
    struct ABTree* Parent;
    int alpha;
    int beta;
}ABTree;

typedef struct Operation{
    Operation_Type type;
    int x1;
    int y1;
    int x2;
    int y2;
}Operation;

void AlphaBetaStart(int depth, int max_depth, Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], ABTree* root, Operation* operation, int player);
void DoOperation(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Operation* operation, int player);
int CalculateValue(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player);

#endif