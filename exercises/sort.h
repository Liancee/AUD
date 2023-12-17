#ifndef EXERCISES_SORT_H
  #define EXERCISES_SORT_H
  #include "datastructure.h"

/***************************************************************************
 *  This module contains methods for specifying in which way the appointments
 *  should be sorted. The only real sorting method for now is quick sort.
 * Detailed information about each method and its arguments will be provided seperately.
 ***************************************************************************/

  /***************************************************************************
   *  Quick_sort
   *  An algorithm to sort the appointments in the calendar in a certain way,
   *      specified by the Sort_* methods below.
   *  Parameter:
   *      - calendar: the calendar that holds all the appointments
   *      - count: the amount of appointments saved in calendar
   *      - (*cmp_method): the sorting specifier (a Sort_* method from below)
   *  Result: void
   ***************************************************************************/
  void Quick_sort(sAppointment * calendar, int count, int (*cmp_method)(sAppointment *, sAppointment *));

  /***************************************************************************
   *  Sort_date_time
   *  A method that specifies in which way the appointments are to be sorted.
   *      This method is given as parameter (function pointer) and called
   *      multiple times by the sort method itself to compare two appointments.
   *      In this case the appointments are first checked for differences in date,
   *      then if necessary in time and if still equivalent 0(equality) is returned
   *      and the while loop continues.
   *  Parameter:
   *      - app1: the first appointments that is to compared to the other one
   *      - app2: the other appointment, that is compared to the first one
   *  Result: Returns -1 if the sort field of the first appointment is smaller
   *      than the second one, 0 if equal and -1 if greater.
   ***************************************************************************/
  int Sort_date_time(sAppointment * app1, sAppointment * app2);

  /***************************************************************************
   *  Sort_description
   *  A method that specifies in which way the appointments are to be sorted.
   *      This method is given as parameter (function pointer) and called
   *      multiple times by the sort method itself to compare two appointments.
   *      In this case the appointments are first checked for differences in their
   *      description then if necessary in date, then time and if still equivalent
   *      0(equality) is returned and the while loop continues.
   *  Parameter:
   *      - app1: the first appointments that is to compared to the other one
   *      - app2: the other appointment, that is compared to the first one
   *  Result: Returns -1 if the sort field of the first appointment is smaller
   *      than the second one, 0 if equal and -1 if greater.
   ***************************************************************************/
  int Sort_description(sAppointment * app1, sAppointment * app2);

  /***************************************************************************
   *  Sort_location
   *  A method that specifies in which way the appointments are to be sorted.
   *      This method is given as parameter (function pointer) and called
   *      multiple times by the sort method itself to compare two appointments.
   *      In this case the appointments are first checked for differences in their
   *      description then if necessary in date, then time and if still equivalent
   *      0(equality) is returned and the while loop continues.
   *  Parameter:
   *      - app1: the first appointments that is to compared to the other one
   *      - app2: the other appointment, that is compared to the first one
   *  Result: Returns -1 if the sort field of the first appointment is smaller
   *      than the second one, 0 if equal and -1 if greater.
   ***************************************************************************/
  int Sort_location(sAppointment * app1, sAppointment * app2);

  /***************************************************************************
   *  Sort_duration
   *  A method that specifies in which way the appointments are to be sorted.
   *      This method is given as parameter (function pointer) and called
   *      multiple times by the sort method itself to compare two appointments.
   *      In this case the appointments are first checked for differences in their
   *      description then if necessary in date, then time and if still equivalent
   *      0(equality) is returned and the while loop continues.
   *  Parameter:
   *      - app1: the first appointments that is to compared to the other one
   *      - app2: the other appointment, that is compared to the first one
   *  Result: Returns -1 if the sort field of the first appointment is smaller
   *      than the second one, 0 if equal and -1 if greater.
   ***************************************************************************/
  int Sort_duration(sAppointment * app1, sAppointment * app2);
#endif //EXERCISES_SORT_H
