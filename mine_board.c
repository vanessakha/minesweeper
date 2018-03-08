//mine_board.c
#include "mine_board.h"
#include "mine_structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// void Seed(int argc, int seed);
void ReadArgs(int argc, char *argv[], int *num_rows, int *num_cols, int *num_mines, int *seed){ 
	// GOOD
	if (argc <= 4){
		printf("Not enough arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0);
	}
	else if (argc > 5){
		printf("Too many arguments. Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0);
	}
	*num_rows = atoi(argv[1]);
	*num_cols = atoi(argv[2]);
	*num_mines = atoi(argv[3]);
	if(argc > 4){
		*seed = atoi(argv[4]);
	}
}

// BOARD ===============================
void CreateBoard(Board *board, int argc, int num_rows, int num_cols, int num_mines, int seed){
	int i;
	//assign values to new board struct
	board->num_rows = num_rows;
	board->num_cols = num_cols;
	board->num_mines = num_mines;

	// allocate space to tiles array 
	board->tiles = (Tile **) malloc(sizeof(Tile *) * board->num_rows);
	for (i = 0; i < board->num_rows; i++){
		board->tiles[i] = (Tile*) malloc(sizeof(Tile) * board->num_cols);
	}

	// seed random number generator
	Seed(argc, seed);

	// put mines onto board
	PlaceMines(board); // board is a Board * right now

	// label each tile as concealed, not questioned, not flagged, mine/not mine
	LabelTiles(board);
}

void Seed(int argc, int seed){
	if (argc > 4){
		srand(seed);
	}
	else{
		srand(time(0));
	}
}


void PlaceMines(Board *board){
	// RAND NUMS OFF
	int i, row, col, board_row;
	for (i = 0; i < board->num_mines; i++){ // make num_mine mines
		do{
			board_row = rand() % board->num_rows; 
			row = board->num_rows - board_row - 1;
			col = rand() % board->num_cols;
		} while(board->tiles[row][col].is_mine == true); // keep getting random cds until spot isn't a mine
		// printf("Placing mine at %d, %d\n", board_row, col);
		board->tiles[row][col].is_mine = true; // if it isn't a mine, make it into a mine
	}
}

//!
void LabelTiles(Board *board){
	int i, j;
	for(i = 0; i < board->num_rows; i++){
		for(j = 0; j < board->num_cols; j++){
			board->tiles[i][j].is_revealed = false;
			board->tiles[i][j].is_flagged = false;
			board->tiles[i][j].is_questioned = false;
			board->tiles[i][j].mines_near = 0;
		}
	}
	LabelMinesNearby(board);
}


void LabelMinesNearby(Board *board){
	int i, j;

	for(i = 0; i < board->num_rows; i++){
		for(j = 0; j < board->num_cols; j++){

			// label tile with # of mines near corner tiles
			if ((i == 0) && (j == 0)){
				TopLeftMines(board, i, j);
			}
			else if ((i == board->num_rows - 1) && (j == 0)){
				BottomLeftMines(board, i, j);
			}
			else if ((i == 0) && (j == board->num_cols - 1)){
				TopRightMines(board, i, j);
			}
			else if ((i == board->num_rows - 1) && (j == board->num_cols - 1)){
				BottomRightMines(board, i, j);
			}

			// label # mines near side tiles
			else if (i == 0){
				TopMines(board, i, j);
			}
			else if(i == board->num_rows - 1){
				BottomMines(board, i, j);
			}
			else if(j == 0){
				LeftMines(board, i, j);
			}
			else if(j == board->num_cols - 1){
				RightMines(board, i, j);
			}

			// label # mines near all other tiles 
			else{
				TileRight(board, i, j);
				TileLeft(board, i, j);
				TileAbove(board, i, j);
				TileBelow(board, i, j);
				TileUpRight(board, i, j);
				TileDownRight(board, i, j);
				TileUpLeft(board, i, j);
				TileDownLeft(board, i, j);
			}
		}
	}
}


void TopLeftMines(Board *board, int i, int j){
	TileRight(board, i, j);
	TileBelow(board, i, j);
	TileDownRight(board, i, j);
}

void BottomLeftMines(Board *board, int i, int j){
	TileAbove(board, i, j);
	TileRight(board, i, j);
	TileUpRight(board, i, j);

}

void TopRightMines(Board *board, int i, int j){
	if (board->num_cols > 1){
		TileLeft(board, i, j);
	}
	if (board->num_rows > 1){
		TileBelow(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileDownLeft(board, i, j);
	}
}


void BottomRightMines(Board *board, int i, int j){
	if (board->num_cols > 1){
		TileLeft(board, i, j);
	}
	if (board->num_rows > 1){
		TileAbove(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileUpLeft(board, i, j);
	}
}


void TopMines(Board *board, int i, int j){
	if(board->num_cols > 1){
		TileRight(board, i, j);
		TileLeft(board, i, j);
	}
	if (board->num_rows > 1){
		TileBelow(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileDownRight(board, i, j);
		TileDownLeft(board, i, j);
	}
}


void BottomMines(Board *board, int i, int j){
	if (board->num_cols > 1){
		TileRight(board, i, j);
	}
	if (board->num_cols > 1){
		TileLeft(board, i, j);
	}
	if (board->num_rows > 1){
		TileAbove(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileUpLeft(board, i, j);
		TileUpRight(board, i, j);
	}
}


void LeftMines(Board *board, int i, int j){
	if (board->num_cols > 1){
		TileRight(board, i, j);
	}
	if (board->num_rows > 1){
		TileAbove(board, i, j);
		TileBelow(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileUpRight(board, i, j);
		TileDownRight(board, i, j);
	}
}


void RightMines(Board *board, int i, int j){
	if (board->num_rows > 1){
		TileAbove(board, i, j);
		TileBelow(board, i, j);
	}
	if (board->num_cols > 1){
		TileLeft(board, i, j);
	}
	if ((board->num_rows > 1) && (board->num_cols > 1)){
		TileUpLeft(board, i, j);
		TileDownLeft(board, i, j);
	}

}

// TILES -- 
void TileAbove(Board *board, int i, int j){
	if (board->tiles[i - 1][j].is_mine == true){ // tile above
		(board->tiles[i][j].mines_near)++;
	}
}

void TileBelow(Board *board, int i, int j){
	if (board->tiles[i + 1][j].is_mine == true){ // tile below
		(board->tiles[i][j].mines_near)++;
	}
}

void TileRight(Board *board, int i, int j){
	if (board->tiles[i][j + 1].is_mine == true){ // right
		(board->tiles[i][j].mines_near)++;
	}
}


void TileLeft(Board *board, int i, int j){
	if (board->tiles[i][j - 1].is_mine == true){ // tile to left
		(board->tiles[i][j].mines_near)++;
	}
}

void TileUpRight(Board *board, int i, int j){
	if (board->tiles[i - 1][j + 1].is_mine == true){ // tile diagonal up-right
		(board->tiles[i][j].mines_near)++;
	}
}

void TileDownRight(Board *board, int i, int j){
	if (board->tiles[i + 1][j + 1].is_mine == true){ // tile diagonal down-right
		(board->tiles[i][j].mines_near)++;
	}
}

void TileUpLeft(Board *board, int i, int j){
	if (board->tiles[i][j - 1].is_mine == true){ // tile to left
		(board->tiles[i][j].mines_near)++;
	}
}

void TileDownLeft(Board *board, int i, int j){
	if (board->tiles[i + 1][j - 1].is_mine == true){ // tile diagonal down-left
		(board->tiles[i][j].mines_near)++;
	}
}

void PrintBoard(Board board){
	int leftMargin = 1;
	int i, j, k;

	for(i = 0; i < board.num_rows; i++){
		printf("%d", board.num_rows - leftMargin); // print left margins 
		for(j = 0; j < board.num_cols; j++){

			if(board.tiles[i][j].is_revealed == false){ // if tile is concealed...
				if(board.tiles[i][j].is_flagged == true){ // and flagged
					printf(" !");
				}
				else if (board.tiles[i][j].is_questioned == true){ // and questioned
					printf(" ?");
				}
				else{ 
					printf(" #");
				}
			}

			else if(board.tiles[i][j].is_revealed == true){ // if tile is revealed...
				if (board.tiles[i][j].is_mine){
					printf(" *");
				}
				else{
					printf(" %d", board.tiles[i][j].mines_near); // print # nearby mines
				}
			}
		}

		leftMargin++;
		printf("\n");
	}
	printf(" ");
	for(k = 0; k < board.num_cols; k++){ // print bottom margin
		printf(" %d", k);
	}
	printf("\n");
}


void DestroyBoard(Board *board){
	int i;
	for (i = 0; i < board->num_rows; i++){
		free(board->tiles[i]);
	}
	free(board->tiles);
	board->tiles = NULL;
}
