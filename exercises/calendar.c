//
// Created by Liance on 12.10.23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"
#include "escapesequenzen.h"

int CountAppointments;
sAppointment Calendar[MAXAPPOINTMENTS];

void printFunctionHeader(char*);
char* getAppointmentDay(eDayOfTheWeek);

void CreateAppointment()
{
  sAppointment* appointment = calloc(1, sizeof(sAppointment));

  printFunctionHeader("Appointment creator");

  STORE_POS;
  printf("  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:", "Date", "Time", "Description", "Location", "Duration");
  RESTORE_POS;

  GetDate("Date", &(Calendar[CountAppointments].Date)); // why no *appointment.Date ?
  GetTime("Time", &(Calendar[CountAppointments].Time)); // &appointment->Time

  GetText("Description", 100, &(appointment->Description), 1);

  GetText("Location", 15, &(Calendar[CountAppointments].Location), 0);

  Calendar[CountAppointments].Duration = malloc(sizeof(sTime));
  GetTime("Duration", Calendar[CountAppointments].Duration);

  Calendar[CountAppointments++] = *appointment;
  free(appointment);
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
    printFunctionHeader("Appointment list");
    printLine('=', 78);
    printf("\n");
    sAppointment* pCal = Calendar;
    sDate* dates = malloc(CountAppointments);

    while (pCal++)
    {
      // would asking if dates has entries and if not save the first be more efficient or directly taking dates and comparing?
        printf("%s, %02i.%02i.%04i", getAppointmentDay(pCal->Date.DayOfTheWeek), pCal->Date.Day, pCal->Date.Month, pCal->Date.Year);
    }

    free(dates);
};

void printFunctionHeader(char* title)
{
    clearScreen();
    printf("%s\n", title);
    printLine('=', strlen(title));
    printf("\n\n");
}

char* getAppointmentDay(eDayOfTheWeek dayOfTheWeek)
{
        switch (dayOfTheWeek)
        {
            case 1: return "Mo";
            case 2: return "Tu";
            case 3: return "We";
            case 4: return "Th";
            case 5: return "Fr";
            case 6: return "Sa";
            case 7: return "Su";
            default: return "NotADay";
        }
}
