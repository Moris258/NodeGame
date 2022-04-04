#ifndef TILE_H
#define TILE_H
#include "Node.h"
#include "NodeGame.h"
#include "NodeActualy.h"



void FillGameTiles(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]);
void DestroyGameTiles(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]);
void DrawGame(Tile* GameTiles[GAME_AREA_WIDTH][GAME_AREA_HEIGHT], Node* GameArea[GAME_AREA_WIDTH][GAME_AREA_HEIGHT]);


#endif