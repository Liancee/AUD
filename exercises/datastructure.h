#ifndef AUFGABE_2_DATASTRUCTURE_H
#define AUFGABE_2_DATASTRUCTURE_H

enum eDayOfTheWeek;
//enum eDayOfTheWeek{NotADay, Mo, Tu, We, Th, Fr, Sa, Su};

typedef struct
{
    int Day, Month, Year;
    eDayOfTheWeek DayOfTheWeek;
} sDate;

typedef enum { NotADay, Mo, Tu, We, Th, Fr, Sa, Su } eDayOfTheWeek;
#endif //AUFGABE_2_DATASTRUCTURE_H