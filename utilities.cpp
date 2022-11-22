#include "utilities.h"
#include "conio2.h"
#include<stdio.h>

void drawBoard(const Point_t boardStartPoint, const Point_t gameBoardStartPoint, const GameBoardDimensions_t gameBoardDimensions,
Stones_enum stones[], int stoneArraySize_1D, int initialize)
{
	drawGameBoard(gameBoardStartPoint.x, gameBoardStartPoint.y, { gameBoardDimensions.x, gameBoardDimensions.y });
	drawStones(stones, stoneArraySize_1D, gameBoardStartPoint);
	if(initialize == 1)drawBorder(boardStartPoint.x, boardStartPoint.y, gameBoardDimensions.wholeBoardSize);
	drawPadding(boardStartPoint.x, boardStartPoint.y, gameBoardDimensions.wholeBoardSize);
}
void drawBorder(int startX, int startY, Dimensions_t boardDimensions)
{
	textbackground(BORDER_BACKGROUND);
	textcolor(BORDER_TEXT_COLOR);
	//top
	gotoxy(startX, startY);
	for (int i = 0; i < boardDimensions.x; i++) {
		putch(BORDER_CHAR);
	}
	//bottom
	gotoxy(startX, boardDimensions.y + startY - 1);
	for (int i = 0; i < boardDimensions.x; i++) {
		putch(BORDER_CHAR);
	}
	//left  do it height -2 times (-2 because top and bottom already done)
	for (int i = 1; i <= boardDimensions.y - 2; i++) {
		gotoxy(startX, startY + i);
		putch(BORDER_CHAR);
	}
	//right
	for (int i = 1; i <= boardDimensions.y - 2; i++) {
		gotoxy(startX - 1 + boardDimensions.x, startY + i);
		putch(BORDER_CHAR);
	}
}
void drawPadding(int startX, int startY, Dimensions_t boardDimensions)
{
	textbackground(BOARD_PADDING_BACKGROUND);
	
	//too little padding (cursor problems)
	if (GAME_BOARD_PADDING < 1)
	{
		gotoxy(1, 1);
		textbackground(RED);
		cputs("TOO LITTLE PADDING");
		return;
	}
	//PADDING VALUE IS FINE 
	//TOP
	for (int i = 0; i < GAME_BOARD_PADDING; i++)
	{
		gotoxy(startX + 1, startY + 1 + i);
		{
			for (int j = 1; j < boardDimensions.x - 1; j++) putch(' ');
		}
	}
	//BOTTOM
	for (int i = 0; i < GAME_BOARD_PADDING; i++)
	{
		gotoxy(startX + 1, startY + boardDimensions.y - 2 - i);
		{
			for (int j = 1; j < boardDimensions.x - 1; j++) putch(' ');
		}
	}
	//LEFT  //from end (without border) minus padding 
	for(int i = 0; i < boardDimensions.y - 2*(GAME_BOARD_PADDING+1); i++)
	{
		gotoxy(startX+1, startY + 1 + GAME_BOARD_PADDING + i);
		for (int j = 0; j < GAME_BOARD_PADDING * CELL_WIDTH; j++) putch(' ');
	}
	//RIGHT  //from end (without border) minus padding*width of cell
	for (int i = 0; i < boardDimensions.y - 2 * (GAME_BOARD_PADDING + 1); i++)
	{
		gotoxy(startX + boardDimensions.x - 1 - GAME_BOARD_PADDING*CELL_WIDTH, startY + 1 + GAME_BOARD_PADDING + i);
		for (int j = 0; j < GAME_BOARD_PADDING * CELL_WIDTH; j++) putch(' ');
	}

	/*if (layersToGo == 0) return;
	int endX = boardDimensions.x - startX + 1;
	int endY = boardDimensions.y - startY + 1;
	//TOP
	gotoxy(startX, startY);
	for (int i = startX; i <= endX; i++) {
		putch(' ');
	}
	//BOTTOM
	gotoxy(startX, endY);
	for (int i = startX; i <= endX; i++) {
		putch(' ');
	}
	//LEFT
	for (int j = 0; j < CELL_WIDTH; j++) {
		for (int i = startY + 1; i <= endY; i++) {
			gotoxy(startX + j, i);
			putch(' ');
		}
	}
	//RIGHT
	for (int j = 0; j < CELL_WIDTH; j++) {
		for (int i = startY + 1; i <= endY; i++) {
			gotoxy(endX - j, i);
			putch(' ');
		}
	}
	//Next layer
	drawPadding(startX + 1, startY + 1, layersToGo - 1, boardDimensions);*/
}
void drawGameBoard(int startX, int startY, Dimensions_t gameBoardDimensions) {
	//characters used:
	const unsigned char intersectionChar = 197;			//┼
	
	const unsigned char verticalLine = 179;				//│
	const unsigned char horizontalLine = 196;			//─
	
	const unsigned char topCrossing = 194;				//┬
	const unsigned char bottomCrossing = 193;				//┴
	const unsigned char rightCrossing = 180;			//┤
	const unsigned char leftCrossing = 195;					//├
	
	const unsigned char emptySpace = ' ';			
	//----------------
	//Colors
	textbackground(GAME_BOARD_BACKGROUND);
	textcolor(GAME_BOARD_TEXT);
	//------
	//Points
	Dimensions_t gameBoardSize = {gameBoardDimensions.x, gameBoardDimensions.y};
	Point_t topLeft = {startX, startY};
	Point_t topRight = {startX + gameBoardSize.x-1, startY};
	Point_t bottomRight = {startX + gameBoardSize.x-1, startY+gameBoardSize.y-1};
	Point_t bottomLeft = {startX, startY + gameBoardSize.y-1};
	//------
	//Center and sides
	gotoxy(50, 50);
	for (int i = 0; i < gameBoardSize.y; i++)
	{
		gotoxy(topLeft.x, topLeft.y + i); //game board start on first iteration
		for (int j = 0; j < gameBoardSize.x; j++)
		{
			if (i % 2 == 0)
			{
				if (j % (CELL_WIDTH + 1) == 0)
				{
					if (i == 0) putch(topCrossing);
					else if(i == gameBoardSize.y - 1) putch(bottomCrossing);
					else if (j == 0) putch(leftCrossing);
					else if (j == gameBoardSize.x - 1) putch(rightCrossing);
					else putch(intersectionChar);
				}
				else putch(horizontalLine);
			}
			else 
			{
				if (j % (CELL_WIDTH + 1) == 0) putch(verticalLine);
				else putch(emptySpace);
			}
		}
	}
	//----------------
	//Corners
	gotoxy(topLeft.x, topLeft.y);
	putch(218);								//┌
	gotoxy(topRight.x, topRight.y);
	putch(191);								//┐
	gotoxy(bottomRight.x, bottomRight.y);
	putch(217);								//┘
	gotoxy(bottomLeft.x, bottomLeft.y);
	putch(192);								//└
}
void drawStones(Stones_enum stones[], int stoneArraySize_1D, Point_t gameStart)
{
	for (int y = 0; y < stoneArraySize_1D; y++)
	{
		for (int x = 0; x < stoneArraySize_1D; x++)
		{
			if (stones[x + y * stoneArraySize_1D] != empty)
			{
				if (stones[x + y * stoneArraySize_1D] == blackStone)
				{
					textcolor(BLACK);
				}
				else if (stones[x + y * stoneArraySize_1D] == whiteStone)
				{
					textcolor(WHITE);
				}
				gotoxy(gameStart.x + x*(CELL_WIDTH+1), gameStart.y + y*2);
				putch(STONE_CHAR);
			}
		}
	}
	textcolor(BLACK);
}

