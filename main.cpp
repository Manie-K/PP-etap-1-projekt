#include<stdio.h>
#include"conio2.h"
#include "configuration.h"
#include "utilities.h"

int main(){
	//TODO
	//PLANSZA POZA GRANICA NIE DZIALA // SCROLL

#ifndef __cplusplus
	Conio2_Init();
#endif
	int zn = 0, attr = 7, back = 0;

	// settitle sets the window title
	settitle(NAME_AND_ALBUM);

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	textbackground(BLACK);
	textcolor(7);

	Stone_t* stones = NULL;
	Players_t players;
	Point_t menuStartPoint = MENU_START_POINT;
	Point_t boardStartPoint = BOARD_START_POINT;
	int intersectionCount;
	Point_t gameBoardStartPoint;
	GameBoardDimensions_t gameBoardSize;
	Dimensions_t menuSize;
	Point_t gameBoardEndPoint;
	Point_t boardEndPoint;
	Point_t menuEndPoint;
	Point_t cursorPosition;
	Point_t boardCursor;

	intersectionCount = chooseGameSize();
	initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize);
	initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

	initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize, 
	{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);

	unsigned int stonesArraySize = intersectionCount * intersectionCount;
	stones = new Stone_t[stonesArraySize];
	resetStones(stones, intersectionCount);
	
	players = DEFAULT_PLAYER_AND_SCORES;

	//CHECKING THE INITIAL VALUES
	if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
	{		
		gotoxy(1, 1);
		textcolor(WHITE);
		textbackground(BLACK);
		cputs("MENU zachodzi na PLANSZE!\n");
		return -1;
	}
	if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint }))
	{
		gotoxy(1, 1);
		textcolor(WHITE);
		textbackground(BLACK);
		cputs("BLEDNE WARTOSCI STARTOWE!\n");
		return -1;
	}

	//INITIAL DRAW
	drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
	initializeMenu(MENU_START_POINT, menuSize, boardCursor);

	do {

		boardCursor = {((cursorPosition.x-gameBoardStartPoint.x) / (CELL_WIDTH + 1)) + 1, ((cursorPosition.y - gameBoardStartPoint.y) / 2) + 1};

		drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 0);
		updateMenu({ menuStartPoint.x + 1,menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, boardCursor, players);
		drawCursor(cursorPosition);

		zn = getch();

		if (zn == 0) {	
			zn = getch();		
			if (zn == 0x48)
			{
				if(cursorPosition.y > gameBoardStartPoint.y)
				cursorPosition.y -= 2;
			}
			else if (zn == 0x50)
			{
				if (cursorPosition.y < gameBoardEndPoint.y)
					cursorPosition.y += 2;
			}
			else if (zn == 0x4b)
			{
				if (cursorPosition.x > gameBoardStartPoint.x)
					cursorPosition.x -= CELL_WIDTH + 1;
			}
			else if (zn == 0x4d) 
			{
				if (cursorPosition.x < gameBoardEndPoint.x)
					cursorPosition.x += CELL_WIDTH + 1;
			}
		}
		else if (zn == 'i')
		{
			if (checkStone(boardCursor, stones, intersectionCount, players.current))
			{
				placeStone(boardCursor, stones, players.current, intersectionCount);

				Stone_t* neighbours = new Stone_t[NEIGHBOURS_COUNT];
				setNeighbours(neighbours, boardCursor, stones, intersectionCount);

				for (int k = 0; k < NEIGHBOURS_COUNT; k++) {
					if (!stoneHasLiberties(neighbours[k].position, stones, intersectionCount, neighbours[k].color))
						players.current.score += removeStone(neighbours[k].position, stones, intersectionCount);
				}
				changePlayers(players);
				delete[] neighbours;
			}
		}
		else if (zn == 'n')
		{
			clrscr();
			delete[] stones;

			intersectionCount = chooseGameSize();
			initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize);
			initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

			initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize,
				{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);

			unsigned int stonesArraySize = intersectionCount * intersectionCount;
			stones = new Stone_t[stonesArraySize];
			resetStones(stones, intersectionCount);

			players = DEFAULT_PLAYER_AND_SCORES;

			//CHECKING THE INITIAL VALUES
			if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
			{
				gotoxy(1, 1);
				textcolor(WHITE);
				textbackground(BLACK);
				cputs("MENU zachodzi na PLANSZE!\n");
				return -1;
			}
			if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint }))
			{
				gotoxy(1, 1);
				textcolor(WHITE);
				textbackground(BLACK);
				cputs("BLEDNE WARTOSCI STARTOWE!\n");
				return -1;
			}

			//INITIAL DRAW
			drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
			initializeMenu(MENU_START_POINT, menuSize, boardCursor);

		}
	} while (zn != 'q');

	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	_setcursortype(_NORMALCURSOR);	

	delete[] stones;

	return 0;
}
