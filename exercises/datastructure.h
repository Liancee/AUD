#ifndef DATASTRUCTURE_H
  #define DATASTRUCTURE_H

  /***************************************************************************
   *  This module contains various data structures, enumerations.
   ***************************************************************************/

  #define MAXAPPOINTMENTS 100

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

  typedef struct
  {
      sDate Date;
      sTime Time;
      char* Description;
      char* Location;
      sTime* Duration;
  } sAppointment;

  extern sAppointment Calendar[];

#endif // DATASTRUCTURE_H
