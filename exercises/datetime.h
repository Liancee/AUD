#ifndef DATETIME_H
#define DATETIME_H

#include "datastructure.h"

/***************************************************************************
 *  This module contains methods around common date related tasks
  such as parsing, input correctness, etc. which are used within exercises.
  Detailed information about each method and its arguments will be provided separately.
 ***************************************************************************/

/***************************************************************************
 *  isDateValid
 *  Validates a date given as parameter.
 *  Parameter:
 *      - day: user input for the day as integer that has to be validated.
 *      - month: user input for the month as integer that has to be validated.
 *      - year: user input for the year as integer that has to be validated.
 *  Result: Returns 1=true if the date is valid otherwise 0=false.
 ***************************************************************************/
int isDateValid(int day, int month, int year);

/***************************************************************************
 *  isLeapYear
 *  Checks if the given year is a leap year.
 *  Parameter:
 *      - year: the year to be checked for if it is a leap year.
 *  Result: Returns 1 if it is a leap year otherwise 0.
 ***************************************************************************/
int isLeapYear(int year);

/***************************************************************************
 *  GetDate
 *  Prompts the user for a time, then awaits user input and validates it
 *  until it is permissible.
 *  Parameter:
 *      - prompt: string with which the user is to be prompted with.
 *      - date: pointer to struct, where the validated user input is saved.
 *  Result: Returns 1 when everything went smoothly otherwise 0.
 ***************************************************************************/
int GetDate(char* prompt, sDate* date);

/***************************************************************************
 *  getDateFromString
 *  Checks if a given string contains a valid date or not.
 *  Parameter:
 *      - input: the user input as string that has to be validated.
 *      - date: pointer to the struct object to save it in if valid.
 *  Result: Returns 1=true when the string contained a date otherwise 0=false.
 ***************************************************************************/
int GetDateFromString(char *input, sDate *date);

/***************************************************************************
 *  GetTime
 *  Prompts the user for a date, then awaits user input and validates it
 *  until it is permissible.
 *  Parameter:
 *      - prompt: string with which the user is to be prompted with.
 *      - time: pointer to struct, where the validated user input is saved.
 *  Result: Returns 1 when everything went smoothly otherwise 0.
 ***************************************************************************/
int GetTime(char* prompt, sTime* time);

/***************************************************************************
 *  getTimeFromString
 *  Checks if a given string contains a valid time or not.
 *  Parameter:
 *      - input: the user input as string that has to be validated.
 *      - time: pointer to the struct object to save it in if valid.
 *  Result: Returns 1=true when the string contained a time otherwise 0=false.
 ***************************************************************************/
int GetTimeFromString(char* input, sTime* time);

/***************************************************************************
 *  getDayOfWeek
 *  Returns the day of the week as enum value (eDayOfTheWeek) for a given date.
 *  Parameter:
 *      - day: day of which the weekday is to be determined.
 *      - month: month of which the weekday is to be determined.
 *      - year: year of which the weekday is to be determined.
 *  Result: Returns the weekday of the given date as enum (eDayOfTheWeek). If
 *  for some reason the weekday could not be determined, the enum has a NotADay
 *  "default" value which would be set in such case.
 ***************************************************************************/
eDayOfTheWeek getDayOfWeek(int day, int month, int year);

void PrintPrompt(char* prompt);

#endif // DATETIME_H
