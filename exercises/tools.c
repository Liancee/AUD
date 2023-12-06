#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "escapesequenzen.h"
#include "datetime.h"

int askAgainInternal();

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void fclearBuffer(FILE * file)
{
  int c;
  while ((c = fgetc(file)) != '\n' && c != EOF);
}

int askAgain()
{
  int isInputValid = 1;

  do
  {
    if (!isInputValid)
    {
      printf("Invalid input! Please enter 'y/Y' or 'n/N' when prompted! ");
      waitForEnter("continue");
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
      waitForEnter("continue");
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

void waitForEnter(char * doWhat)
{
  char c = 0;

  printf("Press Enter to %s ...", doWhat);

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
      waitForEnter("continue");
      isInputValid = 0;
    }
  } while (!isInputValid);
  return 1; // not needed but necessary to compile on my unix machine; structure of this func is **** anyway
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
    return RaiseMallocException("input");

  sprintf(format, "%%%i[^\n]", maxLen);

  PrintPrompt(prompt);
  STORE_POS;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("Enter text here. (max. %i characters; Empty %s allowed)%-*s", maxLen, isEmptyInputAllowed ? "is" : "is not", 36, "");
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
          printf("%-*s\n", 100, input);
        }
        else
          return RaiseMallocException("*text");
      }
      else
      {
        if (!isEmptyInputAllowed)
        {
          printf("Invalid input! Empty input is not allowed. ");
          waitForEnter("continue");
          isInputValid = 0;
        }
        else
          isInputValid = 1;
      }
    }
    else
    {
      if (isEmptyInputAllowed)
      {
        printf("No %s set ...%*s\n", prompt, 60, "");
        isInputValid = 1;
      }
      else
      {
        printf("Invalid input! Empty input is not allowed. ");
        waitForEnter("continue");
        isInputValid = 0;
      }
    }
  } while (!isInputValid);
  free(input);
  input = NULL;
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

int RaiseMallocException(char * varName)
{
  fprintf(stderr, "Memory allocation of %s failed. Program will exit. ", varName);
  waitForEnter("continue");
  return 0;
}
