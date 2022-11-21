#pragma once

#include "configuration.h"
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
};

void initializeBoard(const Point_t startingPoint, const Point_t gameBoardStartPoint, const GameBoardDimensions_t gameBoardDimensions); //draws the whole board + stones
void drawBorder(int startX, int startY, Dimensions_t boardDimensions); //draws a border of the board
void drawPadding(int startX, int startY, Dimensions_t boardDimensions); //draws a padding of the board
void drawGameBoard(int startX, int startY, Dimensions_t gameBoardDimensions); //draws the game board (intersections + lines)
//drawStones();

void updateGameBoard(const Point_t gameBoardStartPoint, const Dimensions_t gameBoardDimensions); //updates the game board and stones

void initializeMenu(const Point_t menuStartPoint, Dimensions_t menuSize); //draws the menu, and sets the menu size 
int menuControlsDisplay(const Point_t controlDisplayStart); //draws the control display part of menu, return num of lines drawn
int updateMenu(const Point_t dynamicMenuStart); //updates dynamic parts of menu (eg. cursor and score), returns num of lines drawn
void setMenuBackground(Point_t menuStartPoint, Dimensions_t menuSize); //sets the background of the menu

//sets the sizes od board and game board. Uses original boardDimension
void setBoardDimensions(GameBoardDimensions_t &board, const int intersections);

//sets the size of menu
void setMenuSize(Dimensions_t &menuSize);

//sets the start point of the game board. Uses original gameBoardStartPoint
void setGameBoardStartPoint(Point_t& gameBoardStartPoint, const Point_t startingPoint);

bool constantsOK(Constants_t constants); //checks if the initial constants are okay (non-negative etc.)
bool rectanglesCollide(Point_t A_topLeft, Point_t A_bottomRight, Point_t B_topLeft, Point_t B_bottomRight); //checks if 2 rectangles collide

//sets the size of the game board (intersection count)
int chooseGameSize();

//pics custom game board size
int customGameSize();