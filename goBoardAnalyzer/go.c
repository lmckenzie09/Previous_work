/**************************************************************************************************/


/**
 * File: go.c
 * Author: Lloyd Mckenzie
 * Date: 28 August 2011
 *
 * Description: File that holds all major functions in gosensei program. Functions to read go board,
 * display go board, analyze number of eyes, two eyes, and eye spaces along with all assorted
 * helper functions
 *
 */

/**************************************************************************************************/

//header files
#include "global.h"
#include "go.h"
#include <stdio.h>
#include <ctype.h>

/**************************************************************************************************/
//function that reads in data from file and then stores it in go_board array
//return is boolean since this function only wants to know if the function
//was succesful in grabbing and storing all data from the file
Bool read_go_board(char *inputFileName, char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    FILE *inputfile;

	inputfile=fopen(inputFileName, "r");
//error message for invalid file
	if(inputfile==NULL)
	{
	    printf("\n%s does not exist\n", inputFileName);
	    return FALSE;
	}
    char player, column, input[2];
    int row;
//reads through file
	while(!(feof(inputfile)))//checks for end of file
	{
	    fscanf(inputfile, "%c %c %i\n", &input[0], &input[1], &row);
	    player=tolower(input[0]);//changes all inputs to lowercase
	    column=tolower(input[1]);


	    //checks to see if inputs are valid
	    if(player!='b'&&player!='w')
	    {
	        printf("Invalid player token input. Valid player tokens: 'b' 'B' 'w' 'W'\n");
	        fclose(inputfile);
	        return FALSE;
	    }
	    if(!(column>='a'&&column<='i'))
	    {
	        printf("Invalid column entry\n");
	        fclose(inputfile);
	        return FALSE;
	    }
	    if(!(row>=1&&row<=9))
	    {
	        printf("Invalid row entry\n");
	        fclose(inputfile);
	        return FALSE;
	    }
//checks to see if there is already a player in a desired spot
        if((go_board[row-1][column-97])!='+')//subtraction used to make sure numbers are actually valid indicies
        {
            printf("Duplicate player token\n");
            fclose(inputfile);
            return FALSE;
        }
        //if no problems, place player token into array
	    go_board[row-1][column-97]=player;
	}
    fclose(inputfile);//close file
    return TRUE;
}

