// Check that the required libraries have been defined
#ifndef STD
#define STD

#include <stdio.h>

#endif

// Check that the Byte2Bit conversion has been defined
#ifndef BY2BI_PATTERN
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

#endif

// Check that this module has not been loaded
#ifndef RULE_FCNS
#define RULE_FCNS

// Function definitions
void setBoardSize(int, int);

int printBoard(char *);

int setCell(char *, int, int);

int clearCell(char *, int, int);

int checkCell(char *, int, int);

int countNeighbors(char *, int, int);

int boardIteration(char *, char *);

#endif
