#ifndef CALENDAR_H
  #define CALENDAR_H

  extern const int appointmentsPerPage, isEmptyTimeAllowed, maxDescriptionLength, isEmptyDescriptionAllowed, maxLocationLength, isEmptyLocationAllowed, isEmptyDurationAllowed;

  /***************************************************************************
   *  This module contains methods to manipulate an appointment in many
   *  different ways.
   *  Detailed information about each method and its arguments will be provided
   *  separately.
   ***************************************************************************/

  /***************************************************************************
   *  CreateAppointment
   *  Creates an appointment.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void CreateAppointment();

  /***************************************************************************
   *  EditAppointment
   *  Edits an appointment.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void EditAppointment();

  /***************************************************************************
   *  DeleteAppointment
   *  Deletes an appointment
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void DeleteAppointment();

  /***************************************************************************
   *  SearchAppointment
   *  Searches through the appointments.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void SearchAppointment();

  /***************************************************************************
   *  SortCalendar
   *  Sorts the appointments.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  // void SortCalendar();

  /***************************************************************************
   *  ListCalendar
   *  Lists all appointments.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void ListCalendar();

  /***************************************************************************
   *  FreeCalendar
   *  Frees the dynamically allocated memory for each appointment in the Calendar.
   *  Parameter: None
   *  Result: void
   ***************************************************************************/
  void FreeCalendar();

#endif // CALENDAR_H
