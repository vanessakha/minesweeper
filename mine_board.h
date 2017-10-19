
#ifndef MINE_BOARD_H

	#define MINE_BOARD_H

	#include "mine_structs.h"

	void ReadArgs(int argc, char *argv[], int *num_rows, int *num_cols, int *num_mines, int *seed);
	void CreateBoard(Board *board, int argc, int num_rows, int num_cols, int num_mines, int seed);
	void PlaceMines(Board *board);
	void LabelTiles(Board *board);
	void LabelMinesNearby(Board *board);
	void Seed(int argc, int seed);
	void TopLeftMines(Board *board, int i, int j);
	void BottomLeftMines(Board *board, int i, int j);
	void TopRightMines(Board *board, int i, int j);
	void BottomRightMines(Board *board, int i, int j);
	void TopMines(Board *board, int i, int j);
	void BottomMines(Board *board, int i, int j);
	void LeftMines(Board *board, int i, int j);
	void RightMines(Board *board, int i, int j);
	void PrintBoard(Board board);
	void DestroyBoard(Board *board);
	void TileAbove(Board *board, int i, int j);
	void TileBelow(Board *board, int i, int j);
	void TileRight(Board *board, int i, int j);
	void TileLeft(Board *board, int i, int j);
	void TileUpRight(Board *board, int i, int j);
	void TileDownRight(Board *board, int i, int j);
	void TileUpLeft(Board *board, int i, int j);
	void TileDownLeft(Board *board, int i, int j);

#endif

