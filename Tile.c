#include <stdlib.h>
#include <stdio.h>
#include "Tile.h"
#include "Node.h"
#include "NodeGame.h"

void FillGameTiles(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            GameTiles[x][y] = (Tile*)malloc(sizeof(Tile));
            if(!GameTiles[x][y])
            {
                fprintf(stderr,"Failed to allocate memory.");
                return;
            }

            GameTiles[x][y]->amount = rand() % 70 + 30;
            GameTiles[x][y]->resource = rand() % TILE_TYPE_AMOUNT;
        }
    }
}

void DestroyGameTiles(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){
    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            free(GameTiles[x][y]);
        }
    }
}

void DrawGame(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]){
    (void)GameTiles;

    for(int y = 0; y < GAME_AREA_HEIGHT; y++){
        for(int x = 0; x < GAME_AREA_WIDTH; x++){
            if(GameArea[x][y] != NULL){
                printf("%c  ", GameArea[x][y]->name);
            }
            else{
                //printf("%d  ", GameTiles[x][y]->resource);
                printf(".  ");
            }
        }
        printf("\n");
    }
}
