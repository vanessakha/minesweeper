#include "mine_structs.h"
#include "mine_board.h"
#include "mine_moves.h"
#include "mine_win.h"

void MineSweeper(int argc, char *argv[]){
	Board board; 
	int num_mines_left;
	int num_rows, num_cols, num_mines, seed;
	int row, col;
	bool lost = false;
	char action_code;

	// read command line arguments
	ReadArgs(argc, argv, &num_rows, &num_cols, &num_mines, &seed);

	//board creation
	CreateBoard(&board, argc, num_rows, num_cols, num_mines, seed);

	num_mines_left = board.num_mines;
	while(!isGameOver(board, lost)){
		PrintMinesLeft(board, num_mines_left);
		PrintBoard(board);
		action_code = GetMove(board, &row, &col); 
		PlayMove(&board, row, col, action_code, &num_mines_left, &lost);
	}

	RevealAllTiles(&board); 
	PrintBoard(board);
	DeclareWinner(board, lost);
	DestroyBoard(&board);
}

int main(int argc, char *argv[]){
	MineSweeper(argc, argv);
	return 0;
}