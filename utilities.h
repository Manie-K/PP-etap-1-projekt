#pragma once
#include "configuration.h"
//PROJECT DONE

//STRUCTURES
struct Point_t {
	int x;
	int y;
}; 
struct Dimensions_t {
	int x;
	int y;
};
struct GameBoardDimensions_t {
	int x;
	int y;
	Dimensions_t wholeBoardSize{};
};
struct Constants_t {
	Point_t boardStart;
	Point_t menuStart;
	Point_t boardEndPoint;
};
enum StonesColors_enum
{
	empty = 0,
	blackStone = 1,
	whiteStone = 2
};
enum PlayersColors_enum
{
	black = 1,
	white = 2
};
struct Stone_t
{
	Point_t position;
	StonesColors_enum color;
	bool checked;
};
struct SinglePlayer_T
{
	PlayersColors_enum playerColor;
	StonesColors_enum stoneColor;
	float score;
};
struct Players_t
{
	SinglePlayer_T current;
	SinglePlayer_T enemy;
};
struct EndPointsInit_t {
	Point_t gameBoardStartPoint;
	Point_t boardStartPoint;
	Point_t menuStartPoint;
};
struct GameStateSave_t
{
	Players_t players;
	Point_t menuStartPoint;
	Point_t boardStartPoint;
	int intersectionCount;
	bool firstRound;
	bool handicap;
};

//FUNCTIONS
void drawBoard(const Point_t startingPoint, const Point_t gameBoardStartPoint, const GameBoardDimensions_t gameBoardDimensions, 
Stone_t stones[], int stoneArraySize_1D, int initialize);

void drawBorder(int startX, int startY, Dimensions_t boardDimensions);
void drawPadding(int startX, int startY, Dimensions_t boardDimensions);
void drawGameBoard(int startX, int startY, Dimensions_t gameBoardDimensions);
void drawStones(Stone_t stones[], int stoneArraySize, Point_t gameStart);

void initializeMenu(const Point_t menuStartPoint, Dimensions_t menuSize, Point_t cursorPosition); //draws the menu, and sets the menu size 
int menuControlsDisplay(const Point_t controlDisplayStart); //draws the control display part of menu, return num of lines drawn

//updates dynamic parts of menu (eg. cursor and score), returns num of lines drawn
int updateMenu(const Point_t dynamicMenuStart, Point_t cursorPosition, const Players_t Players);

void setMenuBackground(Point_t menuStartPoint, Dimensions_t menuSize);
void setBoardDimensions(GameBoardDimensions_t &board, const int intersections);
void setMenuSize(Dimensions_t &menuSize);
void setGameBoardStartPoint(Point_t& gameBoardStartPoint, const Point_t startingPoint);
bool constantsOK(Constants_t constants); //checks if the initial constants are okay (non-negative etc.)
bool rectanglesCollide(Point_t A_topLeft, Point_t A_bottomRight, Point_t B_topLeft, Point_t B_bottomRight);
int chooseGameSize(); //sets the size of the game board (intersection count)
int customGameSize(); //picks custom game board size
void resetStones(Stone_t stones[], int size_1D);
void drawCursor(Point_t cursorPosition);
Stone_t findStoneByPos(Stone_t stones[], Point_t pos, int size_1D); //return the point with this position or {-1, -1} if not found (outside of board)
bool checkStone(Point_t pos, Stone_t stones[], int size_1D, SinglePlayer_T& currentPlayer);
void placeStone(Point_t pos, Stone_t stones[], SinglePlayer_T player, int size_1D);
void changePlayers(Players_t& players);
void setNeighbours(Stone_t neighbours[], Point_t pos, Stone_t stones[], int size_1D);

//initialize mostly board variables
void initializeVariables(const int intersectionCount, Point_t& gameBoardStartPoint, GameBoardDimensions_t& gameBoardSize, Dimensions_t& menuSize, Point_t boardStartPoint);

void initializeCursor(Point_t& cursorPosition, Point_t& boardCursor, Point_t gameBoardStartPoint);
void initializeEndPoints(Point_t& gameBoardEndPoint, Point_t& boardEndPoint, Point_t& menuEndPoint, const Dimensions_t menuSize,
const EndPointsInit_t X, const GameBoardDimensions_t gameBoardSize);

void copyStoneArray(Stone_t source[], Stone_t dest[], int size_1D);
void getRemovedStonesBack(Point_t pos, Stone_t stones[], Stone_t backup[], int size_1D); //reloads the neigbours stones
bool KoRuleOK(Stone_t stones[], Stone_t KoRule[], int size_1D);
void menuCleanBottomInfo(Point_t menuStart, Point_t menuEnd); //cleans bottom part of the menu
int getName(char* name, Point_t menuStart, Point_t menuEnd, Dimensions_t menuSize); //draws and gets the name of the file //-1 if cancelled
bool saveVarsToFile(GameStateSave_t* gameState, char* name); //saves the gameState struct to file, returns false if error occurs
bool saveArraysToFile(char* name, size_t size, Stone_t stones[], Stone_t ko[], Stone_t koBuffer[]); //saves the arrays to file, returns false if error occurs

//loads the gameState++arrays from file, returns false if error occurs
bool loadFromFile(GameStateSave_t* gameState, char* name, Stone_t*& stones, Stone_t*& koRule, Stone_t*& koRuleBuffer); 

int removeChain(Point_t pos, Stone_t stones[], int size_1D); //removes chain and return score
void uncheckStones(Stone_t stones[], int size_1D);
bool chainHasLiberties(Point_t pos, Stone_t stones[], int size_1D);
void printError(const char text[]);
void saveLoadError(const char text[], int color, Point_t pos); //prints error in save/load area
void displayEndScreen(Players_t players);
int calculateTerritory(Point_t pos, Stone_t stones[], int size_1D, bool& wh, bool& bl);
bool gameStarted(Stone_t stones[], int size); //checks if black made a move (if not, black can't skip turn)