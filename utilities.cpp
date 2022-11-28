#include "utilities.h"
#include "conio2.h"
#include<stdio.h>

void drawBoard(const Point_t boardStartPoint, const Point_t gameBoardStartPoint, const GameBoardDimensions_t gameBoardDimensions,
Stone_t stones[], int stoneArraySize_1D, int initialize)
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
void drawStones(Stone_t stones[], int stoneArraySize_1D, Point_t gameStart)
{
	for (int y = 0; y < stoneArraySize_1D; y++)
	{
		for (int x = 0; x < stoneArraySize_1D; x++)
		{
			if (stones[x + y * stoneArraySize_1D].color != empty)
			{
				if (stones[x + y * stoneArraySize_1D].color == blackStone)
				{
					textcolor(BLACK);
				}
				else if (stones[x + y * stoneArraySize_1D].color == whiteStone)
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
	cputs("(a) (b) (c) (d) (e) (h) ... ");
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
	k += menuControlsDisplay({ menuStartPoint.x + 1, menuStartPoint.y + k});
	gotoxy(menuStartPoint.x, menuStartPoint.y + (k++));
	for (int i = 0; i < menuSize.x; i++) putch('-');
	gotoxy(menuStartPoint.x + 1, menuStartPoint.y + (k++));
	cputs("Cursor Position: ");
	k += updateMenu({ menuStartPoint.x + 1, menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, cursorPosition, DEFAULT_PLAYER_AND_SCORES);
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
int updateMenu(const Point_t dynamicMenuStart, const Point_t cursorPosition, const Players_t Players)
{
	int k = 0;
	const int bufferSize = 30;
	char buffer[bufferSize];

	textbackground(MENU_BACKGROUND);
	textcolor(MENU_TEXT);
	int scoreBlack;
	int scoreWhite;
	int cursorX = cursorPosition.x;
	int cursorY = cursorPosition.y;
	
	bool blackPlayer;

	if (Players.current.playerColor == black)
	{
		scoreBlack = Players.current.score;
		scoreWhite = Players.enemy.score;
		blackPlayer = true;
	}
	else
	{
		scoreBlack = Players.enemy.score;
		scoreWhite = Players.current.score;
		blackPlayer = false;
	}

	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y + (k++));
	sprintf_s(buffer, "X: %d   Y: %d   ", cursorX, cursorY);
	cputs(buffer);
	k++;
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y + (k++));
	if (blackPlayer)
	{
		cputs("Current player: Black");
	}
	else 
	{
		cputs("Current player: White");
	}
	k++;
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	cputs("Scores:");
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	sprintf_s(buffer, "Black: %d", scoreBlack);
	cputs(buffer);
	gotoxy(dynamicMenuStart.x, dynamicMenuStart.y+ (k++));
	sprintf_s(buffer, "White: %d", scoreWhite);
	cputs(buffer);

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
	text_info info;
	gettextinfo(&info);
	if (constants.boardEndPoint.x > info.screenwidth) return false;
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
	textbackground(BLACK);
	clrscr();
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
		
		const int bufferSize = 30;
		char buffer[bufferSize];

		sprintf_s(buffer,"Board size: %dx%d  ", size, size);
		cputs(buffer);

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

void resetStones(Stone_t stones[], int oneDimSize)
{
	if (stones == NULL) {
		gotoxy(1, 1);
		textcolor(WHITE);
		textbackground(BLACK);
		cputs("STWORZENIE TABLOCY KAMIENI NIE POWIODLO SIE!\n");
	}
	else 
	{
		for (int y = 0; y < oneDimSize; y++)
		{
			for (int x = 0; x < oneDimSize; x++)
			{
				stones[x + y * oneDimSize].color = empty;
				stones[x + y * oneDimSize].position = { x + 1,y + 1 };
				stones[x + y * oneDimSize].liberties = 0;
			}
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

Stone_t findStoneByPos(Stone_t stones[], Point_t pos, int size_1D)
{
	if(pos.x>=1 && pos.y>=1) {
		for (int y = 0; y < size_1D; y++)
		{
			for (int x = 0; x < size_1D; x++)
			{//stones[] starts indexing from 0, board position starts from 1
				if (stones[x + y * size_1D].position.x == pos.x && stones[x + y * size_1D].position.y == pos.y)
					return stones[x + y * size_1D];
			}
		}
	}
	return { {-1,-1}, empty, 0 }; //return a stone with {-1,-1} position
}
bool checkStone(Point_t pos, Stone_t stones[], int size_1D, singlePlayer_T& currentPlayer)
{
	Stone_t thisStone = findStoneByPos(stones, pos, size_1D);
	if (thisStone.color != empty) return false;
	if (stoneHasLiberties(pos, stones, size_1D, currentPlayer.stoneColor)) 
	{ 
		return true; 
	}
	else 
	{
		Point_t pointToBeKilled = stoneCanKill(pos, stones, size_1D, currentPlayer);
		if (pointToBeKilled.x == -1) 
		{
			return false;
		}
		else
		{
			currentPlayer.score += removeStone(pointToBeKilled, stones, size_1D);
			return true;
		}
	}
}
void placeStone(Point_t pos, Stone_t stones[], singlePlayer_T player, int size_1D)
{
	//stones[] starts indexing from 0, board position starts from 1
	int x = pos.x - 1;
	int y = pos.y - 1;
	stones[x + y * size_1D].color = player.stoneColor;
}
void changePlayers(Players_t &players)
{
	singlePlayer_T temp = { players.current.playerColor, players.current.stoneColor ,players.current.score };
	players.current.playerColor = players.enemy.playerColor;
	players.current.stoneColor = players.enemy.stoneColor;
	players.current.score = players.enemy.score;
	players.enemy = temp;
}

bool stoneHasLiberties(Point_t pos, Stone_t stones[], int size_1D, StonesColors_enum currentPlayerStoneColor)
{
	int x = pos.x;
	int y = pos.y;
	
	Stone_t neighbours[NEIGHBOURS_COUNT];
	setNeighbours(neighbours, pos, stones, size_1D);

	for (int k = 0; k < NEIGHBOURS_COUNT; k++)
	{
		if (neighbours[k].position.x != -1) //if its outside of board we dont increase liberties
		{
			if (neighbours[k].color == empty || neighbours[k].color == currentPlayerStoneColor)
			{
				return true;
			}
		}
	}
	return false;
}

Point_t stoneCanKill(Point_t pos, Stone_t stones[], int size_1D, singlePlayer_T currentPlayer)
{
	//stones[] starts indexing from 0, board position starts from 1
	int x = pos.x - 1;
	int y = pos.y - 1;
	//temporarly putting the stone here
	stones[x + y * size_1D].color = currentPlayer.stoneColor;
	int k = 0;
	Stone_t neighbours[NEIGHBOURS_COUNT];
	setNeighbours(neighbours, pos, stones, size_1D);
	for (k = 0; k < NEIGHBOURS_COUNT; k++)
	{
		if (neighbours[k].position.x != -1) {
			if (!stoneHasLiberties(neighbours[k].position, stones, size_1D, neighbours[k].color))
			{
				break;
			}
		}
	}
	//removing the temporary stone, will be added later in main()
	stones[x + y * size_1D].color = empty;
	if (k < 4)
	{
		//placing the stone would kill at least one enemy, giving this stone liberty
		return neighbours[k].position;
	}
	else return { -1, -1};

}
int removeStone(Point_t pos, Stone_t stones[], int size_1D)
{
	//stones[] starts indexing from 0, board position starts from 1
	int x = pos.x - 1;
	int y = pos.y - 1;
	if (stones[x + y * size_1D].color != empty) {
		stones[x + y * size_1D].color = empty;
		return 1; //later change when removing whole chains
	}
	else return 0;
}
void setNeighbours(Stone_t neighbours[], Point_t pos, Stone_t stones[], int size_1D)
{
	neighbours[0] = findStoneByPos(stones, { pos.x, pos.y - 1 }, size_1D);
	neighbours[1] = findStoneByPos(stones, { pos.x, pos.y + 1 }, size_1D);
	neighbours[2] = findStoneByPos(stones, { pos.x + 1, pos.y }, size_1D);
	neighbours[3] = findStoneByPos(stones, { pos.x - 1, pos.y }, size_1D);
}

void initializeVariables(const int intersectionCount, Point_t &gameBoardStartPoint, GameBoardDimensions_t &gameBoardSize, Dimensions_t &menuSize)
{
	setGameBoardStartPoint(gameBoardStartPoint, BOARD_START_POINT);
	setBoardDimensions(gameBoardSize, intersectionCount);
	setMenuSize(menuSize);
}
void initializeCursor(Point_t &cursorPosition, Point_t &boardCursor, const Point_t gameBoardStartPoint) {
	cursorPosition = { gameBoardStartPoint.x, gameBoardStartPoint.y };
	boardCursor = { 1,1 };
}

void initializeEndPoints(Point_t &gameBoardEndPoint, Point_t &boardEndPoint, Point_t &menuEndPoint,
const Dimensions_t menuSize, const EndPointsInit_t X, const GameBoardDimensions_t gameBoardSize) {
	gameBoardEndPoint = { X.gameBoardStartPoint.x + gameBoardSize.x - 1, X.gameBoardStartPoint.y + gameBoardSize.y - 1 };
	boardEndPoint = { X.boardStartPoint.x + gameBoardSize.wholeBoardSize.x - 1, X.boardStartPoint.y + gameBoardSize.wholeBoardSize.y - 1 };
	menuEndPoint = { X.menuStartPoint.x + menuSize.x - 1, X.menuStartPoint.y + menuSize.y - 1 };
}