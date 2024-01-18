#ifndef DATASTRUCTURE_H
  #define DATASTRUCTURE_H

  /***************************************************************************
   *  This module contains various data structures, enumerations.
   ***************************************************************************/

  #define MAXINDEX 307

  extern int AppointmentCount;

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

  typedef struct sApp
  {
    sDate Date;
    sTime Time;
    char * Description;
    char * Location;
    sTime * Duration;
    struct sApp * Next;
    struct sApp * Previous;
  } sAppointment;

  extern sAppointment *First, *Last;

  typedef struct sLE
  {
    sAppointment * Appointment;
    struct sLE * Next;
  } sListEntry;

  typedef struct
  {
    sListEntry * First, * Last;
  } sHashEntry;

  extern sHashEntry HashTable[MAXINDEX];

#endif // DATASTRUCTURE_H
