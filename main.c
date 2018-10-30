
#include "gol_rules.h"
#include <stdlib.h> // for calloc (allocate and set to 0)
#include <unistd.h> // for usleep (microseconds)
#include <string.h> // for memset

// Pointers to the memory where the board info is located
char * board;
char * newBoard;
char * tempPointer;

// Board size
// (width must be divisible by 8 as we use char->1 byte->8 bits)
int width = 56;
int height = 56;

// Sample program
int main()
{
	// 1 - Set board size
	setBoardSize(width, height);

	// 1 - Allocate memory and set to 0
	board = (char *) calloc(height, width/8);
	newBoard = (char *) calloc(height, width/8);

	// 2 - Initialize figure

	// R-pentomino
	setCell(board, 51, 51);
	setCell(board, 52, 51);
	setCell(board, 50, 52);
	setCell(board, 51, 52);
	setCell(board, 51, 53);//*/

	// Diehard
	/*setCell(board, 48,50);
	setCell(board, 49,50);
	setCell(board, 54,49);
	setCell(board, 49,51);
	setCell(board, 53,51);
	setCell(board, 54,51);
	setCell(board, 55,51);//*/

	// Acorn
	/*setCell(board, 48,49);
	setCell(board, 50,50);
	setCell(board, 47,51);
	setCell(board, 48,51);
	setCell(board, 51,51);
	setCell(board, 52,51);
	setCell(board, 53,51);//*/
	
	// 3 - Print first board
	printBoard(board);

	// 4 - Perform iterations
	for (int i = 0; i < 5250; i++)
	{
		// 4.1 - sleep for 0.125 seconds
		usleep(125000);
		// 4.2 - update the board and store it in newBoard
		boardIteration(board, newBoard);
		// 4.3 - switch the contents of board and newBoard
		tempPointer = board;
		board = newBoard;
		newBoard = tempPointer;
		// 4.4 - set newBoard to 0
		memset(newBoard, 0, height*width/8);
		// 4.5 - print the updated board and the iteration #
		printBoard(board);
		printf("\nIteration: %d\n", i);
	}
	
	return 0;
}
