mine_sweeper.out: mine_board.o mine_moves.o mine_input_val.o mine_win.o main.o
	gcc -g -Wall -Werror -o mine_sweeper.out mine_board.o mine_moves.o mine_input_val.o mine_win.o main.o

mine_board.o: mine_board.c
	gcc -g -Wall -Werror -c mine_board.c -I.

mine_moves.o: mine_moves.c 
	gcc -g -Wall -Werror -c mine_moves.c -I.

mine_input_val.o: mine_input_val.c 
	gcc -g -Wall -Werror -c mine_input_val.c -I.

mine_win.o: mine_win.c 
	gcc -g -Wall -Werror -c mine_win.c -I.

main.o: main.c 
	gcc -g -Wall -Werror -c main.c -I.

clean: 
	rm -fr *.o *.out

