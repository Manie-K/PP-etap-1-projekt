#include<stdio.h>
#include"conio2.h"
#include "configuration.h"
#include "utilities.h"

int main(){
#ifndef __cplusplus
	Conio2_Init();
#endif

	int zn = 0;
	settitle(NAME_AND_ALBUM);
	_setcursortype(_NOCURSOR);
	textbackground(BLACK);
	textcolor(7);
	//required
	Stone_t* stones = NULL;
	Stone_t* koRule = NULL;
	Stone_t* koRuleBuffer = NULL;
	Players_t players;
	Point_t menuStartPoint = MENU_START_POINT;
	Point_t boardStartPoint = BOARD_START_POINT;
	int intersectionCount;
	bool firstRound = true;
	unsigned int handicap = 0;
	//are set from required ones
	unsigned int stonesArraySize;
	Point_t gameBoardStartPoint;
	GameBoardDimensions_t gameBoardSize;
	Dimensions_t menuSize;
	Point_t gameBoardEndPoint;
	Point_t boardEndPoint;
	Point_t menuEndPoint;
	Point_t cursorPosition;
	Point_t boardCursor;

	intersectionCount = chooseGameSize();
	initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize, boardStartPoint);
	initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

	initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize, 
	{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);

	stonesArraySize = intersectionCount * intersectionCount;
	stones = new Stone_t[stonesArraySize];
	koRule = new Stone_t[stonesArraySize];
	koRuleBuffer = new Stone_t[stonesArraySize];
	resetStones(stones, intersectionCount);
	resetStones(koRule, intersectionCount);
	resetStones(koRuleBuffer, intersectionCount);
	
	players = DEFAULT_PLAYER_AND_SCORES;

	//CHECKING THE INITIAL VALUES
	if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
		return -1;
	if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint}))
		return -1;

	//INITIAL DRAW
	drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
	initializeMenu(menuStartPoint, menuSize, boardCursor);

	do {
		boardCursor = { ((cursorPosition.x - gameBoardStartPoint.x) / (CELL_WIDTH + 1)) + 1, ((cursorPosition.y - gameBoardStartPoint.y) / 2) + 1 };

		drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 0);
		updateMenu({ menuStartPoint.x + 1,menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, boardCursor, players);
		drawCursor(cursorPosition);

		zn = getch();

		if (zn == 0) {	
			menuCleanBottomInfo(menuStartPoint, menuEndPoint);
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
				int score = 0;
				placeStone(boardCursor, stones, players.current, intersectionCount);
				Stone_t* neighbours = new Stone_t[NEIGHBOURS_COUNT];
				setNeighbours(neighbours, boardCursor, stones, intersectionCount);
				for (int i = 0; i < NEIGHBOURS_COUNT; i++)
				{
					if (neighbours[i].color == players.enemy.stoneColor)
					{
						uncheckStones(stones, intersectionCount);
						if (!chainHasLiberties(neighbours[i].position, stones, intersectionCount))
						{
							uncheckStones(stones, intersectionCount);
							score += removeChain(neighbours[i].position, stones, intersectionCount);
						}
					}
				}
				if (firstRound) { //initial black advantage
					handicap++;
				}
				else {
					if (KoRuleOK(stones, koRule, intersectionCount)) {
						copyStoneArray(koRuleBuffer, koRule, intersectionCount);
						copyStoneArray(stones, koRuleBuffer, intersectionCount);
						players.current.score += score;
						changePlayers(players);
					}
					else
					{
						removeChain(boardCursor, stones, intersectionCount);
						getRemovedStonesBack(boardCursor, stones, koRuleBuffer, intersectionCount);
					}
				}
				delete[] neighbours;
			}
		}
		else if (zn == 'n')
		{
			clrscr();
			delete[] stones;
			delete[] koRule;
			delete[] koRuleBuffer;

			intersectionCount = chooseGameSize();
			initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize, boardStartPoint);
			initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

			initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize,
				{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);

			stonesArraySize = intersectionCount * intersectionCount;
			stones = new Stone_t[stonesArraySize];
			koRule = new Stone_t[stonesArraySize];
			koRuleBuffer = new Stone_t[stonesArraySize];
			resetStones(stones, intersectionCount);
			resetStones(koRule, intersectionCount);
			resetStones(koRuleBuffer, intersectionCount);
			players = DEFAULT_PLAYER_AND_SCORES;

			//CHECKING THE INITIAL VALUES
			if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
				return -1;
			if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint}))
				return -1;
			
			//INITIAL DRAW
			drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
			initializeMenu(menuStartPoint, menuSize, boardCursor);

		}
		else if (zn == '\r')//enter
		{
			changePlayers(players);
			if (firstRound)
			{
				firstRound = false;
			}
			else 
			{
				players.current.score++;
			}
		}
		else if (zn == 's')
		{
			char* fileName = new char[menuSize.x-3];
			if (getName(fileName, menuStartPoint, menuEndPoint, menuSize) != -1)
			{
				GameStateSave_t* gameState = new GameStateSave_t;
				gameState->players = players;
				gameState->menuStartPoint = menuStartPoint;
				gameState->boardStartPoint = boardStartPoint;
				gameState->intersectionCount = intersectionCount;
				gameState->firstRound = firstRound;
				gameState->handicap = handicap;

				if(!saveVarsToFile(gameState, fileName))
					saveLoadError("DID NOT SAVE TO FILE", RED, { menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2 });
				else 
				{
					if (saveArraysToFile(fileName, stonesArraySize, stones, koRule, koRuleBuffer))
						saveLoadError("SUCCESSFULLY SAVED", DARKGRAY, { menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2 });
					else
						saveLoadError("ERROR WHILE SAVING TO FILE", RED, { menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2 });
				}
				delete gameState;
			}
			delete[] fileName;
		}
		else if (zn == 'l')
		{
			char* fileName = new char[menuSize.x - 3];
			if (getName(fileName, menuStartPoint, menuEndPoint, menuSize) != -1)
			{ 
				delete[] stones;
				delete[] koRuleBuffer;
				delete[] koRule;
				GameStateSave_t* gameState = new GameStateSave_t;
				if (!loadFromFile(gameState, fileName, stones, koRule, koRuleBuffer)) {
					textcolor(RED);
					textbackground(MENU_BACKGROUND);
					gotoxy(menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2);
					cputs("DID NOT LOAD FROM FILE");
					textcolor(BLACK);
				}
				else {
					intersectionCount = gameState->intersectionCount;					
					players = gameState->players;
					menuStartPoint = gameState->menuStartPoint;
					boardStartPoint = gameState->boardStartPoint;
					firstRound = gameState->firstRound;
					handicap = gameState->handicap;

					initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize, boardStartPoint);
					initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

					initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize,
						{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);
					stonesArraySize = intersectionCount * intersectionCount;

					clrscr();
					drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
					initializeMenu(menuStartPoint, menuSize, boardCursor);
				}
				delete gameState;
			}
			delete []fileName;
		}
	} while (zn != 'q');

	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	_setcursortype(_NORMALCURSOR);	

	delete[] stones;
	delete[] koRule;
	delete[] koRuleBuffer;

	return 0;
}
