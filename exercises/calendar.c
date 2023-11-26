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
  if (CountAppointments == MAXAPPOINTMENTS)
  {
    printf("You have reached the max amount of available appointments. Please upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [̲̅$̲̅(̲̅5̲̅)̲̅$̲̅] ");
    waitForEnter();
    clearScreen();
    return;
  }
  printFunctionHeader("Appointment creator");

  STORE_POS;
  printf("  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:", "Date", "Time", "Description", "Location", "Duration");
  RESTORE_POS;

  GetDate("Date", &(Calendar[CountAppointments].Date)); // why no *appointment.Date ?
  GetTime("Time", &(Calendar[CountAppointments].Time)); // &appointment->Time

  GetText("Description", 100, &(Calendar[CountAppointments].Location), 0);

  GetText("Location", 15, &(Calendar[CountAppointments].Location), 0);

  GetTime("Duration", Calendar[CountAppointments].Duration);

  printf("\n  Appointment has been saved!\n\n");
  waitForEnter();
  CountAppointments++;
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
  PrintNewLine(1);

  if (!CountAppointments) // No arms no cookies
  {
    printf("\nNo upcoming appointments in calendar! ");
    waitForEnter();
    return;
  }

  if (CountAppointments == 1)
  {
    // TODO all beneath must be summarized in a function cuz same as below
    if (Calendar->Date.DayOfTheWeek == NotADay)
      return;
    printf("%s, %02i.%02i.%04i", getAppointmentDay(Calendar->Date.DayOfTheWeek), Calendar->Date.Day, Calendar->Date.Month, Calendar->Date.Year);
    printLine('-', 15);
    PrintNewLine(1);

    if (strlen(Calendar->Description) < 49)
      printf("  %02i:%02i -> %-15s| %-48s", Calendar->Time.Hours, Calendar->Time.Minutes, Calendar->Location, Calendar->Description);
    else
      printf("  %02i:%02i -> %-15s| %-44s ...", Calendar->Time.Hours, Calendar->Time.Minutes, Calendar->Location, Calendar->Description);
  }

  sAppointment* pCal = Calendar;
  sDate* dates = calloc(CountAppointments, sizeof(sDate));
  sDate* tmp = dates, *tmp2 = dates; // + sizeof(sDate); <-- did not work, one of the last and nastiest bugs. I wanted to move the sDate pointer tmp2 to the second sDate, now in next line
  tmp2++; // tmp2 starts at position 2, the first position sth has to be saved to
  *tmp = (*pCal).Date;
  unsigned short diffDatesFound = 1, isNewDate;
  pCal++; // start with second date

  while (pCal->Date.Day)
  {
    while (tmp->Day)
    {
      if (pCal->Date.Year == (*tmp).Year && pCal->Date.Month == (*tmp).Month && pCal->Date.Day == (*tmp).Day) // HELLO WHY CANNOT I COMPARE TWO STRUCTS AGAINST EACH OTHER?!?!?!
      {
        isNewDate = 0;
        break;
      }
      else
        isNewDate = 1;
      tmp++;
    }
    if (isNewDate)
    {
      *tmp2++ = pCal->Date;
      diffDatesFound++;
    }
    pCal++;
    tmp = dates;
  }

  if (!realloc(dates, diffDatesFound * sizeof(sDate)))
    return;

  int i; // TODO put up
  pCal = Calendar;
  for (i = 0; i < diffDatesFound; i++)
  {
    if (tmp->DayOfTheWeek == NotADay)
      return;
    printf("%s, %02i.%02i.%04i\n", getAppointmentDay(tmp->DayOfTheWeek), tmp->Day, tmp->Month, tmp->Year);
    printLine('-', 15);
    printf("\n");
    while (pCal->Date.Day)
    {
      if (pCal->Date.Year == (*tmp).Year && pCal->Date.Month == (*tmp).Month && pCal->Date.Day == (*tmp).Day)
      {
        if (!(pCal->Description))
          printf("  %02i:%02i -> %-15s| %-48s", pCal->Time.Hours, pCal->Time.Minutes, pCal->Location, "No description available ...");
        else if (strlen(pCal->Description) < 49)
          printf("  %02i:%02i -> %-15s| %-48s", pCal->Time.Hours, pCal->Time.Minutes, pCal->Location, pCal->Description);
        else
          printf("  %02i:%02i -> %-15s| %-44s ...", pCal->Time.Hours, pCal->Time.Minutes, pCal->Location, pCal->Description);
        PrintNewLine(1);
      }
      pCal++;
    }
    if (i != diffDatesFound - 1)
    {
      PrintNewLine(1);
      printLine('=', 78);
      PrintNewLine(1);
    }

    tmp++;
    pCal = Calendar;
  }
  free(dates);

  PrintNewLine(2);
  waitForEnter();
};

void printFunctionHeader(char* title)
{
    clearScreen();
    printf("%s\n", title);
    printLine('=', strlen(title));
    PrintNewLine(2);
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
