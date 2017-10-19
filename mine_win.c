//mine_win.c	
#include "mine_structs.h"
#include "mine_board.h"
#include "mine_moves.h"
#include "mine_win.h"
#include <stdio.h>
#include <stdbool.h>

// WIN=====================================

bool isGameOver(Board board, bool lost){
	return (win(board) || lost);
}


bool win(Board board){
	// win if all non-mines are revealed and all mines are flagged
	return nonMinesRevealed(board) && allMinesFlagged(board);
}


bool nonMinesRevealed(Board board){
	int i, j;
	for(i = 0; i < board.num_rows; i++){
		for (j = 0; j < board.num_cols; j++){
			if ((board.tiles[i][j].is_mine == false) && (board.tiles[i][j].is_revealed == false)){ // if any tile is non-mine and unrevealed...
				return false; // return false --> game isn't over
			}
		}
	}
	return true; // otherwise, if all non-mines are revealed, return true;
}


bool allMinesFlagged(Board board){
	int i, j;
	for (i = 0; i< board.num_rows; i++){
		for (j = 0; j < board.num_cols; j++){ // if any tile is a mine and unflagged, return false
			if ((board.tiles[i][j].is_mine == true) && (board.tiles[i][j].is_flagged == false)){
				return false;
			}
		}
	}
	return true; // if all mines are flagged, return true;
}


void RevealAllTiles(Board *board){
	int i, j;
	for(i = 0; i < board->num_rows; i++){
		for(j = 0; j < board->num_cols; j++){
			if (board->tiles[i][j].is_revealed == false){
				board->tiles[i][j].is_revealed = true;
			}
		}
	}
}


void DeclareWinner(Board board, bool lost){
	if (win(board)){
		printf("You Won!!\n");
	}
	else if (lost){
		printf("You Lost :(\n");
	}
}