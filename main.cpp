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

	//Board end point
	Point_t boardEndPoint = { boardStartPoint.x + gameBoardSize.wholeBoardSize.x - 1, boardStartPoint.y + gameBoardSize.wholeBoardSize.y - 1 };

	//Menu starting position
	Point_t menuStartPoint = MENU_START_POINT;
	//Menu size, set to correct value later when drawing menu for first time
	Dimensions_t menuSize;
	setMenuSize(menuSize);

	//Menu ending
	Point_t menuEndPoint = { menuStartPoint.x + menuSize.x - 1, menuStartPoint.y + menuSize.y - 1 };
	
	//Cursor starting point *(1,1) of game board*
	Point_t cursorStartPoint = { gameBoardStartPoint.x, gameBoardStartPoint.y };

	int zn = 0, x = 0, y = 0, attr = 7, back = 0, zero = 0;
	char txt[32];

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


	do {
		textbackground(BLACK);
		clrscr();
		textcolor(7);

		initializeMenu(MENU_START_POINT, menuSize);
		initializeBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize);
		// we draw a star
		gotoxy(cursorStartPoint.x + x, cursorStartPoint.y + y);
		textcolor(attr);
		textbackground(back);
		// putch prints one character and moves the cursor to the right
		putch('*');
		// we wait for key press and get its code
		// most key codes correspond to the characters, like
		// a is 'a', 2 is '2', + is '+', but some special keys
		// like cursors provide two characters, where the first
		// one is zero, e.g., "up arrow" is zero and 'H'
		zero = 0;
		zn = getch();
		// we do not want the key 'H' to play role of "up arrow"
		// so we check if the first code is zero
		if (zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == 0x48) y-=2;	// will be a special key
			else if (zn == 0x50) y+=2;
			else if (zn == 0x4b) x-=CELL_WIDTH+1;
			else if (zn == 0x4d) x+=CELL_WIDTH+1;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;	// enter key is 0x0d or '\r'
	} while (zn != 'q');

	textbackground(BLACK);
	clrscr();
	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
	// visible after the program ends
	return 0;
}