/**************************************************************************************************/
//function to display the go board to the screen
//row must be swapped since a goboard is shown with the highest row value at the top, with the lowest at the bottom
void
display_go_board(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{

    int column=0, row=GO_BOARD_SIZE, lines, spaces, i;//declare row to GBS to flip and display properly
    for(row=GO_BOARD_SIZE; row>0; row--)//goes from "bottom" of 2d array to "top"
    {
        //prints out row number
        if(row<10)//if else statement used so that board will still display properly if size is increased
            printf("%i ", (row));
        else
            printf("%i", (row));
        for(column=0, lines=1; column<GO_BOARD_SIZE; column++, lines++)
        {
            printf("%c", go_board[row-1][column]);//prints out character from array
            if(lines<GO_BOARD_SIZE)//properly spaces array outputs with '-' while not adding one at the end
            {
                printf("-");
            }

        }
        if(row>1)//makes sure vertical lines stay inside board and there are no extra lines under row 1
        {
            printf("\n  ");//adds spaces to line up correctly
            for(lines=0, spaces=1; lines<GO_BOARD_SIZE; lines++, spaces++)//starts spaces 1 count ahead to space properly
            {
                printf("%c", '|');
                if(spaces<GO_BOARD_SIZE)//makes sure it doesn't print an extra space
                {
                    printf(" ");
                }
                if(lines==(GO_BOARD_SIZE-1))//if this is the last iteration of the loop, print a new line
                {
                    printf("\n");
                }
            }
        }
    }
    printf("\n  ");
    for(i=0; i<GO_BOARD_SIZE; i++)//prints out column letters at bottom of board
    {
        printf("%c ", (i+65));
    }
    printf("\n");
}

/**************************************************************************************************/
//figures out how many eyes are in the go board and returns that number
int
determine_eyes_black(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int row=0, column=0, eyes=0;
    for(row=0; row<GO_BOARD_SIZE; row++)
    {
        for(column=0; column<GO_BOARD_SIZE; column++)
        {
            if(go_board[row][column]=='+')//goes through the go board and finds a blank space
            {
                if(check_blank(row, column, go_board))//calls function that will return true if the blank space is an eye
                {
                    eyes+=1;//increment eye count
                }
            }
        }
    }
    return eyes;//return eyes
}

/**************************************************************************************************/
//determines how many two eye structures there are in the go board
//borrows the helper functions used in determine eyes function
int
determine_twoeyes_black(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int twoeyes=0, row, column;
    for(row=0; row<GO_BOARD_SIZE; row++)
    {
        for(column=0; column<GO_BOARD_SIZE; column++)
        {
            if(go_board[row][column]=='+')//goes through and sees if there is a blank space
            {
                if(check_blank(row, column, go_board))//checks to see if there is an eye at that blank space
                {
                    if(doubledown(row, column, go_board))//now checks to see if there is an eye close enough to the eye found
                    {
                        twoeyes++;//if checks true, increment twoeyes
                    }
                }
            }
        }
    }
    return twoeyes/2;//returns twoeyes count. The reason we divide by two is because the twoeyes function will count a
    //two eye structure twice as a consequence of stepping through the array in a nested for loop
}

/**************************************************************************************************/
//Function that will return the number of eye spaces in a go board
int
determine_eyesspaces_black(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int i, j, eyespace=0;;
    int spaces[GO_BOARD_SIZE][GO_BOARD_SIZE];//makes and initializes a new 2d array
//this array is used to hold the 'properties' of each blank space.

    for(i=0; i<GO_BOARD_SIZE; i++)
    {
        for(j=0; j<GO_BOARD_SIZE; j++)
        {
            spaces[i][j]=0;//initializes all elements to zero
        }
    }
    bionic(go_board, spaces);//calls function bionic that eventually popoulates the spaces array with all necessary numbers
    eyespace=space_find(spaces);//space_find looks for proper eye spaces and will return an integer based on what it finds
    return eyespace;// we then return that int
}

/**************************************************************************************************/
//function that returns the number of seperate eye spaces
//spaces array now has Identities(numbers) for all spaces.
//If a group of numbers are completely surrounded by black pieces
//it's an eye space
int
space_find(int spaces[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int max=0, finder=0, i=0, j=0;
    for(i=0; i<GO_BOARD_SIZE; i++)//goes through spaces array
    {
        for(j=0; j<GO_BOARD_SIZE; j++)
        {
            if(spaces[i][j]>max)//If value has been marked as a potential eye space
            {
                if(roundabout(spaces, spaces[i][j]))//call function to check if it is a valid space
                {
                    finder++;//if so, move up counter
                }
                    max=spaces[i][j];//change max to number found so that you are looking for next possible eye space
            }
        }
    }
    return finder;
}
//function that goes through the board, and checks to see if the number given shows up enough times in the spaces array
//and is completely surrounded. If they are, return true- else return false
Bool
roundabout(int spaces[GO_BOARD_SIZE][GO_BOARD_SIZE], int check)
{
    int row, col, row_x, col_x;
    for(row=0; row<GO_BOARD_SIZE; row++)//goes through whole array
    {
        for(col=0; col<GO_BOARD_SIZE; col++)
        {
            if(spaces[row][col]==check)//if element in 2d array is the same number as check and thus part of the possible eye space
            {
                for(row_x=row-1; row_x<row+2; row_x++)//check 8 adjacent elements
                {
                    for(col_x=col-1; col_x<col+2; col_x++)
                    {
                        if(row_x>=0&&row_x<GO_BOARD_SIZE&&col_x>=0&&col_x<GO_BOARD_SIZE)//if valid
                        {
                            if(spaces[row_x][col_x]!=spaces[row][col])//if you encounter a different number
                            {
                                if(spaces[row_x][col_x]!=0)//and that number isn't zero
                                    return FALSE;//return false because that means the number you were checking isn't completely
                            }                    //surrounded
                        }
                    }
                }
            }
        }
    }
    return TRUE;//else return true
}

void
bionic(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE], int spaces[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int row=0, col=0, num=0, anyrcheck=0;

    for(row=0; row<GO_BOARD_SIZE; row++)//goes through every element in go_board
    {
        for(col=0; col<GO_BOARD_SIZE; col++)
        {
            if(go_board[row][col]=='+'&&spaces[row][col]==0)//if it finds a blank space AND it sees no saved state (number) in spaces
            {//goes in and checks to see if there is any empty space in a cardinal direction from it
                anyrcheck=any_room(go_board, row, col);
                if(anyrcheck==1)//if it finds one, up num which is used to have a seperate number for each seperate grouping
                {
                    num++;
                    like_rabbits(go_board, spaces, row, col, num);//calls a function that fills in all empty elements up-down
                    //left-right of the given coordinate with 'num'
                }
            }
        }
    }
}
//used to see if there is any blank element up-down left-right from the given element
int
any_room(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE], int row, int col)
{
    int hope=0, row_x, col_x;
    for(row_x=row; row_x<row+2; row_x++)//goes around all adjacent points
    {
        for(col_x=col; col_x<col+2; col_x++)
        {
            if((row_x!=row||col_x!=col)&&row_x>=0&&row_x<GO_BOARD_SIZE&&col_x>=0&&col_x<GO_BOARD_SIZE)//checks to see if space is valid
            {
                if(go_board[row_x][col_x]=='w')//if it's a 'w' return -1
                {
                    hope=-1;
                    return hope;
                }
                if(row_x==row)// if you're to the left/right of element
                {
                    if(go_board[row_x][col_x]=='+')//and you're empty
                    {
                        hope=1;//store 1
                    }
                }
                if(col_x==col)//if up/down
                {
                    if(go_board[row_x][col_x]=='+')//and empty
                    {
                        hope=1;//store 1
                    }
                }
            }
        }
    }
    return hope;//return value stored
}
//function used to populate validly connected empty elements. this is a recursive function
void
like_rabbits(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE], int spaces[GO_BOARD_SIZE][GO_BOARD_SIZE], int row, int col, int num)
{
    int valid=0;
    if(row>=0&&row<GO_BOARD_SIZE&&col>=0&&col<GO_BOARD_SIZE)//checks for valid space
    {
        if(go_board[row][col]=='b')//if element is a 'b', return
            return;
        if(go_board[row][col]=='w')//if a 'w', mark it on the spaces array then return
        {
           spaces[row][col]=-1;
            return;
        }
        if(go_board[row][col]=='+'&&spaces[row][col]==0)//if empty and has not been marked in spaces
        {
            valid=valid_partofspace(go_board, row, col);//first checks to see if this space has any 'w's around it
            if(valid==-1)
            {
                spaces[row][col]=-1;//if it does, mark it as a -1 as well
                return;
            }
            if(valid==1)
            {
                spaces[row][col]=num;//else, mark element as num
            }
        like_rabbits(go_board, spaces, row, col+1, num);//recursively calls through all directions to visit all places on the board
        like_rabbits(go_board, spaces, row+1, col, num);
        like_rabbits(go_board, spaces, row, col-1, num);
        like_rabbits(go_board, spaces, row-1, col, num);
        }
    }
}
//makes sure there is not a 'w' in the vicinity of the element in question
int
valid_partofspace(char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE], int row, int col)
{
    int row_x, col_x, check=0;
    for(row_x=row-1; row_x<row+2; row_x++)
    {
        for(col_x=col-1; col_x<col+2; col_x++)
        {
            if((row_x!=row||col_x!=col)&&row_x>=0&&row_x<GO_BOARD_SIZE&&col_x>=0&&col_x<GO_BOARD_SIZE)
            {
                if(go_board[row_x][col_x]=='w')
                {
                    return -1;
                }
                if(row_x==row||col_x==col)
                {
                    if(go_board[row_x][col_x]=='+')
                    {
                        check=1;
                    }
                }
            }
        }
    }
    if(check>0)
        return check;
    else
        return 0;

}

