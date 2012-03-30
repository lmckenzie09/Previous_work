/**************************************************************************************************/


/**
 * File: main.c
 * Author: Lloyd Mckenzie
 * Date: 28 August 2011
 *
 * Description: Main function file for gosensei program. Directs calls to go.c functions and gives back errors if incorrect
 * arguments are given or if a file is misread
 *
 */

/**************************************************************************************************/

//header files
#include "global.h"
#include "go.h"
#include <stdio.h>
#include <string.h>

/**************************************************************************************************/

//allows to specify different command prompts easily
#define CMD1 "-eyes"
#define CMD2 "-twoeyes"
#define CMD3 "-eyespaces"

/**************************************************************************************************/



int
main(int argc, char *argv[])
{
    /**
     * check for the correct number of commandline arguments. If incorrect
     * provide a simple usage message to the assit the user
     */
	if( argc != 3 )
	{
		printf("\nUsage: %s [%s | %s | %s ] goboardfile \n\n", argv[0], CMD1, CMD2, CMD3);
        return -1;
	}
//initializing go board
    int column, row;
	char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE];

	for(row=0; row<GO_BOARD_SIZE; row++)
    {
        for(column=0; column<GO_BOARD_SIZE; column++)
        {
            go_board[row][column]='+';//initializing to a plus character
        }
    }
//assigning values from file to go board
	Bool read=read_go_board(argv[2], go_board);
//error message if file read was unsuccessful
	if(read==FALSE)
	{
        printf("\nGo file was not read correctly.\n\n");
        return -1;
    }
//shows complete go board
    display_go_board(go_board);

    int result=0;
//chooses which command to execute based on command line inputs,
// based on results, output line slightly differs
//to preserve grammer
    if(strcmp(argv[1], CMD1)==0)
    {
        result=determine_eyes_black(go_board);
        if(result==1)
            printf("\nThere is %i eye for black.", result);
        else
            printf("\nThere are %i eyes for black.", result);
        return 0;
    }

    else if(strcmp(argv[1], CMD2)==0)
    {
        result=determine_twoeyes_black(go_board);
        if(result==1)
            printf("\nThere is %i two eye for black.", result);
        else
            printf("\nThere are %i two eyes for black.", result);
        return 0;
    }

    else if(strcmp(argv[1], CMD3)==0)
    {

        result=determine_eyesspaces_black(go_board);
        if(result==1)
            printf("\nThere is %i eyespace for black.", result);
        else
            printf("\nThere are %i eyespaces for black.", result);
        return 0;
    }
//error statement if command is not recognized
    else
    {
        printf("\nDo not recognize command. Commands available: %s, %s, %s\n", CMD1, CMD2, CMD3);
        return -1;
    }
}
//end of program
/**************************************************************************************************/
