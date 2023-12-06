//
// Created by Liance on 12.10.23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"
#include "escapesequenzen.h"

int CountAppointments = 0;
sAppointment Calendar[MAXAPPOINTMENTS];

void printFunctionHeader(char*);
char* getAppointmentDay(eDayOfTheWeek);
void getDiffDates(sAppointment *, sDate *, unsigned short *);
void freeAppointment(sAppointment *);

void CreateAppointment()
{
  sAppointment * pCal = &(Calendar[CountAppointments]);

  if (CountAppointments == MAXAPPOINTMENTS)
  {
    printf("You have reached the max amount of available appointments. Please upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [$(5)$] ");
    waitForEnter("continue");
    clearScreen();
    return;
  }

  printFunctionHeader("Appointment creator");

  STORE_POS;
  printf("  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:", "Date", "Time", "Description", "Location", "Duration");
  RESTORE_POS;

  if (!GetDate("Date", &(pCal->Date)))
    exit(EXIT_FAILURE);

  if (!GetTime("Time", &(pCal->Time)))
    exit(EXIT_FAILURE);

  if (!GetText("Description", 100, &(pCal->Description), 1))
    exit(EXIT_FAILURE);

  if (!GetText("Location", 15, &(pCal->Location), 1))
    exit(EXIT_FAILURE);

  pCal->Duration = malloc(sizeof(sTime)); // TODO better <- this or that 'app->Duration = malloc(sizeof(sTime));' ?
  if (!GetTime("Duration", pCal->Duration))
    exit(EXIT_FAILURE);

  printf("\n  Appointment has been saved!\n\n");
  waitForEnter("continue");
  CountAppointments++;
};

void EditAppointment()
{
  printf("Edit appointment\n\n");
  waitForEnter("continue");
};

void DeleteAppointment()
{
  printf("Delete appointment\n\n");
  waitForEnter("continue");
};

void SearchAppointment()
{
  printf("Search appointment\n\n");
  waitForEnter("continue");
};

void SortCalendar()
{
  printf("Sort appointments\n\n");
  waitForEnter("continue");
};

void ListCalendar()
{
  printFunctionHeader("Appointment list");
  printLine('=', 77);
  PrintNewLine(1);

  if (!CountAppointments) // No arms no cookies
  {
    printf("\nNo upcoming appointments in calendar! ");
    waitForEnter("continue");
    return;
  }

  sAppointment * pCal = Calendar; // creating a pointer to iterate through all appointments
  sDate * dates = calloc(CountAppointments, sizeof(sDate)); // creating an array where all the different appointment dates are stored
  if (!dates)
    exit(!RaiseMallocException("dates")); // TODO does this work?
  sDate * pDates = dates;
  unsigned short diffDatesFound = 1; // we need diffDatesFound later to know how many different date groups have to be printed

  getDiffDates(pCal, pDates, &diffDatesFound);

  sDate * tmpDates = realloc(dates, diffDatesFound * sizeof(sDate)); // not necessary but we now only have the needed memory allocated for dates cuz before we did not know how many there were
  if (!tmpDates)
  {
    fprintf(stderr, "Memory reallocation of dates failed. Program will exit. ");
    waitForEnter("continue");
    exit(EXIT_FAILURE);
  }
  dates = tmpDates;
  pDates = dates;

  int i; // not moving this up cuz this will probably be extracted into a function later on
  pCal = Calendar; // resetting appointment counter to first appointment
  for (i = 0; i < diffDatesFound; i++) // for every different date we found ...
  {
    if (pDates->DayOfTheWeek == NotADay) // hopefully we never see this one equal to true
      return;
    printf("%s, %02i.%02i.%04i\n", getAppointmentDay(pDates->DayOfTheWeek), pDates->Day, pDates->Month, pDates->Year); // prints header for every different date
    printLine('-', 15);
    PrintNewLine(1);
    while (pCal->Date.Day) // same as in loop above => if appointment "exists/is set"
    {
      if (pCal->Date.Year == (*pDates).Year && pCal->Date.Month == (*pDates).Month && pCal->Date.Day == (*pDates).Day) // if the current appointment date matches the current date to be output
      {
        printf("  %02i:%02i -> %-15s | ", pCal->Time.Hours, pCal->Time.Minutes, (pCal->Location) ? pCal->Location : "No location set");
        printf(((pCal->Description ? strlen(pCal->Description) : 0) < 49) ? "%-48s" : "%-.44s ...", (pCal->Description) ? pCal->Description : "No description available ...");
        PrintNewLine(1);
      }
      pCal++; // goto next appointment
    }
    if (i != diffDatesFound - 1) // if we printed all the different dates we print the "end" listing part
    {
      PrintNewLine(1);
      printLine('=', 78);
      PrintNewLine(1);
    }
    pDates++; // goto next date group that should be printed
    pCal = Calendar; // reset to first appointment
  }
  free(dates);
  dates = NULL;
  tmpDates = NULL;
  pCal = NULL;
  pDates = NULL;

  PrintNewLine(1);
  waitForEnter("continue");
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

void getDiffDates(sAppointment * pCal, sDate * dates, unsigned short * diffDatesFound)
{
  unsigned short isNewDate; // isNewDate is set 1 if a date is not found in dates else if it is 0. If it is 1 at the end of the iteration it is added to dates and 1 is added to diffDatesFound
  // creating a pointer pDates to iterate through dates; creating a pointer pNextDateStorePtr to know where the next date is to be stored
  sDate * pDates = dates, * pNextDateStorePtr = dates;
  *pDates = (*pCal).Date; // storing the first date into dates first position
  pNextDateStorePtr++;
  pCal++; // start with second date

  while (pCal->Date.Day) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
  {
    while (pDates->Day) // same as above but in the dates array. We iterate through every in dates saved different date
    {
      /* HELLO WHY CANNOT I COMPARE TWO STRUCTS AGAINST EACH OTHER?!?!?!
      * If the current date is already in dates, we break and go to next appointment otherwise we set isNewDate to 1 and compare against the next date in dates.
      * If it could not find the current appointment date in dates (isNewDate is still 1 at the end of the loop) it is added to dates.*/
      if (pCal->Date.Year == (*pDates).Year && pCal->Date.Month == (*pDates).Month && pCal->Date.Day == (*pDates).Day)
      {
        isNewDate = 0; // no we already got this one
        break; // so we leave and go next appointment
      }
      else
        isNewDate = 1; // yes date is different
      pDates++; // next date in dates to be compared against
    }
    if (isNewDate)
    {
      *pNextDateStorePtr++ = pCal->Date; // saves the current date and moves to the next save position afterward
      (*diffDatesFound)++;
    }
    pCal++; // Go to next appointment
    pDates = dates; // reset tmp so it starts at the first date in dates again
  }
  pNextDateStorePtr = NULL;
  pDates = NULL;
}

void FreeCalendar()
{
  sAppointment * pCal = Calendar;
  while(pCal->Date.Day)
  {
    freeAppointment(pCal);
    pCal++;
  }
}

void freeAppointment(sAppointment * app)
{
  if (app->Description)
    free(app->Description);
  if (app->Location)
    free(app->Location);
  if (app->Duration)
    free(app->Duration);
}
