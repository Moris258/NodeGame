#include <stdlib.h>
#include <stdio.h>
#include "AlphaBeta.h"

void CopyTiles(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Tile* NewTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){
    FillGameTiles(NewTiles);
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            NewTiles[x][y]->amount = GameTiles[x][y]->amount;
            NewTiles[x][y]->resource = GameTiles[x][y]->resource;
        }
    }
}

void CopyArea(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* NewArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){   
    suppress_error = 1;

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            NewArea[x][y] = NULL;
            if(GameArea[x][y] != NULL){
                NodeCreate(GameArea[x][y]->name, GameArea[x][y]->type, x, y, NewArea, GameArea[x][y]->player);
                for(int i = 0; i < TILE_TYPE_AMOUNT; i++){
                    NewArea[x][y]->resources[i] = GameArea[x][y]->resources[i];
                }
            }
        }
    }
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL){
                for(int i = 0; i < GameArea[x][y]->ConnectedNodesCount; i++){
                    Node* dest = GameArea[x][y];
                    Node* src = GameArea[x][y]->ConnectedNodes[i];

                    ConnectNode(NewArea[dest->posx][dest->posy], NewArea[src->posx][src->posy]);
                }
            }
        }
    }

    suppress_error = 0;
}

int GetFreeConnections(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player){
    (void)player;

    int count = 0;

    NodeList* list = NodeList_Init();

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL)
            {
                if(GameArea[x][y]->ConnectedNodesCount >=3 ){
                    NodeList_AddItem(GameArea[x][y], list);
                    continue;
                }

                for(int i = 0; i < GAME_AREA_HEIGHT; i++){
                    for(int k = 0; k < GAME_AREA_WIDTH; k++){
                        if(GameArea[k][i] != NULL && GameArea[x][y] != GameArea[k][i])
                        {
                            int unconnected = 1;

                            if(GameArea[k][i]->ConnectedNodesCount >= 3 || GameArea[x][y]->player != GameArea[k][i]->player)
                                continue;

                            for(int o = 0; o < GameArea[x][y]->ConnectedNodesCount; o++){
                                if(GameArea[x][y]->ConnectedNodes[o] == GameArea[k][i])
                                {
                                    unconnected = 0;
                                }
                            }

                            if(!unconnected)
                                continue;

                            if(!(NodeList_Search(list, GameArea[k][i]))){
                                count++;
                            }
                        }
                    }
                }
                
                NodeList_AddItem(GameArea[x][y], list);
            }
        }
    }

    NodeList_Destroy(list);

    return count;
}

int Factorial(int number){
    int result = 1;
    for(int i = 1; i <= number; i++){
        result *= i;

    }
    return result;
}

int CalculateValue(Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player){
    int value = 0;
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL && GameArea[x][y]->player == player){
                for(int i = 0; i < TILE_TYPE_AMOUNT; i++){
                    value += GameArea[x][y]->resources[i];
                }
            }
        }
    }
    return value;
}

void FillOperations(Operation ops[], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], int player){
    (void)player;

    ops[0].type = ADD_WORKER_NODE;
    int max = INT_MIN;
    int index = 1;

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameTiles[x][y]->amount > max && GameArea[x][y] == NULL)
            {
                max = GameTiles[x][y]->amount;
                ops[0].x1 = x;
                ops[0].y1 = y;
                ops[0].x2 = 0;
                ops[0].y2 = 0;
            }
        }
    }

    NodeList* list = NodeList_Init();

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL)
            {
                if(GameArea[x][y]->ConnectedNodesCount >= 3){
                    NodeList_AddItem(GameArea[x][y], list);
                    continue;
                }

                for(int i = 0; i < GAME_AREA_HEIGHT; i++){
                    for(int k = 0; k < GAME_AREA_WIDTH; k++){
                        if(GameArea[k][i] != NULL && GameArea[x][y] != GameArea[k][i])
                        {
                            int unconnected = 1;

                            if(GameArea[k][i]->ConnectedNodesCount >= 3 || GameArea[x][y]->player != GameArea[k][i]->player)
                                continue;

                            for(int o = 0; o < GameArea[x][y]->ConnectedNodesCount; o++){
                                if(GameArea[x][y]->ConnectedNodes[o] == GameArea[k][i])
                                {
                                    unconnected = 0;
                                }
                            }

                            if(!unconnected)
                                continue;

                            if(!(NodeList_Search(list, GameArea[k][i]))){
                                ops[index].type = CONNECT_NODES;
                                ops[index].x1 = x;
                                ops[index].y1 = y;
                                ops[index].x2 = k;
                                ops[index].y2 = i;

                                index++;
                            }
                        }
                    }
                }
                
                NodeList_AddItem(GameArea[x][y], list);
            }
        }
    }

    NodeList_Destroy(list);    
}

