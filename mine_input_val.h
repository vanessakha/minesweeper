//mine_input_val.h

// Input Val:

#ifndef MINE_INPUT_VAL_H
	#define MINE_INPUT_VAL_H

	#include <stdbool.h>
	#include "mine_structs.h"

	bool isValidFormatting(int num_args_read, int num_args_needed);
	bool isValidInput(Board board, int row, int col);
	bool isValidAction(int action, int max_action);

#endif