#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "escapesequenzen.h"
#include "datetime.h"

int askAgainInternal();
void waitForEnter();

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int askAgain()
{
  int isInputValid = 1;

  do
  {
    if (!isInputValid)
    {
      printf("Invalid input! Please enter 'y/Y' or 'n/N' when prompted! ");
      waitForEnter();
    }
    isInputValid = askAgainInternal();
  } while (!isInputValid);
  return 1;
}

int askAgainPos(int row, int col)
{
  int isInputValid = 1;

  do
  {
    POSITION(row, col);
    if (!isInputValid)
    {
      printf("Invalid input! Please enter 'y/Y' or 'n/N' when prompted! ");
      waitForEnter();
      POSITION(row, col);
      printf("%-*s", 100, "");
      POSITION(row, col);
    }
    isInputValid = askAgainInternal();
  } while (!isInputValid);
  return 1;
}

int askAgainInternal()
{
  printf("Restart(y/n)?: ");

  char c = 0;
  int isInputValid = scanf("%c", &c);
  if (!isInputValid || (c != 'j' && c != 'J' && c != 'n' && c != 'N'))
  {
    clearBuffer();
    return 0;
  }
  else if (c == 'n' || c == 'N')
    exit(0);
  else if (c == 'y' || c == 'Y')
    return 1;
  else return 0; // we should never be here
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
  char c = 0;

  printf("Press Enter to continue ...");

  do
    scanf("%1c", &c);
  while (c != '\n');
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
  char c = 0;
  int isInputValid = 1;

  do
  {
    if (!isInputValid)
    {
      CLEAR_LINE;
      UP_LINE;
      CLEAR_LINE;
    }

    printf("%s", question);
    scanf("%c", &c);
    if (c != '\n')
      clearBuffer();

    if (c == 'n' || c == 'N')
      return 0;
    else if (c == 'y' || c == 'Y')
      return 1;
    else
    {
      printf("Invalid input! Please enter 'y/Y' or 'n/N' when prompted! ");
      waitForEnter();
      isInputValid = 0;
    }
  } while (!isInputValid);
}

void printLine(char c, int count)
{
  for (int i = 0; i < count; i++)
    printf("%c", c);

  fflush(stdout);
}

int GetText(char* prompt, int maxLen, char** text, int isEmptyInputAllowed)
{
  int isInputValid = 0, len;
  char format[15];
  if (maxLen <= 0 || !text)
    return 0;

  char* input = calloc(maxLen + 1, sizeof(char));
  if (!input)
    return 0;

  sprintf(format, "%%%i[^\n]", maxLen);

  PrintPrompt(prompt);
  STORE_POS;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("%-*s", maxLen + 1, "Enter text here."); // has to print at least 16 characters to override
    RESTORE_POS;
    FORECOLOR_WHITE;

    isInputValid = scanf(format, input);
    clearBuffer();

    RESTORE_POS;
    if (isInputValid)
    {
      len = strlen(input);
      if (len > 0)
      {
        *text = malloc(len + 1);
        if (*text)
        {
          strcpy(*text, input);
          printf("%-*s\n", maxLen + 1, input);
        }

      }
      else
      {
        if (!isEmptyInputAllowed) // why am I not getting here when only enter is pressed?
        {
          printf("Invalid input! Empty input is not allowed. ");
          waitForEnter();
          isInputValid = 0;
        }
      }
    }
    else
    {
      if (isEmptyInputAllowed)
      {
        printf("%*s\n", maxLen + 1, "");
        isInputValid = 1;
      }
    }
  } while (!isInputValid);
  free(input);
  return isInputValid;
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

void PrintNewLine(unsigned short count)
{
  while(count)
  {
    printf("\n");
    count--;
  }
}
