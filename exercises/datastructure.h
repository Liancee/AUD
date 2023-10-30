#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXAPPOINTMENTS 100

extern int CountAppointments;

typedef enum
{
    NotADay,
    Mo,
    Tu,
    We,
    Th,
    Fr,
    Sa,
    Su
} eDayOfTheWeek;

typedef struct
{
    int Day, Month, Year;
    eDayOfTheWeek DayOfTheWeek;
} sDate;

typedef struct
{
    int Hours, Minutes, Seconds;
} sTime;

typedef struct
{
    sDate Date;
    sTime Time;
    char *Location;
    sTime *Duration;
} sAppointment;

extern sAppointment Calendar[];

#endif // DATASTRUCTURE_H