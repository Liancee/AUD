#ifndef DATETIME_H
#define DATETIME_H

#include "datastructure.h"

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

#endif // DATETIME_H
