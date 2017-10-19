//mine_moves.h

#ifndef MINE_MOVES_H

	#define MINE_MOVES_H

	#include "mine_structs.h"
	
	// Moves:
	void PrintMinesLeft(Board board, int num_mines_left);
	char GetMove(Board board, int *row, int *col);
	char GetAction(Board board, int row, int col, int *action, int *max_action);
	void PlayMove(Board *board, int row, int col, char action_code, int *num_mines_left, bool *lost);
	void RevealTiles(Board *board, int row, int col);

#endif

