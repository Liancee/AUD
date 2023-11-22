#ifndef DATETIME_H
#define DATETIME_H

#include "datastructure.h"

/***************************************************************************
 *  This module contains methods around common date related tasks
  such as parsing, input correctness, etc. which are used within exercises.
  Detailed information about each method and its arguments will be provided separately.
 ***************************************************************************/

/***************************************************************************
 *  getDateFromString
 *  Checks if a given string contains a valid date or not.
 *  Parameter: input, date: the user input as string and the struct object to save it in if valid.
 *  Result: Returns 1=true when the string contained a date otherwise 0=false.
 ***************************************************************************/
int getDateFromString(char *input, sDate *date);

/***************************************************************************
 *  isDateValid
 *  Validates a date given as parameter.
 *  Parameter: day, month, year: Individual integers for day, month & year.
 *  Result: Returns 1=true if the date is valid otherwise 0=false.
 ***************************************************************************/
int isDateValid(int day, int month, int year);

/***************************************************************************
 *  isLeapYear
 *  Checks if the given year is a leap year.
 *  Parameter: year: The year to be checked for if it is a leap year.
 *  Result: Returns 1 if it is a leap year otherwise 0.
 ***************************************************************************/
int isLeapYear(int year);

/***************************************************************************
 *  GetDate
 *  short description
 *  Parameter:
 *  Result:
 ***************************************************************************/
void GetDate(char* prompt, sDate* date);

/***************************************************************************
 *  GetTime
 *  short description
 *  Parameter:
 *  Result:
 ***************************************************************************/
void GetTime(char* prompt, sTime* time);

#endif // DATETIME_H
