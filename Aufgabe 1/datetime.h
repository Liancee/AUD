#ifndef AUFGABE_1_DATETIME_H
#define AUFGABE_1_DATETIME_H

/***************************************************************************
 *  getDateFromString
 *  Fragt den Benutzer ob das Programm geschlossen oder erneut ausgefuehrt werden soll
 *  Parameter: input, date: Der eingegebe String vom Benutzer und unser Struct Object
 *  Ergebnis : ...
 ***************************************************************************/
int getDateFromString(char* input, sDate* date);

/***************************************************************************
 *  isDateValid
 *  Fragt den Benutzer ob das Programm geschlossen oder erneut ausgefuehrt werden soll
 *  Parameter: input, date: Der eingegebe String vom Benutzer und unser Struct Object
 *  Ergebnis : ...
 ***************************************************************************/
int isDateValid(int day, int month, int year);

/***************************************************************************
 *  isLeapYear
 *  Fragt den Benutzer ob das Programm geschlossen oder erneut ausgefuehrt werden soll
 *  Parameter: input, date: Der eingegebe String vom Benutzer und unser Struct Object
 *  Ergebnis : ...
 ***************************************************************************/
int isLeapYear(int year);

#endif //AUFGABE_1_DATETIME_H
