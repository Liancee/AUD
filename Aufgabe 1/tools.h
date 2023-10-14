#ifndef TOOLS_H
#define TOOLS_H

/***************************************************************************
 *  AskAgain
 *  Asks the user if the program should be closed or executed again in a specific row/column.
 *  Parameter: none
 *  Ergebnis : Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askAgain();

/***************************************************************************
 *  AskAgainPos
 *  Asks the user if the program should be closed or executed again in a specific row/column.
 *  Parameter: Row, Col: Row and column where the user question begins.
 *  Ergebnis: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askAgainPos(int Row, int Col);

/***************************************************************************
 *  askYesOrNo
 *  Asks the user a question passed as a parameter and takes an answer (yes/no)
 *  Parameter: question, a string that is output as a question on the screen.
 *  Ergebnis: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askYesOrNo(char *question);

/***************************************************************************
 *  clearScreen
 *  Clears the current terminal output.
 *  Parameter: none
 *  Ergebnis: void
 ***************************************************************************/
void clearScreen();

/***************************************************************************
 *  waitForEnter
 *  Awaits an enter keyboard input
 *  Parameter: none
 *  Ergebnis: void
 ***************************************************************************/
void waitForEnter();

/***************************************************************************
 *  clearBuffer
 *  Clears the buffer to the last '\n'
 *  Parameter: none
 *  Ergebnis: void
 ***************************************************************************/
void clearBuffer();

/***************************************************************************
 *  resetArray
 *  Resets all values in an array back to 0
 *  Parameter: a, count: Pointer to array which is to be nulled/reseted and length of the array.
 *  Ergebnis: void
 ***************************************************************************/
void resetArray(int *a, int count);

#endif // TOOLS_H
