#include <stdio.h>
#include <stdlib.h>
#include "C4.h"

#define SIZE 42
#define COLUMNS 7

int validStart(char* input) {
	if (*input == 't' || *input == 'q' || *input == 'c') {
		return 1;
	}
	return 0; 
}

int validDifficulty(char* input) {
	if (*input == 'e' || *input == 'm' || *input == 'h' || *input == 'n' || *input == 'q') {
		return 1;
	}
	return 0; 
}

int validQuit(char* input) {
	if (*input == 'q') {
		return 1;
	}
	return 0;
}

int validColNum(char* input) {
	if ((*input > '0') && (*input <= '7')) {
		return 1;
	}
	return 0;
}

int validSelection(char* input) {
	if (*input == 'y' || *input == 'n') {
		return 1;
	}
	return 0;
}

int coinFlip() {
	return (rand() % 2);
}

//Grid Methods-------------------------------------------------------

void clear(char* grid) {
	for(int i = 0; i < SIZE; i++) {
		grid[i] = ' ';
	}
}

int isColumnFull(char* grid, int colNum) {
	if(grid[colNum] != ' ') {
		return 1;
	}
	return 0;
}

int isGridFull(char* grid) {
	int count = 0;
	for(int i = 0; i < SIZE; i++) {
		if(grid[i] != ' ') {
			count++;
		}
	}
	if(count == SIZE) {
		return 1;
	}
	return 0;
}

void placeDisc(char* grid, int colNum, char discType) {
    for(int i = SIZE - 7 + colNum; i >= colNum; i -= 7) {
        if(grid[i] == ' ') {
            grid[i] = discType;
            return;
        }
    }
}

void forceDisc(char* grid, int colNum, char discType) {
	int i = 0;
	while((colNum + i*7 < SIZE) && (grid[colNum + i*7]  == ' ')) {
		i++;
	}
	grid[colNum + i*7] = discType;
}

int endGame(char* grid, char discType) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 7; j++) {
			if((grid[j + (i*7)] == discType) && (grid[j + (i*7) + 7] == discType) && (grid[j + (i*7) + 14] == discType) && (grid[j + (i*7) + 21] == discType)) { //columns
				return 1;
			}
		}
		for(int j = (3 + i*7); j < (7 + i*7); j++) { //diagonals right to left
			if((grid[j] == discType) && (grid[j + 6] == discType) && (grid[j + 12] == discType) && (grid[j + 18] == discType)) {
				return 1;
			}
		}
		for(int j = (0 + i*7); j < (5 + i*7); j++) { //diagonals left to right
			if((grid[j] == discType) && (grid[j + 8] == discType) && (grid[j + 16] == discType) && (grid[j + 24] == discType)) {
				return 1;
			}
		}
	}
	for(int i = 0; i < 6; i++) { //rows
		if((grid[i*7] == discType) && (grid[i*7 + 1] == discType) && (grid[i*7 + 2] == discType) && (grid[i*7 + 3] == discType)) {
			return 1;
		}
		if((grid[i*7 + 1] == discType) && (grid[i*7 + 2] == discType) && (grid[i*7 + 3] == discType) && (grid[i*7 + 4] == discType)) {
			return 1;
		}
		if((grid[i*7 + 2] == discType) && (grid[i*7 + 3] == discType) && (grid[i*7 + 4] == discType) && (grid[i*7 + 5] == discType)) {
			return 1;
		}
		if((grid[i*7 + 3] == discType) && (grid[i*7 + 4] == discType) && (grid[i*7 + 5] == discType) && (grid[i*7 + 6] == discType)) {
			return 1;
		}
	}
	return 0;
}

