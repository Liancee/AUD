#ifndef AUFGABE_1_DATETIME_H
#define AUFGABE_1_DATETIME_H

/***************************************************************************
 *  getDateFromString
 *  Checks if a given string contains a valid date or not.
 *  Parameter: input, date: the user input as string and the struct object to save it in if valid.
 *  Result: Returns 1=true when the string contained a date otherwise 0=false.
 ***************************************************************************/
int getDateFromString(char* input, sDate* date);

/***************************************************************************
 *  isDateValid
 *  Validates a date given as parameter.
 *  Parameter: date: pointer to the date struct with the set integer for day, month and year.
 *  Result: Returns 1=true if the date is valid otherwise 0=false.
 ***************************************************************************/
int isDateValid(sDate* date);

/***************************************************************************
 *  isLeapYear
 *  Checks if the given year is a leap year.
 *  Parameter: year: The year to be checked for if it is a leap year.
 *  Result: Returns 1 if it is a leap year otherwise 0.
 ***************************************************************************/
int isLeapYear(int year);

#endif //AUFGABE_1_DATETIME_H