//function that takes original eye and checks to see if there is an eye close enough to count as a two eye structure
Bool
doubledown(int row, int column, char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int row_x, col_x;
    for(row_x=row-2; row_x<row+3; row_x++)//steps through the spaces around the given space with a radius of two spaces
    {
        for(col_x=column-2; col_x<column+3; col_x++)
        {
            if((row_x>=0&&row_x<GO_BOARD_SIZE)&&//makes sure that the point is inside the board
               (col_x>=0&&col_x<GO_BOARD_SIZE))
            {
                if(go_board[row_x][col_x]=='+')//if the point is an empty space...
                {
                    if(check_blank(row_x, col_x, go_board))//check to see if its an eye
                        return TRUE;
                }
            }
        }
    }
    return FALSE;//else return false
}


/*************************************************************************************************/
//checks to see if there is an eye at the specified array element
Bool
check_blank(int row, int column, char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int adj;
    adj=check_around(row, column);//gathers how many valid adjacent points are around the specified point
    if(check_eyes(row, column, adj, go_board))//checks if there is an eye
    {
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************************************/

int//checks how many valid adjacent places are around the specified blank space
check_around(int row, int column)
{//if specified point is in a corner, returns 3, on the side return 5, else return 8
    if((row==0&&column==0)||
       (row==(GO_BOARD_SIZE-1)&&column==0)||
       (row==0&&column==(GO_BOARD_SIZE-1))||
       (row==(GO_BOARD_SIZE-1)&&column==(GO_BOARD_SIZE-1)))
       {
           return 3;
       }
    if(row==0||column==0||row==(GO_BOARD_SIZE-1)||column==(GO_BOARD_SIZE-1))
    {
        return 5;
    }
    else
        return 8;
}

/******************************************************************************************************/
//Actually confirms if an eye is at this designated place or not
Bool
check_eyes(int row, int column, int adj, char go_board[GO_BOARD_SIZE][GO_BOARD_SIZE])
{
    int cross_check=0, row_x, col_x;
    //checks how many valid adjacent points around specified area, then determines the number of
    //valid elements are in the cardinal directions
    if(adj==3)
        cross_check=2;
    if(adj==5)
        cross_check=3;
    if(adj==8)
        cross_check=4;
    //loops through all points surrounding
    for(row_x=row-1; row_x<row+2; row_x++)
    {
        for(col_x=column-1; col_x<column+2; col_x++)
        {
            //if test point is valid
            if((row_x>=0&&row_x<(GO_BOARD_SIZE))&&
               (col_x>=0&&col_x<(GO_BOARD_SIZE))&&
               (row_x!=row||col_x!=column))
            {
                //and if it holds a 'b'
                if(go_board[row_x][col_x]=='b')
                {
                    //first check to see if its on a cardinal direction or not and keep note accordingly
                    if((row_x==row&&(col_x!=column))||(col_x==column&&(row_x!=row)))
                    {
                        cross_check--;
                    }
                    adj--;
                }
            }
        }
    }
    //if you do not have enough 'b's in the cardinal directions and adjacent, return false, else return true
    if(cross_check!=0||adj>1)
    {
        return FALSE;
    }
    else
        return TRUE;
}

