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
	int liberties;
};
struct singlePlayer_T
{
	PlayersColors_enum playerColor;
	StonesColors_enum stoneColor;
	int score;
};
struct Players_t
{
	singlePlayer_T current;
	singlePlayer_T enemy;
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
int customGameSize(); //pics custom game board size

void resetStones(Stone_t stones[], int oneDimSize); //sets all intersections to EMPTY

void drawCursor(Point_t cursorPosition); //draws cursor

Stone_t findStoneByPos(Stone_t stones[], Point_t pos, int size_1D); //return the point with this position or {-1, -1} if not found (out of board)
bool checkStone(Point_t pos, Stone_t stones[], int size_1D, singlePlayer_T currentPlayer); //checks if stone can be placed here
void placeStone(Point_t pos, Stone_t stones[], singlePlayer_T player, int size_1D); //add a stone to STONE array which will be later drawn 
void changePlayers(Players_t& players); //swaps players (current and enemy)
bool stoneHasLiberties(Point_t pos, Stone_t stones[], int size_1D, singlePlayer_T currentPlayer) //check if stone at this position has liberties (ture or false)