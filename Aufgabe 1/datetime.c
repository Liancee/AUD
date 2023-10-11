#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

int isLeapYear(int year)
{
  //durch 4 teilbar, nicht durch 100 aber durch 400
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int isDateValid(int day, int month, int year)
{
  // Gucken ob es ein legitimes Datum ist, auch wenn Schaltjahr
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
  // in einzelne ints parsen und in sDate speichern sonst falsch wieder geben
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