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

  if (!GetDate("Date", &(Calendar[CountAppointments].Date)))
  {
    waitForEnter();
    exit(0);
  }

  if (!GetTime("Time", &(Calendar[CountAppointments].Time)))
  {
    waitForEnter();
    exit(0);
  }

  if (!GetText("Description", 100, &(Calendar[CountAppointments].Description), 1))
  {
    waitForEnter();
    exit(0);
  }

  if (!GetText("Location", 15, &(Calendar[CountAppointments].Location), 1))
  {
    waitForEnter();
    exit(0);
  }

  Calendar[CountAppointments].Duration = malloc(1);
  if (!GetTime("Duration", Calendar[CountAppointments].Duration))
  {
    waitForEnter();
    exit(0);
  }

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
  printLine('=', 77);
  PrintNewLine(1);

  if (!CountAppointments) // No arms no cookies
  {
    printf("\nNo upcoming appointments in calendar! ");
    waitForEnter();
    return;
  }

  sAppointment* pCal = Calendar;
  sDate* dates = calloc(CountAppointments, sizeof(sDate));
  if (!dates)
  {
    fprintf(stderr, "Memory allocation of dates failed. Program will exit. ");
    waitForEnter();
    exit(0);
  }
  sDate* tmp = dates, *nextDateStorePtr = dates; // + sizeof(sDate); <-- did not work, one of the last and nastiest bugs. I wanted to move the sDate pointer tmp2 to the second sDate, now in next line
  nextDateStorePtr++; // tmp2 starts at position 2, the first position sth has to be saved to
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
      *nextDateStorePtr++ = pCal->Date;
      diffDatesFound++;
    }
    pCal++;
    tmp = dates;
  }

  if (!realloc(dates, diffDatesFound * sizeof(sDate)))
  {
    fprintf(stderr, "Memory reallocation of dates failed. Program will exit. ");
    waitForEnter();
    exit(0);
  }


  int i;
  pCal = Calendar;
  for (i = 0; i < diffDatesFound; i++)
  {
    if (tmp->DayOfTheWeek == NotADay)
      return;
    printf("%s, %02i.%02i.%04i\n", getAppointmentDay(tmp->DayOfTheWeek), tmp->Day, tmp->Month, tmp->Year);
    printLine('-', 15);
    PrintNewLine(1);
    while (pCal->Date.Day)
    {
      if (pCal->Date.Year == (*tmp).Year && pCal->Date.Month == (*tmp).Month && pCal->Date.Day == (*tmp).Day)
      {
        printf("  %02i:%02i -> %-15s | ", pCal->Time.Hours, pCal->Time.Minutes, (pCal->Location) ? pCal->Location : "No location set");
        printf(((pCal->Description ? strlen(pCal->Description) : 0) < 49) ? "%-48s" : "%-.44s ...", (pCal->Description) ? pCal->Description : "No description available ...");
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
