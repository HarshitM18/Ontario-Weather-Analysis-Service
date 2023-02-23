////////////////////////////////////////////////////////
/*
*****************************************************************************
                              Reflection
                             Final Assessment
Full Name  : Harshit Gupta, Daiki Nagashima, Cheuk Lung Li
Student ID#: 157860214 , 113066211 , 149507212
Email      : hgupta16@myseneca.ca , dnagashima@myseneca.ca , cli259@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*/
////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//                      HELPER FUNCTIONS                        //
//////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

//////call hearder file
#include "helper.h"

//call library
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

//clearInputBuffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

//pause
void suspend(void)
{
    printf("< Press [ENTER] key to continue >");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//prompt integer input
int inputInt(void)
{
    // Made according to flowchart and variable names taken directly from the ms1 pdf
    char newLine = '\0';
    int value = 0;
    do
    {
        scanf(" %d%c", &value, &newLine);
        if (newLine == '\n')
        {
            ;
        }
        else
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (newLine != '\n');
    return value;
}

//prompt integer input within a range
int inputIntRange(int lowBound, int upBound)
{
    int value = 0, valid = 0;
    do
    {
        value = inputInt();
        if (value >= lowBound && value <= upBound)
        {
            ;
        }
        else
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowBound, upBound);
        }
        valid = (value < lowBound || value > upBound);
    } while (valid);
    return value;
}