#include<stdio.h>
#include"conio2.h"
#include "configuration.h"
#include "utilities.h"

int main() {
	//TODO

	//Pozycja kursora
	//Kursos nie ucieka za plansze
	//£adniejszy kursor
	//PLANSZA POZA GRANICA NIE DZIALA // SCROLL


	//Sets the game board size (intersection count)
	int intersectionCount;
	intersectionCount = chooseGameSize();


	//Whole board and game board starting positions
	Point_t boardStartPoint = BOARD_START_POINT;
	Point_t gameBoardStartPoint;
	setGameBoardStartPoint(gameBoardStartPoint, boardStartPoint);

	//Size of the game board !!!!WHOLE BOARD size inside
	GameBoardDimensions_t gameBoardSize;
	setBoardDimensions(gameBoardSize, intersectionCount);

	Point_t gameBoardEndPoint = { gameBoardStartPoint.x + gameBoardSize.x - 1, gameBoardStartPoint.y + gameBoardSize.y - 1 };

	//Board end point
	Point_t boardEndPoint = { boardStartPoint.x + gameBoardSize.wholeBoardSize.x - 1, boardStartPoint.y + gameBoardSize.wholeBoardSize.y - 1 };

	//Menu starting position
	Point_t menuStartPoint = MENU_START_POINT;
	//Menu size
	Dimensions_t menuSize;
	setMenuSize(menuSize);

	//Menu ending
	Point_t menuEndPoint = { menuStartPoint.x + menuSize.x - 1, menuStartPoint.y + menuSize.y - 1 };

	//Cursor starting point *(1,1) of game board*
	Point_t cursorStartPoint = { gameBoardStartPoint.x, gameBoardStartPoint.y };
	Point_t cursorPosition = { cursorStartPoint };
	Point_t boardCursor = { 1,1 };


	int zn = 0, attr = 7, back = 0, zero = 0;

	//stones array
	const unsigned int stonesArraySize = gameBoardSize.x * gameBoardSize.y;
	Stones_enum* stones = new Stones_enum[stonesArraySize];
	resetStones(stones, { gameBoardSize.x, gameBoardSize.y });


#ifndef __cplusplus
	Conio2_Init();
#endif


	// settitle sets the window title
	settitle(NAME_AND_ALBUM);

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);

	
	//CHECKING THE INITIAL VALUES
	if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
	{		
		gotoxy(1, 1);
		textcolor(WHITE);
		textbackground(BLACK);
		cputs("MENU zachodzi na PLANSZE!\n");
		return -1;
	}
	if (!constantsOK({ boardStartPoint, menuStartPoint }))
	{
		gotoxy(1, 1);
		textcolor(WHITE);
		textbackground(BLACK);
		cputs("BLEDNE WARTOSCI STARTOWE!\n");
		return -1;
	}

	//INITILIZE
	drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, 1);
	initializeMenu(MENU_START_POINT, menuSize, cursorPosition);

	do {
		textbackground(BLACK);
		textcolor(7);

		boardCursor = {(cursorPosition.x / (CELL_WIDTH + 1)) - 1, (cursorPosition.y / 2) - 1};

		drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, 0);
		updateMenu({ menuStartPoint.x + 1,menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, boardCursor);

		drawCursor(cursorPosition);
		zero = 0;
		zn = getch();
		

		if (zn == 0) {
			zero = 1;		
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
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends
	return 0;
}
