#pragma once
//PROJECT DONE
//MAIN SETTINGS---------------------------------------------------------------
#define BOARD_START_POINT {32,4} //sets the board (border + padding + game board) top left point {x,y} 
#define MENU_START_POINT {1,1} //sets the menu top left point {x,y}
#define STONE_CHAR 254 //the character used to represent a stone on board

//BOARD SETTINGS--------------------------------------------------------------
//!--- BORDER ---!
#define BORDER_CHAR ('#') //character displayed on border
#define BORDER_BACKGROUND RED
#define BORDER_TEXT_COLOR BLACK
//!--- PADDING ---!
#define GAME_BOARD_PADDING 1 // <1;+infinity) area between game board and border
#define BOARD_PADDING_BACKGROUND BROWN
//!--- GAME BOARD ---!
#define GAME_BOARD_BACKGROUND BROWN
#define GAME_BOARD_TEXT DARKGRAY
#define MIN_GAME_BOARD_SIZE 3
#define MAX_GAME_BOARD_SIZE 25

//MENU SETTINGS---------------------------------------------------------------
//!--- Static menu ---!
#define MENU_BACKGROUND CYAN
#define MENU_TEXT BLACK

//CURSOR----------------------------------------------------------------------
#define CURSOR_COLOR GREEN

//DO NOT EDIT-----------------------------------------------------------------
#define CELL_WIDTH 3 //width of single character (3 to make it look better)
#define NAME_AND_ALBUM "Maciej Goralczyk 193302" //my name and student album number
#define IMPLEMENTED_FUNCTIONALITIES_STRING "Implemented functionalities:" //used later to calculate menu width
#define MENU_HEIGHT 27 //sets menu height (manually, beacuse it is dependant of number of functionalities and controls
#define DYNAMIC_MENU_Y_OFFSET 17 //where dynamic menu starts
#define DEFAULT_PLAYER_AND_SCORES { {black, blackStone,0}, {white,whiteStone ,0}} //initial current player and scores
#define NEIGHBOURS_COUNT 4 //always 4, even if near border, so no need to change
#define DOWN_ARROW 0x50
#define UP_ARROW 0x48
#define RIGHT_ARROW 0x4d
#define LEFT_ARROW 0x4b
#define ENTER '\r'
#define ESC '\x1b'