void initializeMenu(const Point_t menuStartPoint, const Dimensions_t menuSize, const Point_t cursorPosition)
{
	textbackground(MENU_BACKGROUND);
	textcolor(MENU_TEXT);

	setMenuBackground(menuStartPoint, menuSize);
	int k = 0;

	//+1 in every x coord to make it 'centered'
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
	gotoxy(menuStartPoint.x + 1, menuStartPoint.y + (k++));
	cputs(NAME_AND_ALBUM);
	gotoxy(menuStartPoint.x + 1, menuStartPoint.y + (k++));
	cputs(IMPLEMENTED_FUNCTIONALITIES_STRING);
	gotoxy(menuStartPoint.x + 1, menuStartPoint.y + (k++));
	cputs("(a) (b) (c) ... ");
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
	k += menuControlsDisplay({ menuStartPoint.x + 1, menuStartPoint.y + k});
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
	gotoxy(menuStartPoint.x + 1, menuStartPoint.y + (k++));
	cputs("Cursor Position: ");
	k += updateMenu({ menuStartPoint.x + 1, menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, cursorPosition);
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
}
int menuControlsDisplay(const Point_t controlDisplayStart)
{
	int i = 0;
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("Availabe controls:");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("arrows - move the cursor");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("q - quit game");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("enter - confirm");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("escape - cancel");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("i - place stone");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("s - save game");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("l - load game");
	gotoxy(controlDisplayStart.x, controlDisplayStart.y + (i++));
	cputs("f - finish game");

	return i;
}
int updateMenu(const Point_t dynamicMenuStart, const Point_t cursorPosition)
{
	int k = 0;

	textbackground(MENU_BACKGROUND);
	textcolor(MENU_TEXT);

	int cursorX = cursorPosition.x;
	int cursorY = cursorPosition.y;
	char currentPlayer[] = "White";
	int scoreBlack = 1;
	int scoreWhite = 5;
	
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y + (k++));
	printf("X: %d   Y: %d   ", cursorX, cursorY);
	k++;
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y + (k++));
	printf("Current player: %s", currentPlayer);
	k++;
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	cputs("Scores:");
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	printf("Black: %d", scoreBlack);
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	printf("White: %d", scoreWhite);

	return k;
}
void setMenuBackground(Point_t menuStartPoint, Dimensions_t menuSize) {
	textbackground(MENU_BACKGROUND);
	for (int i = 0; i < menuSize.y; i++)
	{
		gotoxy(menuStartPoint.x, menuStartPoint.y + i);
		for(int j = 0; j < menuSize.x; j++)
		{
			putch(' ');
		}
	}
}


