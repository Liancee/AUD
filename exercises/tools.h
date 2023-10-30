#ifndef TOOLS_H
#define TOOLS_H

/***************************************************************************
 *  askAgain
 *  Asks the user if the program should be closed or executed again in a specific row/column.
 *  Parameter: None
 *  Result: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askAgain();

/***************************************************************************
 *  askAgainPos
 *  Asks the user if the program should be closed or executed again in a specific row/column.
 *  Parameter: Row, Col: Row and column where the user question begins.
 *  Result: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askAgainPos(int Row, int Col);

/***************************************************************************
 *  askYesOrNo
 *  Asks the user a question passed as a parameter and takes an answer (yes/no)
 *  Parameter: question, a string that is output as a question on the screen.
 *  Result: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askYesOrNo(char *question);

/***************************************************************************
 *  clearScreen
 *  Clears the current terminal output.
 *  Parameter: None
 *  Result: void
 ***************************************************************************/
void clearScreen();

/***************************************************************************
 *  waitForEnter
 *  Awaits an enter keyboard input
 *  Parameter: None
 *  Result: void
 ***************************************************************************/
void waitForEnter();

/***************************************************************************
 *  clearBuffer
 *  Clears buffer til line break
 *  Parameter: None
 *  Result: void
 ***************************************************************************/
void clearBuffer();

/***************************************************************************
 *  resetArray
 *  Sets every value in an array to 0
 *  Parameter: a, count: Pointer to array which is to be nulled/reseted and
 *      length of the array.
 *  Result: void
 ***************************************************************************/
void resetArray(int *a, int count);

/***************************************************************************
 *  printLine
 *  Method that repeatedly prints a given character a number of given times
 *  Parameter: c, count: character [c] will be repeated [count] times
 *  Result: void
 ***************************************************************************/
void printLine(char c, int count);

#endif // TOOLS_H