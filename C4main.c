#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "C4.h"

int main() {
	//char buffer[2000] = {0};
	char input[10] = "?";
	char grid[42] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
					' ', ' ', ' ', ' ', ' ', ' '};
	char difficulty = '?';
	int botScore = 0;
	int playerScore = 0;
	char playType;
	//int colNum;
	int gameStatus;
	
	//Intro Start-----------------------------------------------------------------------
	
	system("cls");
	printf("Welcome to Connect Four. If you would like to view the tutorial, enter 't'.\n");
	printf("You can quit at anytime by entering 'q'. To continue, enter 'c'.\n");
	printf("Enter: ");
	scanf("%1s", input);
	while(!validStart(input) && !validQuit(input)) {
		system("cls");
		printf("That isn't a valid option. Would you like to continue (c) or view the tutorial (t)?\n");
		printf("Please re-enter: ");
		scanf("%1s", input);
	}
	if(*input == 't') {
		system("cls");
		printf("The aim of this game is to be the first to connect four in a row. This can be four diagonally, horizontally or vertically.\n");
		printf("You may select the column you wish to 'drop' your disc into and it will fall into the nearest available slot.\n");
		printf("Please enter 'c' to continue: ");
		scanf("%1s", input);
	}
	while((*input != 'c') && !validQuit(input)) {
		system("cls");
		printf("That isn't a valid option. Would you like to continue (c)?\n");
		printf("Please re-enter: ");
		scanf("%1s", input);
	}
	system("cls");
	if(!validQuit(input)) {
		printf("Enter 'p' if you would like to play against another player or \n");
		printf("enter 'b' if you would prefer to play against the bot.\n");
		printf("Enter: ");
		scanf("%s", input);
	}
	while((*input != 'p')  && (*input != 'b') && !validQuit(input)) {
		system("cls");
		printf("That isn't a valid option. Would you like to play against another player or the bot? (p/b)\n");
		printf("Please re-enter: ");
		scanf("%1s", input);
	}
	playType = *input;
	if(!validQuit(input) && (*input == 'b')) {
		system("cls");
		printf("Please enter a difficulty option: easy, medium, hard or nightmare (e, m, h, n)\n");
		printf("Enter: ");
		scanf("%1s", input);
		while(!validDifficulty(input) && !validQuit(input)) {
			system("cls");
			printf("That isn't a valid difficulty option. Select from easy (e), medium (m), hard (h) or nightmare (n)\n");
			printf("Please re-enter: ");
			scanf("%1s", input);
		}
		difficulty = *input;
	}
	else if(!validQuit(input)) {
		system("cls");
		printf("Would you like to flip a coin to decide who goes first? (y/n)\n");
		printf("Enter: ");
		scanf("%s", input);
		while((*input != 'y') && (*input == 'n') && !validQuit(input)) {
			system("cls");
			printf("That isn't a valid option. Would you like to flip a coin? (y/n)\n");
			printf("Enter: ");
			scanf("%s", input);
		}
		system("cls");
		if((*input == 'y') && !validQuit(input)) {
			for(int i = 0; i < 3; i++) {
				Sleep(1000);
				printf("*");
				printf("\n");
			}
			if(coinFlip() == 1) {
				printf("Heads!");
			}
			else {
				printf("Tails!");
			}
			printf("\n\n");
			printf("The first player's colour is yellow, the second player's colour is red.\n");
			for(int i = 3; i > 0; i--) {
				Sleep(1500);
				printf("%d\n", i);
			}
		}
	}
	
	//Game Loop Start-------------------------------------------------------------------
		
	while(!validQuit(input) && playType == 'b') {
		gameStatus = 0;
		system("cls");
		printGrid(grid);
		if(difficulty == 'n') {
			difficultySelector('h', grid, 'c');
			difficultySelector('h', grid, 'c');
			system("cls");
			printGrid(grid);
		}
		else {
			printf("Computer is thinking...\n");
		Sleep(1500);
		difficultySelector(difficulty, grid, 'c');
		system("cls");
		printGrid(grid);
		}
		
		if(endGame(grid, 'c') && !validQuit(input)) {
			gameStatus = 1;
			botScore++;
			printf("\n");
			printf("\n");
			if(difficulty == 'e') {
				printf("You somehow lost on easy mode.");
			}
			else if(difficulty == 'm') {
				printf("Looks like you lost on medium difficulty.");
			}
			else if(difficulty == 'h'){
				printf("Looks like you lost on hard mode.");
			}
			else {
				printf("Lost on nightmare mode?! Git Gud.");
			}
		}
		
		if(!gameStatus) {
			printf("\n");
			printf("Please enter the number of the column in which you wish to drop your disc.\n");
			printf("Enter: ");
			scanf("%1s", input);
			while(!validColNum(input) && !validQuit(input)) {
				system("cls");
				printGrid(grid);
				printf("\n");
				printf("That isn't a valid column number.\n");
				printf("Please re-enter: ");
				scanf("%1s", input);
				if(isColumnFull(grid, (*input - '0' - 1))) {
					system("cls");
					printGrid(grid);
					printf("\n");
					printf("That column is full!\n");
					printf("Please re-enter another column number: ");
					scanf("%1s", input);
				}
			}
			placeDisc(grid, (*input - '0' - 1), 'p');
			system("cls");
			printGrid(grid);
		}
		
		if(endGame(grid, 'p') && !validQuit(input)) {
			gameStatus = 1;
			playerScore++;
			printf("\n");
			printf("\n");
			if(difficulty == 'e') {
				printf("You won on easy mode.");
			}
			else if(difficulty == 'm') {
				printf("Looks like you won on medium difficulty.");
			}
			else if(difficulty == 'h') {
				printf("Looks like you won on hard mode!");
			}
			else {
				printf("You somehow won, you absolute cheat.");
			}
		}
		
		if(isGridFull(grid)) {
			gameStatus = 1;
			printf("\n\n");
			printf("Looks like a stalemate.");
		}
		
		if(!validQuit(input) && gameStatus) {
			printf("\n");
			printf("Would you like to play again? (y/n)\n");
			printf("Enter: ");
			scanf("%1s", input);
			while(!validSelection(input) && !validQuit(input)) {
				system("cls");
				printGrid(grid);
				printf("\n");
				printf("That isn't a valid option. Would you like to play another round? (y/n)\n");
				printf("Please re-enter: ");
				scanf("%1s", input);
			}
		}
		
		if(*input == 'y') {
			clear(grid);
		}
		else if(*input == 'n') {
			printf("\n\n");
			printf("Bot score: %d\n", botScore);
			printf("Player Score: %d\n", playerScore);
			printf("\n");
			if(botScore > playerScore) {
				printf("Looks like you lost.");
				break;
			}
			else if(playerScore > botScore) {
				printf("Looks like you won!");
				break;
			}
			else {
				printf("Draw!");
				break;
			}
		}
		else if(validQuit(input)){
			break;
		}
	}
	
	//PvP Loop----------------------------------------------------
	
	while(!validQuit(input) && playType == 'p') {
		gameStatus = 0;
		system("cls");
		printGrid(grid);
		
		if(!gameStatus && !validQuit(input)) {
			printf("\n");
			printf("Yellow player's turn!\n");
			printf("Please enter the number of the column in which you wish to drop your disc.\n");
			printf("Enter: ");
			scanf("%1s", input);
			while(!validColNum(input) && !validQuit(input)) {
				system("cls");
				printGrid(grid);
				printf("\n");
				printf("That isn't a valid column number.\n");
				printf("Please re-enter: ");
				scanf("%1s", input);
				if(isColumnFull(grid, (*input - '0' - 1))) {
					system("cls");
					printGrid(grid);
					printf("\n");
					printf("That column is full!\n");
					printf("Please re-enter another column number: ");
					scanf("%1s", input);
				}
			}
			placeDisc(grid, (*input - '0' - 1), 'p');
			system("cls");
			printGrid(grid);
		}
		if(endGame(grid, 'p') && !validQuit(input)) {
			gameStatus = 1;
			playerScore++;
			printf("\n");
			printf("\n");
			printf("Yellow has won!\n");
		}
		
		if(!gameStatus && !validQuit(input)) {
			printf("\n");
			printf("Red player's turn!\n");
			printf("Please enter the number of the column in which you wish to drop your disc.\n");
			printf("Enter: ");
			scanf("%1s", input);
			while(!validColNum(input) && !validQuit(input)) {
				system("cls");
				printGrid(grid);
				printf("\n");
				printf("That isn't a valid column number.\n");
				printf("Please re-enter: ");
				scanf("%1s", input);
				if(isColumnFull(grid, (*input - '0' - 1))) {
					system("cls");
					printGrid(grid);
					printf("\n");
					printf("That column is full!\n");
					printf("Please re-enter another column number: ");
					scanf("%1s", input);
				}
			}
			placeDisc(grid, (*input - '0' - 1), 'c');
			system("cls");
			printGrid(grid);
		}
		if(endGame(grid, 'c') && !validQuit(input)) {
			gameStatus = 1;
			botScore++;
			printf("\n");
			printf("\n");
			printf("Red has won!\n");
		}
		
		if(isGridFull(grid)) {
			gameStatus = 1;
			printf("\n\n");
			printf("Looks like a stalemate.");
		}
		
		if(!validQuit(input) && gameStatus) {
			printf("\n");
			printf("Would you like to play again? (y/n)\n");
			printf("Enter: ");
			scanf("%1s", input);
			while(!validSelection(input) && !validQuit(input)) {
				system("cls");
				printGrid(grid);
				printf("\n");
				printf("That isn't a valid option. Would you like to play another round? (y/n)\n");
				printf("Please re-enter: ");
				scanf("%1s", input);
			}
		}
		if(*input == 'y') {
			clear(grid);
		}
		else if(*input == 'n') {
			printf("\n\n");
			printf("Red score: %d\n", botScore);
			printf("Yellow Score: %d\n", playerScore);
			printf("\n");
			if(botScore > playerScore) {
				printf("Looks like red won!");
				break;
			}
			else if(playerScore > botScore) {
				printf("Looks like yellow won!");
				break;
			}
			else {
				printf("Draw!");
				break;
			}
		}
		else if(validQuit(input)){
			break;
		}
	}
	return 0;
}