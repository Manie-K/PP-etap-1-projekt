#pragma once

#include "configuration.h"

//DATA STRUCTURES
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
};
struct SinglePlayer_T
{
	PlayersColors_enum playerColor;
	StonesColors_enum stoneColor;
	int score;
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
	Stone_t* stones;
	Stone_t* koRule;
	Stone_t* koRuleBuffer;
	Players_t players;
	Point_t menuStartPoint;
	Point_t boardStartPoint;
	int intersectionCount;
	bool firstRound;
	unsigned int handicap;
};

//FUNCTIONS
//draws the whole board + stones
void drawBoard(const Point_t startingPoint, const Point_t gameBoardStartPoint, const GameBoardDimensions_t gameBoardDimensions, 
Stone_t stones[], int stoneArraySize_1D, int initialize);

void drawBorder(int startX, int startY, Dimensions_t boardDimensions); //draws a border of the board
void drawPadding(int startX, int startY, Dimensions_t boardDimensions); //draws a padding of the board
void drawGameBoard(int startX, int startY, Dimensions_t gameBoardDimensions); //draws the game board (intersections + lines)
void drawStones(Stone_t stones[], int stoneArraySize, Point_t gameStart); //draws stones


void initializeMenu(const Point_t menuStartPoint, Dimensions_t menuSize, Point_t cursorPosition); //draws the menu, and sets the menu size 
int menuControlsDisplay(const Point_t controlDisplayStart); //draws the control display part of menu, return num of lines drawn
int updateMenu(const Point_t dynamicMenuStart, Point_t cursorPosition, const Players_t Players); //updates dynamic parts of menu (eg. cursor and score), returns num of lines drawn
void setMenuBackground(Point_t menuStartPoint, Dimensions_t menuSize); //sets the background of the menu

//sets the sizes od board and game board. Uses original boardDimension
void setBoardDimensions(GameBoardDimensions_t &board, const int intersections);

//sets the size of menu
void setMenuSize(Dimensions_t &menuSize);

//sets the start point of the game board. Uses original gameBoardStartPoint
void setGameBoardStartPoint(Point_t& gameBoardStartPoint, const Point_t startingPoint);

bool constantsOK(Constants_t constants); //checks if the initial constants are okay (non-negative etc.)
//checks if 2 rectangles collide
bool rectanglesCollide(Point_t A_topLeft, Point_t A_bottomRight, Point_t B_topLeft, Point_t B_bottomRight);

int chooseGameSize(); //sets the size of the game board (intersection count)
int customGameSize(); //picks custom game board size

void resetStones(Stone_t stones[], int oneDimSize); //sets all intersections to EMPTY

void drawCursor(Point_t cursorPosition); //draws cursor

Stone_t findStoneByPos(Stone_t stones[], Point_t pos, int size_1D); //return the point with this position or {-1, -1} if not found (out of board)
bool checkStone(Point_t pos, Stone_t stones[], int size_1D, SinglePlayer_T& currentPlayer); //checks if stone can be placed here
void placeStone(Point_t pos, Stone_t stones[], SinglePlayer_T player, int size_1D); //add a stone to STONE array which will be later drawn 
void changePlayers(Players_t& players); //swaps players (current and enemy)

//checks if stone at this position has liberties (true or false)
bool stoneHasLiberties(Point_t pos, Stone_t stones[], int size_1D, StonesColors_enum currentPlayerStoneColor);

//checks if this stone placed at pos can kills other instead of suicide, return {-1,-1} if not, {x,y} of given stone otherwise
bool stoneCanKill(Point_t pos, Stone_t stones[], int size_1D, SinglePlayer_T currentPlayer); 

int removeStone(Point_t pos, Stone_t stones[], int size_1D); //removes the stone at given position, return number of stones removed

void setNeighbours(Stone_t neighbours[], Point_t pos, Stone_t stones[], int size_1D); //changes the neighbours array, sets the cell neighbours

//initialize mostly board variables
void initializeVariables(const int intersectionCount, Point_t& gameBoardStartPoint, GameBoardDimensions_t& gameBoardSize, Dimensions_t& menuSize, Point_t boardStartPoint);
void initializeCursor(Point_t& cursorPosition, Point_t& boardCursor, Point_t gameBoardStartPoint); //initialize cursor varaibles

//initialize endpoints
void initializeEndPoints(Point_t& gameBoardEndPoint, Point_t& boardEndPoint, Point_t& menuEndPoint, const Dimensions_t menuSize,
const EndPointsInit_t X, const GameBoardDimensions_t gameBoardSize);

void copyStoneArray(Stone_t source[], Stone_t dest[], int oneDimSize); //copies stones array into ko rule array (for next round)
void getRemovedStonesBack(Point_t pos, Stone_t stones[], Stone_t backup[], int oneDimSize); //reloads the neigbours stones
bool KoRuleOK(Stone_t stones[], Stone_t KoRule[], int oneDimSize); //checks if the ko rule takes place (return false if yes)
void menuCleanBottomInfo(Point_t menuStart, Point_t menuEnd); //cleans bottom part of the menu
int getName(char* name, Point_t menuStart, Point_t menuEnd, Dimensions_t menuSize); //draws and gets the name of the file //-1 if cancelled
bool saveToFile(GameStateSave_t* gameState, char* name); //saves the gameState struct to file, returns false if error occurs
bool loadFromFile(GameStateSave_t* gameState, char* name); //loads the gameState from file, returns false if error occurs