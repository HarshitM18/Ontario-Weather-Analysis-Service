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
*****************************************************************************
*/
////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//                      HELPER FUNCTIONS                        //
//////////////////////////////////////////////////////////////////
// SAFE-GUARD: 
#ifndef helper_h
#define helper_h


//clearInputBuffer
void clearInputBuffer(void);

//pause
void suspend(void);

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////


//prompt integer input
int inputInt(void);

//prompt integer input within a range
int inputIntRange(int, int);


#endif//  !helper_h