//REALLY FINISHED
#include<stdio.h>
#include"conio2.h"
#include "configuration.h"
#include "utilities.h"

int main(){
#ifndef __cplusplus
	Conio2_Init();
#endif

	//initial configuration
	settitle(NAME_AND_ALBUM);
	_setcursortype(_NOCURSOR);
	textbackground(BLACK);
	textcolor(WHITE);
	
	//non-saved variables
	int zn = 0;
	bool topView = false;
	//required variables
	Stone_t* stones = NULL;
	Stone_t* koRule = NULL;
	Stone_t* koRuleBuffer = NULL;
	Players_t players;
	Point_t menuStartPoint = MENU_START_POINT;
	Point_t boardStartPoint = BOARD_START_POINT;
	int intersectionCount;
	bool firstRound = true;
	bool handicap = false;
	
	//Theese variables are set from required ones
	unsigned int stonesArraySize;
	Point_t gameBoardStartPoint;
	GameBoardDimensions_t gameBoardSize;
	Dimensions_t menuSize;
	Point_t gameBoardEndPoint;
	Point_t boardEndPoint;
	Point_t menuEndPoint;
	Point_t cursorPosition;
	Point_t boardCursor;

	//setting variables values
	players = DEFAULT_PLAYER_AND_SCORES;
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

	//checking initial values
	if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
		return -1;
	if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint}))
		return -1;

	//initial draw of board and menu
	drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
	initializeMenu(menuStartPoint, menuSize, boardCursor);
	
	//GAME LOOP
	do {
		//sets the cursor position on game board
		boardCursor = { ((cursorPosition.x - gameBoardStartPoint.x) / (CELL_WIDTH + 1)) + 1, ((cursorPosition.y - gameBoardStartPoint.y) / 2) + 1 };

		//draws game elements
		drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 0);
		updateMenu({ menuStartPoint.x + 1,menuStartPoint.y + DYNAMIC_MENU_Y_OFFSET }, boardCursor, players);
		drawCursor(cursorPosition);

		//sets the camera
		if(!topView)gotoxy(cursorPosition.x, cursorPosition.y);
		else gotoxy(cursorPosition.x, 1);
		topView = false;

		//keyboard input
		zn = getch();

		if (zn == 0) {	
			//menu gets cleaned after cursor moves
			menuCleanBottomInfo(menuStartPoint, menuEndPoint);
			
			zn = getch();		
			if (zn == UP_ARROW) 
			{
				if (cursorPosition.y > gameBoardStartPoint.y)
					cursorPosition.y -= 2;
				else
					topView = true;
			}
			else if (zn == DOWN_ARROW) 
			{
				if (cursorPosition.y < gameBoardEndPoint.y)
					cursorPosition.y += 2;
			}
			else if (zn == LEFT_ARROW)
			{
				if (cursorPosition.x > gameBoardStartPoint.x)
					cursorPosition.x -= CELL_WIDTH + 1;
			}
			else if (zn == RIGHT_ARROW) 
			{
				if (cursorPosition.x < gameBoardEndPoint.x)
					cursorPosition.x += CELL_WIDTH + 1;
			}
		}
		else if (zn == 'i')
		{
			if (checkStone(boardCursor, stones, intersectionCount, players.current))
			{
				//can place stone
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
				uncheckStones(stones, intersectionCount);

				if (firstRound)//initial black advantage
					handicap = true;
				else //Ko rule
				{
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
			//delets old allocated memory
			clrscr();
			delete[] stones;
			delete[] koRule;
			delete[] koRuleBuffer;

			//setting variables values
			players = DEFAULT_PLAYER_AND_SCORES;
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

			//checking initial values
			if (rectanglesCollide(menuStartPoint, menuEndPoint, boardStartPoint, boardEndPoint))
				return -1;
			if (!constantsOK({ boardStartPoint, menuStartPoint, boardEndPoint}))
				return -1;
			
			//initial draw of board and menu
			drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
			initializeMenu(menuStartPoint, menuSize, boardCursor);
		}
		else if (zn == ENTER)
		{
			if (gameStarted(stones, stonesArraySize))
			{
				if (firstRound)
					firstRound = false;
				else
					players.enemy.score++;
				changePlayers(players);
			}
		}
		else if (zn == 's')
		{
			char* fileName = new char[menuSize.x-3];
			if (getName(fileName, menuStartPoint, menuEndPoint, menuSize) != -1)
			{
				//saves variables
				GameStateSave_t* gameState = new GameStateSave_t;
				gameState->players = players;
				gameState->menuStartPoint = menuStartPoint;
				gameState->boardStartPoint = boardStartPoint;
				gameState->intersectionCount = intersectionCount;
				gameState->firstRound = firstRound;
				gameState->handicap = handicap;

				if (!saveVarsToFile(gameState, fileName))
				{
					saveLoadError("DID NOT SAVE TO FILE", RED, { menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2 });
				}
				else 
				{
					//saves arrays to file
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
				if (!loadFromFile(gameState, fileName, stones, koRule, koRuleBuffer)) 
				{
					saveLoadError("DID NOT LOAD FROM FILE", RED, { menuStartPoint.x + 1, menuStartPoint.y + MENU_HEIGHT - 2 });
				}
				else 
				{
					//loads the variables
					intersectionCount = gameState->intersectionCount;					
					players = gameState->players;
					menuStartPoint = gameState->menuStartPoint;
					boardStartPoint = gameState->boardStartPoint;
					firstRound = gameState->firstRound;
					handicap = gameState->handicap;

					//initialize variables
					initializeVariables(intersectionCount, gameBoardStartPoint, gameBoardSize, menuSize, boardStartPoint);
					initializeCursor(cursorPosition, boardCursor, gameBoardStartPoint);

					initializeEndPoints(gameBoardEndPoint, boardEndPoint, menuEndPoint, menuSize,
						{ gameBoardStartPoint, boardStartPoint, menuStartPoint }, gameBoardSize);
					stonesArraySize = intersectionCount * intersectionCount;

					//initialize screen
					clrscr();
					drawBoard(boardStartPoint, gameBoardStartPoint, gameBoardSize, stones, intersectionCount, 1);
					initializeMenu(menuStartPoint, menuSize, boardCursor);
				}
				delete gameState;
			}
			delete []fileName;
		}
		else if (zn == 'f')
		{
			//adding score from handicap
			if (handicap)
			{
				if (players.current.playerColor == white)
					players.current.score += 0.5;
				else
					players.enemy.score += 0.5;
			}
			else
			{
				if (players.current.playerColor == white)
					players.current.score += 6.5;
				else
					players.enemy.score += 6.5;
			}

			//calculate score
			bool blackNeighbour = false, whiteNeighbour = false;
			uncheckStones(stones, intersectionCount);
			for (int y = 0; y < intersectionCount; y++)
			{
				for (int x = 0; x < intersectionCount; x++)
				{
					blackNeighbour = false;
					whiteNeighbour = false;
					if ((stones[x + y * intersectionCount].color == empty) && (stones[x + y * intersectionCount].checked == false)) //C6385 warning, but false positive
					{
						int m = calculateTerritory({ x + 1,y + 1 }, stones, intersectionCount, whiteNeighbour, blackNeighbour);
						if (m != 0)
						{
							if (blackNeighbour)
							{
								if (players.current.playerColor == black)
									players.current.score += m;
								else
									players.enemy.score += m;
							}
							else if (whiteNeighbour)
							{
								if (players.current.playerColor == white)
									players.current.score += m;
								else
									players.enemy.score += m;
							}
						}
					}
				}
			}
			//display
			displayEndScreen(players);

			//config after game ends
			textbackground(BLACK);
			clrscr();
			_setcursortype(_NORMALCURSOR);

			delete[] stones;
			delete[] koRule;
			delete[] koRuleBuffer;

			return 0;
		}
	} while (zn != 'q');

	//config after game ends
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	_setcursortype(_NORMALCURSOR);	

	delete[] stones;
	delete[] koRule;
	delete[] koRuleBuffer;

	return 0;
}
