
#ifndef MINE_STRUCTS_H
	#define MINE_STRUCTS_H
	
	#include <stdbool.h>

	typedef struct Tile_struct{
		int mines_near;
		bool is_revealed;
		bool is_flagged;
		bool is_questioned;
		bool is_mine;
	}Tile;

	typedef struct Board_struct{
		int num_rows;
		int num_cols;
		int num_mines;
		Tile **tiles;
	}Board;

#endif