//mine_input_val.c	

#include "mine_structs.h"
#include "mine_input_val.h"
#include "mine_board.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

bool isValidFormatting(int num_args_read, int num_args_needed){
	bool isValidFormat = num_args_read == num_args_needed;
	char last_char;
	do{
		scanf("%c", &last_char);
		if (!isspace(last_char)){
			isValidFormat = false;
		}
	}while (last_char != '\n');
	return isValidFormat;
}

bool isValidInput(Board board, int row, int col){
	// could also check if row and column are integers

	if (!(row >= 0) || !(row < board.num_rows) || !(col >= 0) || !(col < board.num_cols)){
		return false; // if rows and columns are not within the right integers, input is invalid
	}

	else if (board.tiles[row][col].is_revealed == true){ // if tile has been revealed, input is invalid
		return false;
	}

	else{ // otherwise, input is valid
		return true;
	}
}

bool isValidAction(int action, int max_action){
	if (action < 0){
		return false;
	}
	else if (action > max_action){
		return false;
	}
	else{
		return true;
	}
}