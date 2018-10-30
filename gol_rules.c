#include "gol_rules.h"

int width;
int height;

//Set the width and height of the board
void setBoardSize(int width, int height)
{
	width=width;
	height=height;
}

// Print a whole board as lines
// NOT NEEDED AS WE WILL USE NCURSES
int printBoard(char * b)
{
	printf("\n");
	// For each row
	for (int j = 0; j < height; j++)
	{
		// Print all bytes in row
		for (int i = 0; i < width/8; i++){
			printf(BY2BI_PATTERN, BY2BI(b[j*width/8 + i]));
		}
		// Print newline after each row
		printf("\n");
	}
	return 0;
}

//-----------------------------------------------//
// Set the value of a cell (i, j) -> set it to 1 //
//-----------------------------------------------//

int setCell (char * b, int i, int j)
{
	if (i < 0 || width-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
	}
	else if (j < 0 || height-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
	}
	else
	{
		b[j*width/8 + i/8] |= ((char) 1 << (i%8));
	}
	return 0;
}

//-------------------------------------------------//
// Clear the value of a cell (i, j) -> set it to 0 //
//-------------------------------------------------//

int clearCell (char * b, int i, int j)
{
	if (i < 0 || width-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
	}
	else if (j < 0 || height-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
	}
	else
	{
		b[j*width/8 + i/8] &= ~((char) 1 << (i%8));
	}
	return 0;
}

//--------------------------------//
// Get the value of a cell (i, j) //
//--------------------------------//

int checkCell (char * b, int i, int j)
{
	if (i < 0 || width-1 < i)
	{
		// For debugging
		// perror("Array index i out of bounds.");
		return 0;
	}
	else if (j < 0 || height-1 < j)
	{
		// For debugging
		// perror("Array index j out of bounds."); 
		return 0;
	}
	else
	{
		return (int) (b[j*width/8+i/8] & ((char) 1 << (i%8))) != 0;
	}
	return 0;
}

//-------------------------------------------------------------------//
// Count the neighbors of a cell (i, j) which are alive (equal to 1) //
//-------------------------------------------------------------------//

int countNeighbors(char * b, int i, int j)
{
	int counter = 0;
	// loop through the row above, the row of the cell and the row below
	for (int dj = -1; dj < 2; dj++)
	{
		// if row not out of bounds
		if ((j + dj >= 0) && (j + dj < height))
		{
			// loop through the column before, the column of the cell and the next column
			for (int di = -1; di < 2; di++)
			{
				// if column not out of bounds
				if ((i + di >= 0) && (i + di < height))
				{
					// avoid central cell
					if ((di != 0) || (dj != 0))
					{
						counter += checkCell(b, i + di, j + dj);
					}
				}
			}
		}
	}

	return counter;
}

//------------------------------------------------------------------//
// Count the neighbors of each cell and apply the rules of the game //
//------------------------------------------------------------------//

int boardIteration(char * b, char * nb)
{
	int nalive = 0;
	// For each cell
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			// 1 - Count neighbors
			nalive = countNeighbors(b, i, j);
			// 2 - Apply rules
			// 2.1 - cell is alive
			if (checkCell(b, i, j))
			{
				// 2.1.1 - cell survives
				if ((nalive == 2) || (nalive == 3))
				{
					setCell(nb, i, j);
				}
				// 2.1.2 - cell dies
				else
				{
					clearCell(nb, i, j);
				}
			}
			// 2.2 - cell is dead and revives
			else if (nalive == 3)
			{
				setCell(nb, i, j);
			}
		}
	}
	return 0;
}
