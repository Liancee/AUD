#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calendar.h"
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"
#include "escapesequenzen.h"
#include "menu.h"
#include "sort.h"

int AppointmentCount = 0;
sAppointment Calendar[MAXAPPOINTMENTS];

int const appointmentsPerPage = 5;

void printFunctionHeader(char *);
char* getAppointmentDay(eDayOfTheWeek);
void getDiffDates(sAppointment *, sDate *, unsigned short *);
char * add_time(sAppointment *);
void freeAppointment(sAppointment *);

void CreateAppointment()
{
  printFunctionHeader("Appointment creator");

  if (AppointmentCount == MAXAPPOINTMENTS)
  {
    printf("You have reached the max amount of available appointments. Please upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [$(5)$] ");
    waitForEnter("continue");
    clearScreen();

    return;
  }

  sAppointment * pCal = &(Calendar[AppointmentCount]);

  STORE_POS;
  printf("  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:", "Date", "Time", "Description", "Location", "Duration");
  RESTORE_POS;

  if (!GetDate("Date", &(pCal->Date))) exit(EXIT_FAILURE);

  if (!GetTime("Time", &(pCal->Time), 0)) exit(EXIT_FAILURE);

  if (!GetText("Description", 100, &(pCal->Description), 1)) exit(EXIT_FAILURE);

  if (!GetText("Location", 15, &(pCal->Location), 1)) exit(EXIT_FAILURE);

  sTime time;
  if (!GetTime("Duration", &time, 1)) exit(EXIT_FAILURE);
  if (time.Hours != 255)
  {
    pCal->Duration = malloc(sizeof(sTime));
    if (pCal->Duration) *(pCal->Duration) = time; //pCal->Duration = &time; // TODO what happens here exactly? address to dynamic pointer or dynamic pointer to address?
    else
    {
      RaiseMallocException("pCal->Duration");
      exit(EXIT_FAILURE);
    }
  }

  printf("\n  Appointment has been saved!\n\n");
  waitForEnter("continue");
  AppointmentCount++;
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
  if (!AppointmentCount) // No arms no cookies
  {
    printFunctionHeader("Sort appointments");
    printLine('=', 77);
    PrintNewLine(1);

    printf("\nThere are no appointments to sort in the calendar! ");
    waitForEnter("continue");
    return;
  }

  int userChoice = 0;
  char * menuItems[] =
  {
      "Sort by date and time",
      "Sort by description",
      "Sort by location",
      "Sort by duration",
      "Back to main menu"
  };

  switch (GetMenu("Sort appointments", menuItems, sizeof(menuItems) / sizeof(menuItems[0])))
  {
    case 0:
      printf("Parameter error for GetMenu() method! Program will exit.");
    waitForEnter("continue");
    exit(EXIT_FAILURE);
    case 1:
      Quick_sort(Calendar, AppointmentCount, Sort_date_time);
      return;
    case 2:
      Quick_sort(Calendar, AppointmentCount, Sort_description);
      return;
    case 3:
      Quick_sort(Calendar, AppointmentCount, Sort_location);
      return;
    case 4:
      Quick_sort(Calendar, AppointmentCount, Sort_duration);
      return;
    default: return; // handles case 5 "Back to main menu"
  }
};

