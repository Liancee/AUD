#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

int isLeapYear(int year)
{
  // it is a leap year if it is dividable by 4 and not by 100 but 400
  return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int isDateValid(sDate* date)
{
  // filtering out obvious wrong inputs in days, month and year
  if ((*date).Day < 1 || (*date).Day > 31 ||(*date).Month < 1 || (*date).Month > 12 || (*date).Year < 0)
    return 0;

  // if february and depended on leap year check if the day is out of bounds
  if ((*date).Month == 2) {
    if (isLeapYear((*date).Year) && (*date).Day > 29) // if it is a leap year there cannot be more than 29 days in february
      return 0;
    if (!isLeapYear((*date).Year) && (*date).Day > 28) // if it is not a leap year there cannot be more than 28 days in february
      return 0;
  } else if (((*date).Month == 4 || (*date).Month == 6 || (*date).Month == 9 || (*date).Month == 11) && (*date).Day > 30) // checks if the input month has only 30 days but the input days are 31
      return 0;

  return 1;
}

int getDateFromString(char* input, sDate* date)
{
  char* pDay = input; // the day should begin at the start of the input string, so we set the day pointer to the beginning of the input
  char* pMonth = 0;
  char* pYear = 0;

  // we add 1 to our input pointer as long as there is no '.' which separates day, month and year
  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }
  // when we arrived at the dot we add 1 one again, so we are behind the dot on the start of the month and set our month pointer there as well
  pMonth = ++input;

  // works exactly like above only for the year
  while(*input != '.')
  {
    if(*input == '\0')
      return 0;
    input++;
  }

  pYear = ++input;

  // we parse our integers and set them in the struct
  date->Day = atoi(pDay);
  date->Month = atoi(pMonth);
  date->Year = atoi(pYear);

  // we give the address of the struct to a method which checks if the date is valid
  return isDateValid(date);
}