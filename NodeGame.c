#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Node.h"
#include "NodeGame.h"
#include "Tile.h"
#include "NodeActualy.h"
#include "AlphaBeta.h"




//TODO:
//Add 2 player support to AI
int main(int argc, char* argv[]){

    if(argc < 3)
    {
        fprintf(stderr, "Too few arguments.");
        return 1;
    }

    int seed = strtol(argv[1], NULL, 10);
    int depth = strtol(argv[2], NULL, 10);

    Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
    Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT];
    //Node* MotherNodes[2];

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            GameArea[x][y] = NULL;
        }
    }

    srand(seed);

    NodeCreate('M', MOTHER_NODE, 0, 0, GameArea, 1);
    //MotherNodes[0] = GameArea[0][0];
    //NodeCreate('W', WORKER_NODE, 1, 0, GameArea, 1);
    //NodeCreate('W', WORKER_NODE, 0, 1, GameArea, 1);

    NodeCreate('B', MOTHER_NODE, 9, 9, GameArea, 2);
    //MotherNodes[1] = GameArea[9][9];

    //NodeCreate('A', WORKER_NODE, 8, 9, GameArea, 2);
    //NodeCreate('A', WORKER_NODE, 9, 8, GameArea, 2);
    //NodeCreate('A', WORKER_NODE, 8, 8, GameArea, 2);


    //ConnectNode(GameArea[0][0], GameArea[1][0]);
    //ConnectNode(GameArea[0][0], GameArea[0][1]);

    //ConnectNode(GameArea[9][9], GameArea[9][8]);
    //ConnectNode(GameArea[9][9], GameArea[8][9]);
    //ConnectNode(GameArea[9][9], GameArea[8][8]);
    FillGameTiles(GameTiles);



    int turns = 6;
    Operation best_move;
    int player = 1;
    int player1_value = CalculateValue(GameArea, 1);
    int player2_value = CalculateValue(GameArea, 2);
    while(turns > 0){

        AlphaBetaStart(0, depth, GameTiles, GameArea, NULL, &best_move, player);

        printf("\nSUCCESS: %d %d %d %d %d PLAYER: %d\n", best_move.type, best_move.x1, best_move.y1, best_move.x2, best_move.y2, player);
        DoOperation(GameTiles, GameArea, &best_move, player);        

        player1_value = CalculateValue(GameArea, 1);
        player2_value = CalculateValue(GameArea, 2);
        printf("\n%d %d", player1_value, player2_value);

        turns--;
        player = player == 1 ? 2 : 1;
    }

    

    if(player1_value > player2_value){
        printf("\nPlayer 1 wins. %d %d\n", player1_value, player2_value);
    }
    else{
        printf("\nPlayer 2 wins. %d %d\n", player1_value, player2_value);
    }

    DrawGame(GameTiles, GameArea);

    GameAreaDestroy(GameArea);
    DestroyGameTiles(GameTiles);

    return 0;
}