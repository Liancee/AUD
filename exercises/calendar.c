//
// Created by Liance on 12.10.23.
//
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"

int CountAppointments;
sAppointment Calendar[MAXAPPOINTMENTS];

void CreateAppointment()
{
  clearScreen();
  char* title = "Appointment creator";

  sAppointment appointment;

  printf("%s\n", title);
  printLine('=', strlen(title));
  printf("\n\n");

  GetDate("Date", &appointment.Date);

  GetTime("Time", &appointment.Time);

  GetText("Description", 100, appointment.Description, 0);

  GetText("Location", 15, appointment.Location, 0);

  waitForEnter();


  // date, time, description, location, duration
};

void EditAppointment()
{
    printf("Edit appointment\n\n");
    waitForEnter();
};

void DeleteAppointment()
{
    printf("Delete appointment\n\n");
    waitForEnter();
};

void SearchAppointment()
{
    printf("Search appointment\n\n");
    waitForEnter();
};

void SortCalendar()
{
    printf("Sort appointments\n\n");
    waitForEnter();
};

void ListCalendar()
{
    printf("List appointments\n\n");
    waitForEnter();
};