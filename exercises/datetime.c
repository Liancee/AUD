#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

void GetDate(char* prompt, sDate* date)
{

}

void GetTime(char* prompt, sTime* time)
{

}

int isLeapYear(int year)
{
  //dividable by 4, not by 100 but by 400
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int isDateValid(int day, int month, int year)
{
  // Check for valid date even when it is a leap year
  // Check if the day, month, and year are within valid ranges
  if (day < 1 || month < 1 || month > 12 || year < 0)
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

int getDateFromString(char* input, sDate* date)
{
  // parse into individual ints so we can save them in sDate else we return 0 (false)
  char* pDay = input;
  char* pMonth = 0;
  char* pYear = 0;

  int day = 0, month = 0, year = 0;

  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  pMonth = ++input;

  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  pYear = ++input;

  day = atoi(pDay);
  month = atoi(pMonth);
  year = atoi(pYear);

  if(isDateValid(day, month, year))
  {
    date->Day = day;
    date->Month = month;
    date->Year = year;

    return 1;
  }

  return 0;
}