void ListCalendar()
{
  //clearScreen(); TODO

  if (!AppointmentCount) // No arms no cookies
  {
    printFunctionHeader("Appointment list");
    printLine('=', 77);
    PrintNewLine(1);

    printf("\nNo upcoming appointments in calendar! ");
    waitForEnter("continue");
    return;
  }

  sAppointment * pCal = Calendar; // creating a pointer to iterate through all appointments
  sDate * dates = calloc(AppointmentCount + 1, sizeof(sDate)); // creating an array where all the different appointment dates are stored
  if (!dates) exit(!RaiseMallocException("dates"));

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

  int i, outputCount = 0, remainingDatesToBeDisplayed = AppointmentCount, headerIsPrinted = 0, page = 1; // not moving this up cuz this will probably be extracted into a function later on
  pCal = Calendar; // resetting appointment counter to first appointment
  for (i = 0; i < diffDatesFound; i++) // for every different date we found ...
  {
    if (pDates->DayOfTheWeek == NotADay) return; // hopefully we never see this one equal to true

    while (pCal->Date.Day) // same as in loop above => if appointment "exists/is set" TODO doesnt this loop go outofbounds?
    {
      if (pCal->Date.Year == (*pDates).Year && pCal->Date.Month == (*pDates).Month && pCal->Date.Day == (*pDates).Day) // if the current appointment date matches the current date to be output
      {
        if (!headerIsPrinted)
        {
          int pageOutputLen = strlen("Appointment list\t\t\t\t\t       Page %02d from %02d");
          char * output = malloc(pageOutputLen + 1);
          if (output)
          {
            snprintf(output, pageOutputLen, "Appointment list\t\t\t\t\t       Page %02d from %02d", page, AppointmentCount % appointmentsPerPage ? AppointmentCount / appointmentsPerPage + 1 : AppointmentCount / appointmentsPerPage);
            printFunctionHeader(output);
            free(output);
          }
          else printFunctionHeader("Appointment list");
          output = NULL;

          printLine('=', 78);
          PrintNewLine(1);

          printf("%s, %02d.%02d.%04i\n", getAppointmentDay(pDates->DayOfTheWeek), pDates->Day, pDates->Month, pDates->Year); // prints header for every different date
          printLine('-', 15);
          PrintNewLine(1);

          headerIsPrinted = 1;
        }
        char * end_time = NULL;
        if (pCal->Duration) end_time = add_time(pCal);

        printf("  %02d:%02d %7s -> %-15s | ", pCal->Time.Hours, pCal->Time.Minutes, pCal->Duration ? end_time : " ", (pCal->Location) ? pCal->Location : "No location set");
        printf(((pCal->Description ? strlen(pCal->Description) : 0) < 41) ? "%-40s" : "%-.36s ...", (pCal->Description) ? pCal->Description : "No description available ...");
        PrintNewLine(1);
        outputCount++;
        if (end_time) free(end_time);
      }
      pCal++; // goto next appointment

      if (outputCount == appointmentsPerPage && remainingDatesToBeDisplayed > appointmentsPerPage)
      {
        page++;
        headerIsPrinted = 0;
        outputCount = 0;
        remainingDatesToBeDisplayed -= remainingDatesToBeDisplayed >= appointmentsPerPage ? appointmentsPerPage : remainingDatesToBeDisplayed;
        printf("\n");
        int outputLen = strlen("show the next (%i) appointments");
        char * output = malloc(outputLen + 1);
        if (output)
        {
          snprintf(output, outputLen, "show the next (%i) appointments", remainingDatesToBeDisplayed > appointmentsPerPage ? appointmentsPerPage : remainingDatesToBeDisplayed);
          waitForEnter(output);
          free(output);
          output = NULL;
        }
        else waitForEnter("show the next appointments");

        clearScreen();
      }
    }

    if (i != diffDatesFound - 1) // if we printed all the different dates we print the "end" listing part
    {
      pDates++;
      PrintNewLine(1);
      printLine('=', 78);
      printf("\n%s, %02i.%02i.%04i\n", getAppointmentDay(pDates->DayOfTheWeek), pDates->Day, pDates->Month, pDates->Year); // prints header for every different date
      printLine('-', 15);
      PrintNewLine(1);
    }
    else pDates++; // goto next date group that should be printed
    pCal = Calendar; // reset to first appointment
  }
  free(dates);
  dates = NULL;
  tmpDates = NULL;
  pCal = NULL;
  pDates = NULL;

  PrintNewLine(1);
  waitForEnter("exit to main menu");
};

void printFunctionHeader(char * title)
{
  clearScreen();
  printf("%s\n", title);
  printLine('=', strlen(title));
  PrintNewLine(2);
}

char * getAppointmentDay(eDayOfTheWeek dayOfTheWeek)
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
  int i;
  for (i = 0; i < AppointmentCount - 1; i++) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
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
      else isNewDate = 1; // yes date is different
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

char * add_time(sAppointment * app)
{
  sTime t;

  t.Seconds = app->Time.Seconds + app->Duration->Seconds;
  t.Minutes = app->Time.Minutes + app->Duration->Minutes;
  t.Hours = app->Time.Hours + app->Duration->Hours;

  if (t.Seconds >= 60) {
    t.Minutes += t.Seconds / 60;
    t.Seconds %= 60;
  }

  if (t.Minutes >= 60) {
    t.Hours += t.Minutes / 60;
    t.Minutes %= 60;
  }

  t.Hours %= 24; // Limiting the hours to a 24-hour day
  // cannot interpret if the end time is on a new day, do not know in which way I would like to implement it (+1)

  char * time = malloc(8);
  if (time)
  {
    sprintf(time, "- %02d:%02d", t.Hours, t.Minutes);
    return time;
  }
  else
  {
    RaiseMallocException("time");
    waitForEnter("exit");
    exit(EXIT_FAILURE);
  }
}

void FreeCalendar()
{
  sAppointment * pCal = Calendar;
  for (int i = 0; i < AppointmentCount; i++)
  {
    freeAppointment(pCal);
    pCal++;
  }
}

void freeAppointment(sAppointment * app)
{
  if (app->Description) free(app->Description);
  if (app->Location) free(app->Location);
  if (app->Duration) free(app->Duration);
}
