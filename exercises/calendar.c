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
  char* prompt = "%-12s: ";

  printf("%s\n", title);
  printLine('=', strlen(title));
  printf("\n\n");
  GetDate("%-12s: ");

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