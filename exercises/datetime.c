#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "escapesequenzen.h"
#include "tools.h"

// function declarations
void PrintPrompt(char*);
int getDateFromString(char*, sDate*);
int isDateValid(int, int, int);
int isLeapYear(int);
eDayOfTheWeek getDayOfWeek(sDate*);
int getTimeFromString(char*, sTime*);
int isTimeValid(int, int, int);


void GetDate(char* prompt, sDate* date)
{
  PrintPrompt(prompt);
  STORE_POS;

  int scanRes = 0, isDateValid = 0;
  char* input = malloc(20);
  if (!input)
      return;


  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("%-*s", 50, "dd.mm.yyyy");
    RESTORE_POS;
    FORECOLOR_WHITE;
    scanRes = scanf("%19[^\n]", input);
    clearBuffer();

    if (scanRes)
    {
      isDateValid = getDateFromString(input, date);
      RESTORE_POS;
      if (isDateValid)
        printf("%02i.%02i.%04i\n", date->Day, date->Month, date->Year);
      else
      {
        printf("Date is invalid! ");
        waitForEnter();
      }
    }
  } while (!scanRes || !isDateValid);
}

void PrintPrompt(char* prompt)
{
  printf("  %-12s: ", prompt);
}

int getDateFromString(char* input, sDate* date)
{
  char* pDay = input;
  char* pMonth = 0;
  char* pYear = 0;

  int day = 0, month = 0, year = 0;

  // dd.mm.yyyy set pointer to first '.' cuz right after starts the month
  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  // set month pointer
  pMonth = ++input;

  // as above set pointer to second '.' cuz right after starts the year
  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  // set year pointer
  pYear = ++input;

  // parse strings to ints
  day = atoi(pDay);
  month = atoi(pMonth);
  year = atoi(pYear);

  // set the struct values with our variables if they are valid and return 1 else return 0
  if(isDateValid(day, month, year))
  {
    date->Day = day;
    date->Month = month;
    date->Year = year;
    date->DayOfTheWeek = getDayOfWeek(date);

    return 1;
  }
  return 0;
}

int isDateValid(int day, int month, int year)
{
  // Check for valid date even when it is a leap year
  // Check if the day, month, and year are within valid ranges
  if (day < 1 || month < 1 || month > 12 || year < 0 || year > 9999)
    return 0;

  if (month == 2) {
    if (isLeapYear(year) && day > 29)
      return 0;
    if (!isLeapYear(year) && day > 28)
      return 0;
  } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return 0;

  return 1;
}

int isLeapYear(int year)
{
  //dividable by 4, not by 100 but by 400
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

eDayOfTheWeek getDayOfWeek(sDate* date)
{
  if (date->Month < 3)
  {
    date->Month += 12;
    date->Year--;
  }

  int h = (date->Day + 2 * date->Month + 3 * (date->Month + 1) / 5 + date->Year + date->Year / 4 - date->Year / 100 + date->Year / 400) % 7;

  switch (h) {
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


void GetTime(char* prompt, sTime* time)
{
  PrintPrompt(prompt);
  STORE_POS;

  int scanRes = 0, isTimeValid = 0;
  char* input = malloc(20);
  if (!input)
    return;

  do
  {
    RESTORE_POS;
    FORECOLOR_YELLOW;
    printf("%-*s", 50, "hh:mm[:ss]");
    RESTORE_POS;
    FORECOLOR_WHITE;
    scanRes = scanf("%19[^\n]", input);
    clearBuffer();

    if (scanRes)
    {
      // TODO: empty input should also be allowed => NULL Pointer
      isTimeValid = getTimeFromString(input, time);
      RESTORE_POS;
      if (isTimeValid)
        if(!time->Seconds)
          printf("%02i:%02i     \n", time->Hours, time->Minutes);
        else printf("%02i:%02i:%02i  \n", time->Hours, time->Minutes, time->Seconds);
      else
      {
        printf("Time is invalid! Note that seconds are [optional] (hh:mm or hh:mm:ss). ");
        waitForEnter();
      }
    }
  } while (!scanRes || !isTimeValid);
  free(input);
}

int getTimeFromString(char* input, sTime* time)
{
  char* pHour = input;
  char* pMin = 0;
  char* pSec = 0;

  int hour = 0, min = 0, sec = 0;

  // hh:mm[:ss] set pointer to first ':' cuz right after start the minutes
  while(*input != ':')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  // set minute pointer
  pMin = ++input;

  // as above set pointer to second ':' cuz right after start the year
  while(*input != ':')
  {
    if(*input == '\0')
      break;
    input++;
  }
  // if specified set seconds pointer and parse it to int
  if(*input != '\0')
  {
    pSec = ++input;
    sec = atoi(pSec);
  }

  // parse strings to ints
  hour = atoi(pHour);
  min = atoi(pMin);


  // set the struct values with our variables if they are valid and return 1 else return 0
  if(isTimeValid(hour, min, sec))
  {
    time->Hours = hour;
    time->Minutes = min;
    if (sec)
      time->Seconds = sec;

    return 1;
  }
  return 0;
}

// Check if the hour, month, and Sec are within valid ranges
int isTimeValid(int hour, int min, int sec)
{
  return (hour >= 0 && (min >= 0 && min < 60) && (sec >= 0 && sec < 60));
}
