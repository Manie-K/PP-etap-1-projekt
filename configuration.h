#pragma once
//MAIN SETTINGS---------------------------------------------------------------
#define BOARD_START_POINT {90,1} //sets the board (border + padding + game board) top left point {x,y} 
#define MENU_START_POINT {1,1} //sets the menu top left point {x,y}
//BOARD SETTINGS--------------------------------------------------------------
//!--- BORDER ---!
#define BORDER_CHAR ('#') //character displayed on border
#define BORDER_BACKGROUND RED
#define BORDER_TEXT_COLOR BLACK
//!--- PADDING ---!
#define GAME_BOARD_PADDING 2 // <1;+infinity) area between game board and border
#define BOARD_PADDING_BACKGROUND BROWN
//!--- GAME BOARD ---!
#define GAME_BOARD_BACKGROUND BROWN
#define GAME_BOARD_TEXT BLACK
#define MIN_GAME_BOARD_SIZE 3
#define MAX_GAME_BOARD_SIZE 25

//MENU SETTINGS---------------------------------------------------------------
//!--- Static menu ---!
#define MENU_BACKGROUND CYAN
#define MENU_TEXT BLACK

//DO NOT EDIT-----------------------------------------------------------------
#define CELL_WIDTH 3 //width of single character (3 to make it look better)
#define NAME_AND_ALBUM "Maciej Góralczyk 193302" //my name and student album number
#define IMPLEMENTED_FUNCTIONALITIES_STRING "Implemented functionalities:" //used later to calculate menu width
#define MENU_HEIGHT 24 //sets menu height (manually, beacuse it is dependantd of number of functionalities and controls