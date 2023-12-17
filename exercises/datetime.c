#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"
#include "datastructure.h"
#include "escapesequenzen.h"
#include "tools.h"

// function declarations
int isTimeValid(int, int, int);

int GetDate(char * prompt, sDate * date)
{
  if (!date)
  {
    fprintf(stderr, "Given parameter sDate* is NULL. Program will exit. ");
    return 0;
  }

  int isInputValid = 0, isDateValid = 0;
  char * input = calloc(1, sizeof("dd.mm.yyyy"));
  if (!input) return RaiseMallocException("input");

  PrintPrompt(prompt);
  STORE_POS;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("%-*s", 50, "dd.mm.yyyy (Empty is not allowed)");
    RESTORE_POS;
    FORECOLOR_WHITE;
    isInputValid = scanf("%11[^\n]", input);
    clearBuffer();

    if (isInputValid)
    {
      isDateValid = GetDateFromString(input, date);
      RESTORE_POS;
      if (isDateValid) printf("%02i.%02i.%04i%*s\n", date->Day, date->Month, date->Year, 50, "");
      else
      {
        printf("Date is invalid! ");
        waitForEnter("continue");
      }
    }
  } while (!isInputValid || !isDateValid);

  free(input);
  input = NULL;

  return 1;
}

void PrintPrompt(char * prompt)
{
  printf("  %-12s: ", prompt);
}

int GetDateFromString(char * input, sDate * date)
{
  char * pDay = input;
  char * pMonth = 0;
  char * pYear = 0;

  int day = 0, month = 0, year = 0;

  // dd.mm.yyyy set pointer to first '.' cuz right after starts the month
  while (*input != '.')
  {
    if (*input == '\0') return 0;
    input++;
  }

  // set month pointer
  pMonth = ++input;

  // as above set pointer to second '.' cuz right after starts the year
  while (*input != '.')
  {
    if (*input == '\0') return 0;
    input++;
  }

  // set year pointer
  pYear = ++input;

  // parse strings to ints
  day = atoi(pDay);
  month = atoi(pMonth);
  year = atoi(pYear);

  // set the struct values with our variables if they are valid and return 1 else return 0
  if (isDateValid(day, month, year))
  {
    date->Day = day;
    date->Month = month;
    date->Year = year;
    date->DayOfTheWeek = getDayOfWeek(day, month, year);

    return 1;
  }
  return 0;
}

int isDateValid(int day, int month, int year)
{
  // Check for valid date even when it is a leap year
  // Check if the day, month, and year are within valid ranges
  if (day < 1 || month < 1 || month > 12 || year < 0 || year > 9999) return 0;

  if (month == 2)
  {
    if (isLeapYear(year) && day > 29) return 0;
    if (!isLeapYear(year) && day > 28) return 0;
  } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;

  return 1;
}

int isLeapYear(int year)
{
  //dividable by 4, not by 100 but by 400
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

eDayOfTheWeek getDayOfWeek(int day, int month, int year)
{
  if (month < 3)
  {
    month += 12;
    year--;
  }

  int h = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;

  switch (h)
  {
    case 0: return Mo;
    case 1: return Tu;
    case 2: return We;
    case 3: return Th;
    case 4: return Fr;
    case 5: return Sa;
    case 6: return Su;
    default: return NotADay; // Error
  }
}


int GetTime(char * prompt, sTime * time, unsigned short isEmptyInputAllowed)
{
  // if (!time) return RaiseMallocException("time");

  int isInputValid = 0, isTimeValid = 0;
  char * input = calloc(sizeof("hh:mm:ss"), sizeof(char));
  if (!input) return RaiseMallocException("input");

  PrintPrompt(prompt);
  STORE_POS;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("hh:mm[:ss] (Empty %s allowed)%-*s", isEmptyInputAllowed ? "is" : "is not", 66, "");
    RESTORE_POS;
    FORECOLOR_WHITE;
    isInputValid = scanf("%8[^\n]", input);
    clearBuffer();

    if (isInputValid)
    {
      isTimeValid = GetTimeFromString(input, time);
      RESTORE_POS;
      if (isTimeValid)
      {
        if (time->Seconds == -1) printf("%02i:%02i%*s\n", time->Hours, time->Minutes, 50, "");
        else printf("%02i:%02i:%02i%*s\n", time->Hours, time->Minutes, time->Seconds, 50, "");
      }
      else
      {
        printf("Time is invalid! Note that seconds are [optional] (hh:mm or hh:mm:ss). ");
        waitForEnter("continue");
      }
    }
    else
    {
      RESTORE_POS;
      if (isEmptyInputAllowed)
      {
        time->Hours = 255; // user input was allowedly empty
        printf("No %s set ...%*s\n", prompt, 60, "");
        isInputValid = 1;
        isTimeValid = 1;
      }
      else
      {
        printf("Invalid input! Empty input is not allowed. ");
        waitForEnter("continue");
        isInputValid = 0;
      }
    }
  } while (!isInputValid || !isTimeValid);

  free(input);
  input = NULL;

  return 1;
}

int GetTimeFromString(char * input, sTime * time)
{
  char * pHour = input;
  char * pMin = NULL;
  char * pSec = NULL;

  int hour = 0, min = 0, sec = -1;

  // hh:mm[:ss] set pointer to first ':' cuz right after start the minutes
  while (*input != ':')
  {
    if (*input == '\0') return 0;
    input++;
  }

  // set minute pointer
  pMin = ++input;

  // as above set pointer to second ':' cuz right after start the seconds
  while (*input != ':')
  {
    if (*input == '\0') break;
    input++;
  }

  // if specified set seconds pointer and parse it to int
  if (*input != '\0')
  {
    pSec = ++input;
    sec = atoi(pSec);
  }

  // parse strings to ints
  hour = atoi(pHour);
  min = atoi(pMin);


  // set the struct values with our variables if they are valid and return 1 else return 0
  if (isTimeValid(hour, min, sec))
  {
    /*sTime t;
    t.Hours = hour;
    t.Minutes = min;
    t.Seconds = sec;
    *time = t;*/
    //time = &t; // TODO ask why this not work is it now equivalent to the line before

    time->Hours = hour;
    time->Minutes = min;
    time->Seconds = sec;

    return 1;
  }
  return 0;
}

// Check if the hour, month, and Sec are within valid ranges
int isTimeValid(int hour, int min, int sec)
{
  return ((hour >= 0 && hour < 24) && (min >= 0 && min < 60) && (sec >= -1 && sec < 60));
}
