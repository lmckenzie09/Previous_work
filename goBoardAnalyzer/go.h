/**************************************************************************************************/


/**
 * File: go.h
 * Author: Lloyd Mckenzie
 * Date: 28 August 2011
 *
 * Description: Header file for gosensei program
 *
 */

/**************************************************************************************************/


/**************************************************************************************************/


#ifndef GO_H
#define GO_H

/**************************************************************************************************/
//making a constant value to be used as size of board
enum { GO_BOARD_SIZE = 9 };

/***************************************************************************************************/

Bool read_go_board(char *, char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

void display_go_board(char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int determine_eyes_black(char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int determine_twoeyes_black(char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int determine_eyesspaces_black(char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

Bool doubledown(int, int, char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

Bool check_blank(int, int, char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int check_around(int, int);

Bool check_eyes(int, int, int, char [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int space_find(int [GO_BOARD_SIZE][GO_BOARD_SIZE]);

void bionic(char [GO_BOARD_SIZE][GO_BOARD_SIZE], int [GO_BOARD_SIZE][GO_BOARD_SIZE]);

int any_room(char [GO_BOARD_SIZE][GO_BOARD_SIZE], int, int);

void like_rabbits(char [GO_BOARD_SIZE][GO_BOARD_SIZE], int [GO_BOARD_SIZE][GO_BOARD_SIZE], int, int, int);

int valid_partofspace(char [GO_BOARD_SIZE][GO_BOARD_SIZE], int, int);

Bool roundabout(int [GO_BOARD_SIZE][GO_BOARD_SIZE], int);
/**************************************************************************************************/

#endif

/**************************************************************************************************/
