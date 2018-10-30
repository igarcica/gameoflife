#include <stdio.h>
#include <stdlib.h> // for calloc (allocate and set to 0)
#include <unistd.h> // for usleep (microseconds)
#include <string.h> // for memset

// To print a byte as 0/1 (-/o) from left to right
// NOT NEEDED AS WE WILL USE NCURSRS
#define BY2BI_PATTERN "%c %c %c %c %c %c %c %c "
#define BY2BI(byte)  \
  (byte & 0x01 ? 'o' : '-'), \
  (byte & 0x02 ? 'o' : '-'), \
  (byte & 0x04 ? 'o' : '-'), \
  (byte & 0x08 ? 'o' : '-'), \
  (byte & 0x10 ? 'o' : '-'), \
  (byte & 0x20 ? 'o' : '-'), \
  (byte & 0x40 ? 'o' : '-'), \
  (byte & 0x80 ? 'o' : '-')

// Pointers to the memory where the board info is located
char * board;
char * newBoard;
char * tempPointer;

// Function definitions
int printBoard(char *, int, int);

int setCell(char *, int, int, int, int);

int clearCell(char *, int, int, int, int);

int checkCell(char *, int, int, int, int);

int countNeighbors(char *, int, int, int, int);

int boardIteration(char *, char *, int, int);

int checkBoardExpansion(char *, char *, int, int);

int BoardExpansion(char *, char *, int, int);

// Print a whole board as lines
// NOT NEEDED AS WE WILL USE NCURSES
int printBoard(char * b, int w, int h)
{
	printf("\n");
	// For each row
	for (int j = 0; j < h; j++)
	{
		// Print all bytes in row
		for (int i = 0; i < w/8; i++){
			printf(BY2BI_PATTERN, BY2BI(b[j*w/8 + i]));
		}
		// Print newline after each row
		printf("\n");
	}
	return 0;
}

// Set the value of a cell (i, j) -> set it to 1
int setCell (char * b, int i, int j, int w, int h)
{
	if (i < 0 || w-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
	}
	else if (j < 0 || h-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
	}
	else
	{
		b[j*w/8 + i/8] |= ((char) 1 << (i%8));
	}
	return 0;
}

// Clear the value of a cell (i, j) -> set it to 0
int clearCell (char * b, int i, int j, int w, int h)
{
	if (i < 0 || w-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
	}
	else if (j < 0 || h-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
	}
	else
	{
		b[j*w/8 + i/8] &= ~((char) 1 << (i%8));
	}
	return 0;
}

// Get the value of a cell (i, j)
int checkCell (char * b, int i, int j, int w, int h)
{	
	if (i < 0 || w-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
		return 0;
	}
	else if (j < 0 || h-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
		return 0;
	}
	else
	{
		return (int) (b[j*w/8+i/8] & ((char) 1 << (i%8))) != 0;
	}
	return 0;
}

// Count the neighbors of a cell (i, j) which are alive (equal to 1)
int countNeighbors(char * b, int i, int j, int w, int h)
{
	int counter = 0;
	// loop through the row above, the row of the cell and the row below
	for (int dj = -1; dj < 2; dj++)
	{
		// if row not out of bounds
		if ((j + dj >= 0) && (j + dj < h))
		{
			// loop through the column before, the column of the cell and the next column
			for (int di = -1; di < 2; di++)
			{
				// if column not out of bounds
				if ((i + di >= 0) && (i + di < w))
				{
					// avoid central cell
					if ((di != 0) || (dj != 0))
					{
						counter += checkCell(b, i + di, j + dj, w, h);
					}
				}
			}
		}
	}

	return counter;
}

// Count the neighbors of each cell and apply the rules of the game
int boardIteration(char * b, char * nb, int w, int h)
{
	int nalive = 0;
	// For each cell
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			// 1 - Count neighbors
			nalive = countNeighbors(b, i, j, w, h);
			// 2 - Apply rules
			// 2.1 - cell is alive
			if (checkCell(b, i, j, w, h))
			{
				// 2.1.1 - cell survives
				if ((nalive == 2) || (nalive == 3))
				{
					setCell(nb, i, j, w, h);
				}
				// 2.1.2 - cell dies
				else
				{
					clearCell(nb, i, j, w, h);
				}
			}
			// 2.2 - cell is dead and revives
			else if (nalive == 3)
			{
				setCell(nb, i, j, w, h);
			}
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////// DYNAMIC BOARD ////////////////////////////////////////////////////////////////
int checkBoardExpansion(char * b, char * nb, int w, int h)
{
	// Check if there is any live cell in the board borders and allocate more memory if necessary
	// UP i = [0, width], j = 0
	for (int i = 0; i < w; i++)
	{
		if (checkCell(b, i, 0, w, h))
		{
			return 1;
		}

	}
	// DOWN i = [0, width], j = height
	for (int i = 0; i < w; i++)
	{	
		if (checkCell(b, i, h-1, w, h))
		{
			return 1;
		}
	}
	// LEFT i = 0, j = [0,height]
	for (int j = 0; j < h; j++)
	{
		if (checkCell(b, 0, j, w, h))
		{
			return 1;
		}	
	}
	// RIGHT i = width, j = [0, height]
	for (int j = 0; j < h; j++)
	{
		if (checkCell(b, w-1, j, w, h))
		{
			return 1;
		}
	}

	return 0;
}

int BoardExpansion(char * b, char * nb, int w, int h)
{

	for (int j = 8; j < h-7; j++) // Leave blank first and last 8 rows
	{
		for (int i = 8; i < w-8; i++) // Leave blank first and last columns 
		{
			if (checkCell(b, i-8, j-8, w-16, h-16))
			{
				setCell(nb, i, j, w, h);
			}
		}
	}	

	return 0;			
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sample program
int main()
{
	// Board size
	// (width must be divisible by 8 as we use char->1 byte->8 bits)
	int width = 8;
	int height = 8;

	// 1 - Allocate memory and set to 0
	board = (char *) calloc(height, width/8);
	newBoard = (char *) calloc(height, width/8);

	setCell(board, 2, 1, width, height);
	setCell(board, 3, 1, width, height);
	setCell(board, 1, 2, width, height);
	setCell(board, 2, 2, width, height);
	setCell(board, 2, 3, width, height);//*/

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
	printBoard(board, width, height);

	// 4 - Perform iterations
	for (int i = 0; i < 5250; i++)
	{
		// 4.1 - sleep for 0.125 seconds
		usleep(125000);
		// 4.2 - update the board and store it in newBoard
		boardIteration(board, newBoard, width, height);

		// 4.3 - switch the contents of board and newBoard
		tempPointer = board;
		board = newBoard;
		newBoard = tempPointer;
		memset(newBoard, 0, height*width/8);

		int grow = checkBoardExpansion(board, newBoard, width, height);
		if (grow)
		{
			height += 16;
			width += 16;
			free(newBoard);
			newBoard = (char *) calloc(height, width/8);
			BoardExpansion(board, newBoard, width, height);
			tempPointer = board;
			board = newBoard;
			newBoard = tempPointer;
			free(newBoard);
			newBoard = (char *) calloc(height, width/8);
		}
		
		
		// 4.5 - print the updated board and the iteration #
		// 4.1 - sleep for 0.125 seconds
		usleep(125000);
		printBoard(board, width, height);
		printf("\nIteration: %d\n", i);
	}
	
	return 0;
}
