#ifndef TOOLS_H
#define TOOLS_H

/***************************************************************************
 *  This module contains various methods and/or definitions which are used within exercises.
  Detailed information about each method and its arguments will be provided separately.
 ***************************************************************************/

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
 *  Parameter:
 *      - Row: row where the user question begins.
 *      - Col: column where the user question begins.
 *  Result: Returns a one if the user input was a j/J and a 0 if it was an n/N.
 ***************************************************************************/
int askAgainPos(int Row, int Col);

/***************************************************************************
 *  askYesOrNo
 *  Asks the user a question passed as a parameter and takes an answer (yes/no)
 *  Parameter:
 *      - question: a string that is output as a question on the screen.
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
 *  Parameter:
 *      - a: Pointer to array which is to be nulled/reseted.
 *      - count: length of array.
 *  Result: void
 ***************************************************************************/
void resetArray(int *a, int count);

/***************************************************************************
 *  printLine
 *  Method that repeatedly prints a given character a number of given times
 *  Parameter:
 *      - c: character to be printed given times
 *      - count: the given character will be printed [count] times
 *  Result: void
 ***************************************************************************/
void printLine(char c, int count);

/***************************************************************************
 *  GetText
 *  Gets a user input of a certain maxLen after sending the user a prompt.
 *  Parameter:
 *      - prompt: is printed to the user.
 *      - maxLen: max. count of chars the user can input.
 *      - text: is the address where the final user input is saved to.
 *      - isEmptyInputAllowed: determines if the user is allowed to input
 *      nothing.
 *  Result: Returns 1 when everything went smoothly otherwise 0.
 ***************************************************************************/
int GetText(char* prompt, int maxLen, char** text, int isEmptyInputAllowed);

/***************************************************************************
 *  PrintNewLine
 *  Prints new lines as many times as the given parameter
 *  Parameter:
 *      - count: how many new lines should be printed.
 *  Result: void
 ***************************************************************************/
void PrintNewLine(unsigned short count);

#endif // TOOLS_H
