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

  sAppointment* pCal = Calendar; // creating a pointer to iterate through all appointments
  sDate* dates = calloc(CountAppointments, sizeof(sDate)); // creating an array where all the different appointment dates are stored
  if (!dates)
  {
    fprintf(stderr, "Memory allocation of dates failed. Program will exit. ");
    waitForEnter();
    exit(0);
  }
  // creating a pointer tmp to iterate through dates; creating a pointer nextDateStorePtr to know where the next date is to be stored
  sDate* tmp = dates, *nextDateStorePtr = dates; // + sizeof(sDate); <-- did not work, one of the last and nastiest bugs. I wanted to move the sDate pointer tmp2 to the second sDate, now in next line
  nextDateStorePtr++; // tmp2 starts at position 2, the first position sth has to be saved to
  *tmp = (*pCal).Date; // storing the first date into dates first position
  unsigned short diffDatesFound = 1, isNewDate; /* we need diffDatesFound later to know how many different date groups have to be printed;
 * isNewDate is set 1 if a date is not found in dates else if it is 0. If it is 1 at the end of the iteration it is added to dates and 1 is added to diffDatesFound*/
  pCal++; // start with second date

  while (pCal->Date.Day) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
  {
    while (tmp->Day) // same as above but in the dates array. We iterate through every in dates saved different date
    {
      /* HELLO WHY CANNOT I COMPARE TWO STRUCTS AGAINST EACH OTHER?!?!?!
      * If the current date is already in dates, we break and go to next appointment otherwise we set isNewDate to 1 and compare against the next date in dates.
      * If it could not find the current appointment date in dates (isNewDate is still 1 at the end of the loop) it is added to dates.*/
      if (pCal->Date.Year == (*tmp).Year && pCal->Date.Month == (*tmp).Month && pCal->Date.Day == (*tmp).Day)
      {
        isNewDate = 0; // no we already got this one
        break; // so we leave and go next appointment
      }
      else
        isNewDate = 1; // yes date is different
      tmp++; // next date in dates to be compared against
    }
    if (isNewDate)
    {
      *nextDateStorePtr++ = pCal->Date; // saves the current date and moves to the next save position afterward
      diffDatesFound++;
    }
    pCal++; // Go to next appointment
    tmp = dates; // reset tmp so it starts at the first date in dates again
  }

  if (!realloc(dates, diffDatesFound * sizeof(sDate))) // not necessary but we now only have the needed memory allocated for dates cuz before we did not know how many there were
  {
    fprintf(stderr, "Memory reallocation of dates failed. Program will exit. ");
    waitForEnter();
    exit(0);
  }

  int i; // not moving this up cuz this will probably be extracted into a function later on
  pCal = Calendar; // resetting appointment counter to first appointment (might actually not be necessary since we already do at the end of the loop above (we already do the same with tmp...))
  for (i = 0; i < diffDatesFound; i++) // for every different date we found ...
  {
    if (tmp->DayOfTheWeek == NotADay) // hopefully we never see this one equal to true
      return;
    printf("%s, %02i.%02i.%04i\n", getAppointmentDay(tmp->DayOfTheWeek), tmp->Day, tmp->Month, tmp->Year); // prints header for every different date
    printLine('-', 15);
    PrintNewLine(1);
    while (pCal->Date.Day) // same as in loop above => if appointment "exists/is set"
    {
      if (pCal->Date.Year == (*tmp).Year && pCal->Date.Month == (*tmp).Month && pCal->Date.Day == (*tmp).Day) // if the current appointment date matches the current date to be output
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

    tmp++; // goto next date group that should be printed
    pCal = Calendar; // reset to first appointment
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