void setBoardDimensions(GameBoardDimensions_t &board, const int intersections)
{
	board.x = 4 * intersections - 3;
	board.y = 2 * intersections - 1;
	board.wholeBoardSize.x = board.x + 2 * ((CELL_WIDTH * GAME_BOARD_PADDING) + 1);
	board.wholeBoardSize.y = board.y + 2 * (GAME_BOARD_PADDING + 1);
}
void setMenuSize(Dimensions_t &menuSize)
{
	int width = sizeof(IMPLEMENTED_FUNCTIONALITIES_STRING) / sizeof(IMPLEMENTED_FUNCTIONALITIES_STRING[0]) - 1;;
	menuSize.x = width + 2; //+2 because one empty space on each side
	menuSize.y = MENU_HEIGHT;
}
void setGameBoardStartPoint(Point_t &gameBoardStartPoint, const Point_t startingPoint)
{
	gameBoardStartPoint.x = startingPoint.x + 1 + GAME_BOARD_PADDING * CELL_WIDTH;
	gameBoardStartPoint.y = startingPoint.y + 1 + GAME_BOARD_PADDING;
}

bool constantsOK(const Constants_t constants)
{
	if (constants.boardStart.x < 1 ||
		constants.boardStart.y < 1 ||
		constants.menuStart.x < 1 ||
		constants.menuStart.y < 1)
		return false;
	if (GAME_BOARD_PADDING < 1) return false;
	return true;
}
bool rectanglesCollide(Point_t A_topLeft, Point_t A_bottomRight, Point_t B_topLeft, Point_t B_bottomRight)
{
	if (A_topLeft.x > B_bottomRight.x || B_topLeft.x > A_bottomRight.x) return false; //checks horizontally
	if (A_topLeft.y > B_bottomRight.y || B_topLeft.y > A_bottomRight.y) return false; //checks vertically
	return true;
}

int chooseGameSize()
{
	int size = 0, zn=0;
	textbackground(LIGHTCYAN);
	textcolor(BLACK);
	
	gotoxy(5, 5);
	cputs("Choose the size of the game board:");
	gotoxy(5, 6);
	cputs("a) 9x9");
	gotoxy(5, 7);
	cputs("b) 13x13");
	gotoxy(5, 8);
	cputs("c) 19x19");
	gotoxy(5, 9);
	cputs("d) custom size");

	textbackground(BLACK);
	
	while (true) {
		zn = getch();
		if (zn == (int)'a') {
			clrscr();
			return 9;
		}
		else if (zn == (int)'b') {
			clrscr();
			return 13;
		}
		else if (zn == (int)'c') {
			clrscr();
			return 19;
		}
		else if (zn == (int)'d') {
			clrscr();
			return customGameSize();
		}
	}

}
int customGameSize()
{
	int zn;
	int size = 3;

	textbackground(LIGHTCYAN);
	textcolor(BLACK);

	gotoxy(5, 6);
	cputs("<-     decrease size");
	gotoxy(5, 7);
	cputs("->     increase size");
	gotoxy(5, 8);
	cputs("enter  confirm choice");
	gotoxy(5, 9);
	cputs("escape cancel");

	while (true)
	{
		gotoxy(5,5);
		
		textbackground(LIGHTCYAN);
		textcolor(RED);
		
		printf("Board size: %dx%d  ", size, size);
		
		textbackground(BLACK);
		textcolor(BLACK);

		zn = getch();
		if (zn == 0)
		{
			zn = getch();
			if (zn == 0x4b)
			{
				if(size > MIN_GAME_BOARD_SIZE)size--;
			}
			else if (zn == 0x4d)
			{
				if (size < MAX_GAME_BOARD_SIZE)size++;
			}
		}
		else if(zn == '\r') //enter key
		{ 
			clrscr();
			return size;
		}
		else if (zn == '\x1b') //escape
		{
			clrscr();
			return chooseGameSize();
		}
	}
}

void resetStones(Stones_enum stones[], int oneDimSize)
{
	for (int y = 0; y < oneDimSize; y++)
	{
		for (int x = 0; x < oneDimSize; x++)
		{
			stones[x + y * oneDimSize] = empty;
		}
	}
}
void drawCursor(Point_t cursorPosition)
{
	textcolor(CURSOR_COLOR);
	textbackground(GAME_BOARD_BACKGROUND);
	int x = cursorPosition.x;
	int y = cursorPosition.y;
	
	//drawing cursor
	gotoxy(x+1, y + 1);
	putch(217);								//┘
	gotoxy(x+1, y - 1);
	putch(191);								//┐
	gotoxy(x-1, y + 1);
	putch(192);								//└
	gotoxy(x-1, y - 1);
	putch(218);								//┌

	textcolor(BLACK);
}