void DoOperation(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Operation* operation, int player){
    switch(operation->type){
        case ADD_WORKER_NODE:
            NodeCreate(player == 1 ? 'W' : 'A', WORKER_NODE, operation->x1, operation->y1, GameArea, player);

            break;
        case CONNECT_NODES:
            ConnectNode(GameArea[operation->x1][operation->y1], GameArea[operation->x2][operation->y2]);

            break;
        default:
            break;
    }
    Node* MotherNode = NULL;

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL)
            {
                if(GameArea[x][y]->type == MOTHER_NODE && GameArea[x][y]->player == player){
                    MotherNode = GameArea[x][y];
                    break;
                }
            }
        }
        if(MotherNode != NULL)
            break;
    }
    NodeList* list = NodeList_Init();

    AdvanceTurn(GameTiles, MotherNode, list);

    NodeList_Destroy(list);

}

void AlphaBetaStart(int depth, int max_depth, Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], ABTree* root, Operation* operation, int player){
    
    Tile* NewTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
    Node* NewArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
    CopyArea(GameArea, NewArea);
    CopyTiles(GameTiles, NewTiles);


    int value = 0;

    /*
    int alpha_player;

    if(depth % 2 == 0){
        alpha_player = player;
    }
    else{
        alpha_player = player == 2 ? 1 : 2;
    }*/


    if(root == NULL){
        root = (ABTree*)malloc(sizeof(ABTree));
        root->alpha = INT_MIN;
        root->beta = INT_MAX;
        root->Parent = NULL;
    }
    else{
        DoOperation(NewTiles, NewArea, operation, player == 1 ? 2 : 1);
        //printf("\n%d %d %d %d %d", operation->type, operation->x1, operation->y1, operation->x2, operation->y2);
        //printf("\n");
        //DrawGame(NewTiles, NewArea);
    }

    int operations = 1 + GetFreeConnections(NewArea, player);
    //printf("\noperations: %d Player: %d\n", operations, player);
    //DrawGame(NewTiles, NewArea);
    Operation ops[operations];


    if(depth != max_depth){
        FillOperations(ops, NewArea, NewTiles, player);

        root->Children = (ABTree**)malloc(sizeof(ABTree*) * operations);
        if(!root->Children)
            fprintf(stderr, "FAIL");

        for(int i = 0; i < operations; i++){
            root->Children[i] = (ABTree*)malloc(sizeof(ABTree));
            if(!root->Children[i])
                fprintf(stderr, "FAIL");
            root->Children[i]->Parent = root;
        }
        
        for(int i = 0; i < operations; i++){
            if(root->alpha >= root->beta)
                break;
            root->Children[i]->alpha = root->alpha;
            root->Children[i]->beta = root->beta;

            AlphaBetaStart(depth + 1, max_depth, NewTiles, NewArea, root->Children[i], &ops[i], player == 1 ? 2 : 1);
        }

        if(root->Parent != NULL){
            if(depth % 2 == 1){
                if(root->Parent->alpha < root->beta)
                    root->Parent->alpha = root->beta;
            }
            else{
                if(root->Parent->beta > root->alpha)
                    root->Parent->beta = root->alpha;
            }
        }
    }
    else{        
        if(depth % 2 == 1){
            value = CalculateValue(NewArea, player == 2 ? 1 : 2);
            //printf("\nVALUE ALPHA: %d\n", value);
            root->beta = value;
            if(root->Parent->alpha < root->beta)
                root->Parent->alpha = root->beta;
        }
        else{
            value = CalculateValue(NewArea, player);
            //printf("\nVALUE BETA: %d\n", value);
            root->alpha = value;
            if(root->Parent->beta > root->alpha)
                root->Parent->beta = root->alpha;
        }
    }


    if(root->Parent == NULL){
        //printf("\nFINAL VALUE: %d\n", root->alpha);
        int best_move_index = 0;
        for(int i = 0; i < operations; i++){
            if(root->Children[i]->beta == root->alpha){
                best_move_index = i;
                break;
            }
        }
        operation->type = ops[best_move_index].type;
        operation->x1 = ops[best_move_index].x1;
        operation->y1 = ops[best_move_index].y1;
        operation->x2 = ops[best_move_index].x2;
        operation->y2 = ops[best_move_index].y2;
    }


    //FREE
    if(depth != max_depth){ 
        for(int i = 0; i < operations; i++){
            free(root->Children[i]);
        }
        free(root->Children);
    }
    

    if(root->Parent == NULL)
        free(root);
    GameAreaDestroy(NewArea);
    DestroyGameTiles(NewTiles);
    //printf("\nEXIT\n");

    return;
}