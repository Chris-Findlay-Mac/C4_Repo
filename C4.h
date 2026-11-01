#include <stdio.h>

int validStart(char* input);

int validDifficulty(char* input);

int validQuit(char* input);

int validColNum(char* input);

int validSelection(char* input);

int coinFlip();

void clear(char* grid);

int isColumnFull(char* grid, int colNum);

int isGridFull(char* grid);

void placeDisc(char* grid, int colNum, char discType);

void forceDisc(char* grid, int colNum, char discType);

int endGame(char* grid, char discType); //check after computer and player turns, fix later

void computerInsertionSearch(char* grid);

void difficultySelector(char difficulty, char* grid, char discType);

void printGrid(char* grid);
