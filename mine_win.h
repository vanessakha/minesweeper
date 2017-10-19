//mine_win.h

#ifndef MINE_WIN_H
	#define MINE_WIN_H

	#include <stdbool.h>
	#include "mine_structs.h"

	// Win:
	bool isGameOver(Board board, bool lost);
	bool win(Board board);
	bool nonMinesRevealed(Board board);
	bool allMinesFlagged(Board board);
	void RevealAllTiles(Board *board);
	void DeclareWinner(Board board, bool lost);

#endif