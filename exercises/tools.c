#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "escapesequenzen.h"
#include "datetime.h"

void CharReplace(char*, char, char);

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
      // printf("Program will exit now.\n");
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

void waitForEnter()
{
  char c;
  int res = -1;

  do
  {
    if (res != -1)
    {
      CLEAR_LINE;
    }

    printf("Press Enter to continue ...");
    res = scanf("%c", &c);
  } while (c != '\n');
}

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

int askYesOrNo(char *question)
{
  char c;
  int res = -1;

  do
  {
    if (res != -1)
    {
      CLEAR_LINE;
      UP_LINE;
      CLEAR_LINE;
    }

    printf("%s", question);
    res = scanf("%c", &c);
    if (c != '\n')
      clearBuffer();

    // If input is n/N program exits
    if (c == 'n' || c == 'N')
    {
      // printf("Program will exit now.\n");
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

void printLine(char c, int count)
{
  for (int i = 0; i < count; i++)
    printf("%c", c);

  fflush(stdout);
}

void GetText(char* prompt, int len, char* text, int isEmptyEntryAllowed)
{

  PrintPrompt(prompt);
  STORE_POS;

  int isInputValid = 0;
  char* input = calloc(len, sizeof(char));
  if (!input)
    return;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("%-*s", 160, "Enter text here.");
    RESTORE_POS;
    FORECOLOR_WHITE;
    isInputValid = scanf(" %99[^\n]", input); // reads til \n or 99 chars
    clearBuffer();

    if (isInputValid)
    {
      RESTORE_POS;
      if (!(!*input && !isEmptyEntryAllowed))
      {
        text = malloc(strlen(input));
        strcpy(text, input);

        printf("%-*s\n", 100, text);
      }
      else
      {
        printf("Entry is invalid! isEmptyEntryAllowed is 0 so there must be an entry of at least one character. ");
        waitForEnter();
      }
    }
  } while (!isInputValid || (!*input && !isEmptyEntryAllowed));
  free(input);
}

void CharReplace(char* input, char toBeReplaced, char replacement)
{
  int i;

  if (input == NULL)
    return;

  for (i = 0; input[i] != '\0'; i++)
    if (input[i] == toBeReplaced)
      input[i] = replacement;
}
