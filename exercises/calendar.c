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

void printFunctionHeader(char*);

void CreateAppointment()
{
  sAppointment appointment;

  printFunctionHeader("Appointment creator");

  GetDate("Date", &appointment.Date);

  GetTime("Time", &appointment.Time);

  GetText("Description", 100, appointment.Description, 0);

  GetText("Location", 15, appointment.Location, 0);

  GetTime("Duration", appointment.Duration);

  Calendar[CountAppointments++] = appointment;
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

    while (pCal++)
    {
        printf("%s, %02i.%02i.%04i", getAppointmentDay(pCal->Date.DayOfTheWeek), pCal->Date.Day, pCal->Date.Month, pCal->Date.Year);
    }
    // TODO: implement this
    printf("List appointments\n\n");
    waitForEnter();
};

void printFunctionHeader(char* title)
{
    clearScreen();
    printf("%s\n", title);
    printLine('=', strlen(title));
    printf("\n\n");
}

char[] getAppointmentDay(eDayOfTheWeek dayOfTheWeek)
{

        switch (dayOfTheWeek)
        {
            case 1: return "Mo";
            case 2: return "Tu";
            case 3: return "We";
            case 4: return "";
            case 5: return "";
            case 6: return "";
            case 7: return "";
            default: return
            NotADay; // Error
        }
    return
}
