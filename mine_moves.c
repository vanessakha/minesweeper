//mine_moves.c

#include "mine_structs.h"
#include "mine_moves.h"
#include "mine_board.h"
#include "mine_input_val.h"
#include <stdio.h>
#include <stdbool.h>

// MOVE================================

void PrintMinesLeft(Board board, int num_mines_left){
	printf("There are %d mines left\n", num_mines_left);
}


char GetMove(Board board, int *row, int *col){
	int action;
	int row_margin, num_args_read;
	char action_code;
	int max_action;
	// ask for row and column until input is valid 
	do{
		printf("Enter row a row between 0-%d and a column between 0-%d: ", board.num_rows - 1, board.num_cols - 1);
		num_args_read = scanf(" %d %d", &row_margin, col); 
		*row = board.num_rows - 1 - row_margin;
		if ((isValidInput(board, *row, *col)) && (isValidFormatting(num_args_read, 2))){
			action_code = GetAction(board, *row, *col, &action, &max_action);
		}
		if (((*row >= 0) && (*row < board.num_rows) && (*col >= 0) && (*col < board.num_cols)) && board.tiles[*row][*col].is_revealed == true){
			printf("This tile is already revealed.\n");
		}
	}while((!isValidFormatting(num_args_read, 2)) || (!isValidInput(board, *row, *col)) || (action_code == 'c') || (!isValidAction(action, max_action))); // checks if tile is revealed as well
	//action message (doesn't reach if action is cancel:
	return action_code;
}


char GetAction(Board board, int row, int col, int *action, int *max_action){
	char action_code = '\0';

	if (board.tiles[row][col].is_flagged == true){ // if tile is flagged...
		// actions = remove flag, cancel
		printf("Enter Action\n0. UnMark\n1. Cancel\nAction: ");
		scanf(" %d", action); // get action from user

		if (*action == 0){
			action_code = 'k'; // k = unmark
		}

		if (*action == 1){ 
			action_code = 'c'; // this is represents the move (needed since different tiles have action numbers that rep. different things)
		}
		*max_action = 1;
	}
	else if (board.tiles[row][col].is_questioned == true){ // if tile is questioned...
		// actions = remove, cancel
		printf("Enter Action\n0. UnQuestion\n1. Cancel\nAction: ");
		scanf(" %d", action); // get action input

		if (*action == 0){
			action_code = 'n'; // n = unquestion
		}
		if (*action == 1){ 
			action_code = 'c';
		}
		*max_action = 1;
	}

	else{ // if that tile isn't questioned or flagged
		printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\nAction: ");
		scanf(" %d", action); // get action input

		if (*action == 0){
			action_code = 'r'; // r = reveal
		}
		if (*action == 1){
			action_code = 'q'; // q = question
		}
		if (*action == 2){
			action_code = 'm'; // m = mark
		}
		if (*action == 3){ 
			action_code = 'c'; // c = cancel, ask for inp
		}
		*max_action = 3;
	}
	return action_code;
}

//!
void PlayMove(Board *board, int row, int col, char action_code, int *num_mines_left, bool *lost){
	if (action_code == 'k'){
		board->tiles[row][col].is_flagged = false;
		(*num_mines_left)++;
	}
	else if (action_code == 'n'){ // if tile is question and action is unquestion...
		board->tiles[row][col].is_questioned = false; //unquestion tile
	}
	else if (action_code == 'r'){ // reveal a concealed tile:
		if (board->tiles[row][col].is_mine == true){ // if tile is a mine, player loses!
			*lost = true;
		}
		else{ 
			RevealTiles(board, row, col); // if not mine... reveal tile(s)
		}
	}
	else if (action_code == 'q'){ // and action is question...
		board->tiles[row][col].is_questioned = true; // question tile
	}
	else if (action_code == 'm'){ // and action is mark...
		board->tiles[row][col].is_flagged = true; // flag tile
		(*num_mines_left)--;
	} 
// note: if tile is marked or flagged, it should always be concealed
}

//!
void RevealTiles(Board *board, int row, int col){ // note: tiles are not bombs at this point
	// if the tile is 0, open it and all unrevealed tiles around it, call function for each of those tiles, if it isn't 0, reveal the current tile only
	// if it's already revealed, return

	//base cases:
	if ((board->tiles[row][col].is_flagged == true) || (board->tiles[row][col].is_questioned == true)){
		board->tiles[row][col].is_revealed = false;
		return;
	}
	else if ((board->tiles[row][col].mines_near != 0) || (board->tiles[row][col].is_revealed == true)){ // if tile has at least one mine nearby...
		board->tiles[row][col].is_revealed = true; // reveal that tile only
		return;
	}

	else if (board->tiles[row][col].mines_near == 0){ // if tile has no nearby mines
		board->tiles[row][col].is_revealed = true;
		if ((row == 0) && (col == 0)){ // if tile is at top-left-- call for right, down, down-right
			RevealTiles(board, row + 1, col);
			RevealTiles(board, row + 1, col + 1);
			RevealTiles(board, row, col + 1);
		}
		else if ((row == 0) && (col == board->num_cols - 1)){ // if tile is at top-right-- call for left, down, left-down
			RevealTiles(board, row + 1, col);
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row + 1, col - 1);
		}
		else if ((row == board->num_rows - 1) && (col == 0)){ // bottom left 
			RevealTiles(board, row - 1, col);
			RevealTiles(board, row, col + 1);
			RevealTiles(board, row - 1, col + 1);
		}
		else if ((row == board->num_rows - 1) && (col == board->num_cols - 1)){ // bottom right
			RevealTiles(board, row - 1, col);
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row - 1, col - 1);
		}
		else if(col == 0){ // left tiles, not corner...
			RevealTiles(board, row - 1, col); // up
			RevealTiles(board, row + 1, col); // down
			RevealTiles(board, row, col + 1); // right
			RevealTiles(board, row - 1, col + 1); //up-right
			RevealTiles(board, row + 1, col + 1); //down-right
		}
		else if (col == board->num_cols - 1){ //  right tiles...
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row + 1, col);
			RevealTiles(board, row - 1, col);
			RevealTiles(board, row - 1, col - 1);
			RevealTiles(board, row + 1, col - 1);
		}
		else if (row == 0){ // top tiles
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row, col + 1);
			RevealTiles(board, row + 1, col);
			RevealTiles(board, row + 1, col + 1);
			RevealTiles(board, row + 1, col - 1);
		}
		else if (row == board->num_rows - 1){ // bottom tiles
			RevealTiles(board, row, col + 1);
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row - 1, col);
			RevealTiles(board, row - 1, col - 1);
			RevealTiles(board, row - 1, col + 1);
		}
		else{
			RevealTiles(board, row, col + 1);
			RevealTiles(board, row, col - 1);
			RevealTiles(board, row - 1, col);
			RevealTiles(board, row + 1, col);
			RevealTiles(board, row - 1, col - 1);
			RevealTiles(board, row - 1, col + 1);
			RevealTiles(board, row + 1, col + 1);
			RevealTiles(board, row + 1, col - 1);
		}
	}	
}
