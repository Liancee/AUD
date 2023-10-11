#include <stdio.h>
#include <stdlib.h>
#include "../escapesequenzen.h"

void clearBuffer()
{
    char dummy;

    do
        scanf("%c", &dummy);
    while (dummy != '\n');
}

int askAgain()
{
    int res;
    char c;

    do
    {
        printf("Moechten Sie noch einmal (j/n)? ");
        res = scanf("%c", &c);
        if (c != '\n')
            clearBuffer();

        // If input is n/N program exits
        if (c == 'n' || c == 'N')
        {
            // printf("Programm wird beendet.\n");
            // exit(0);

            return 0;
        }
        // Inner while loop repeats since input is neither j/J nor n/N
        else if (c != 'j' && c != 'J')
            printf("Falsche Eingabe! Bitte 'j/J' oder 'n/N' eigeben!\n");

        // If input was j/J, main while loop will just repeat
    } while (res == 0 || (c != 'j' && c != 'J' && c != 'n' && c != 'N'));

    return 1;
}

int askAgainPos(int row, int col)
{
    int res;
    char c;

    POSITION(row, col);

    do
    {
        printf("Moechten Sie noch einmal (j/n)? ");
        res = scanf("%c", &c);
        if (c != '\n')
            clearBuffer();

        // If input is n/N program exits
        if (c == 'n' || c == 'N')
        {
            // printf("Programm wird beendet.\n");
            // exit(0);

            return 0;
        }
        // Inner while loop repeats since input is neither j/J nor n/N
        else if (c != 'j' && c != 'J')
            printf("Falsche Eingabe! Bitte 'j/J' oder 'n/N' eigeben!\n");

        // If input was j/J, main while loop will just repeat
    } while (res == 0 || (c != 'j' && c != 'J' && c != 'n' && c != 'N'));
    return 1;
}

void resetArray(int *a, int count)
{
    // While array has values != 0, set the current value to 0(*a = 0) and move the pointer to the next one afterwards (a++)
    // Note: "while (*a++ = 0)" not possible loop will stop because a = 0 (false) before moving pointer (a++)
    while (*a)
        *a++ = 0;
}

// NEW

void waitForEnter()
{
  char input;
  int result = -1;

  do
  {
    if (result != -1)
    {
      CLEAR_LINE;
    }

    printf("Bitte Eingabetaste drücken...");
    result = scanf("%c", &input);
  } while (input != '\n');
}

/**
 * Clears the current terminal output
 *
 * @returns void
 */
void clearScreen()
{
#ifdef _WIN32
  system("CLS");
#elif __linux__
  system("clear");
#else
  CLEAR;
#endif
}

/**
 * Determines if a given question was answered yes or no
 * @param char*: The question preceeding the input
 *
 * @returns 1 - user answered yes; 0 - user answered no
 */
int askYesOrNo(char *question)
{
  char input;
  int result = -1;

  do
  {
    if (result != -1)
    {
      CLEAR_LINE;
      UP_LINE;
      CLEAR_LINE;
    }

    printf("%s", question);
    result = scanf("%c", &input);

    if (input != '\n')
    {
      clearBuffer();
    }

    if (input == 'j' || input == 'J')
    {
      return 1;
    }

    if (input == 'n' || input == 'N')
    {
      return 0;
    }
  } while (result == 0 || (input != 'j' && input != 'J' && input != 'n' && input != 'N'));

  return 0;
}