void computerInsertionSearch(char* grid) {
	for(int i = 0; i < 7; i++) {
		if(!isColumnFull(grid, i)) {
			placeDisc(grid, i, 'c');
			if(endGame(grid, 'c')) {
				//colNum = i;
				return;
			}
			forceDisc(grid, i, ' ');
			placeDisc(grid, i, 'p');
			if(endGame(grid, 'p')) {
				forceDisc(grid, i, 'c');
				//colNum = i;
				return;
			}
			forceDisc(grid, i, ' ');
		}
	}
	for(int i = 0; i < 7; i++) {
		if(!isColumnFull(grid, i)) {
			placeDisc(grid, i, 'c');
			for(int j = 0; j < 7; j++) { //if computer can win next turn => place
				if(!isColumnFull(grid, j)) {
					placeDisc(grid, j, 'c');
					if(endGame(grid, 'c')) {
						forceDisc(grid, j, ' ');
						//colNum = i;
						return;
					}
					forceDisc(grid, j, ' ');
				}
			}
			forceDisc(grid, i, 'p');
			for(int j = 0; j < 7; j++) { //if player can win NEXT next turn => intercept
				if(!isColumnFull(grid, j)) {
					placeDisc(grid, j, 'p');
					for(int k = 0; k < 7; k++) {
						if(!isColumnFull(grid, k)) {
							placeDisc(grid, k, 'p');
							if(endGame(grid, 'p')) {
								forceDisc(grid, k, ' ');
								forceDisc(grid, j, ' ');
								forceDisc(grid, i, 'c');
								//colNum = i;
								return;
							}
							forceDisc(grid, k, ' ');
						}
					}
					forceDisc(grid, j, ' ');
				}
			}
			forceDisc(grid, i, 'c');
			for(int j = 0; j < 7; j++) { //if computer can win NEXT next turn => place
				if(!isColumnFull(grid, j)) {
					placeDisc(grid, j, 'c');
					for(int k = 0; k < 7; k++) {
						if(!isColumnFull(grid, k)) {
							placeDisc(grid, k, 'c');
							if(endGame(grid, 'c')) {
								forceDisc(grid, k, ' ');
								forceDisc(grid, j, ' ');
								//colNum = i;
								return;
							}
							forceDisc(grid, k, ' ');
						}
					}
					forceDisc(grid, j, ' ');
				}
			}
			forceDisc(grid, i, 'p');
			for(int j = 0; j < 7; j++) { //if player can win next turn => intercept
				if(!isColumnFull(grid, j)) {
					placeDisc(grid, j, 'p');
					if(endGame(grid, 'p')) {
						forceDisc(grid, j, ' ');
						forceDisc(grid, i, 'c');
						//colNum = i;
						return;
					}
					forceDisc(grid, j, ' ');
				}
			}
			forceDisc(grid, i, ' ');
		}
	}
	difficultySelector('e', grid, 'c');
}

void difficultySelector(char difficulty, char* grid, char discType) {
	if(difficulty == 'e') {
		int tempColNum = rand() % 7;
		if(isColumnFull(grid, tempColNum)) {
			difficultySelector('e', grid, discType);
		}
		placeDisc(grid, tempColNum, discType);
		//colNum = tempColNum;
		return;
	}
	else if(difficulty == 'm') {
		int mid = rand() % 3;
		if(mid == 2) {
			difficultySelector('e', grid, discType);
		}
		else {
			computerInsertionSearch(grid);
		}
	}
	else if(difficulty == 'h') {
		int hard = rand() % 10;
		if(hard == 9) {
			difficultySelector('e', grid, discType);
		}
		else {
			computerInsertionSearch(grid);
		}
	}
}

void printGrid(char* grid) {
	//system("cls");
	
	printf("\n");
	printf("		---------------------------------------------------------\n");
	for(int i = 0; i < 6; i++) {
		for(int k = 0; k < 3; k++) {
			printf("		");
			for(int j = 0; j < 7; j++) {
				if(grid[j + (i*7)] == 'c') {
					printf("|\033[41m       \033[0m");
				}
				else if(grid[j + (i*7)] == 'p') {
					printf("|\033[43m       \033[0m");
				}
				else {
					printf("|       ");
				}
			}
			printf("|\n");
		}
		printf("		|-------|-------|-------|-------|-------|-------|-------|\n");
	}
	printf("\n");
	printf("		|^^^1^^^|^^^2^^^|^^^3^^^|^^^4^^^|^^^5^^^|^^^6^^^|^^^7^^^|\n");
}
