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
#include "list.h"

int AppointmentCount = 0;

const int appointmentsPerPage = 5, isEmptyTimeAllowed = 0, maxDescriptionLength = 100, isEmptyDescriptionAllowed = 1, maxLocationLength = 15, isEmptyLocationAllowed = 1, isEmptyDurationAllowed = 1;

void printFunctionHeader(char *);
char* getAppointmentDay(eDayOfTheWeek);
void getDiffDates(sDate *, unsigned short *);
char * add_time(sAppointment *);
void freeAppointment(sAppointment *);

void CreateAppointment()
{
  printFunctionHeader("Appointment creator");

  // do not need below anymore after swapping to doubly linked list .. Sadge :(
  /*if (AppointmentCount == MAXAPPOINTMENTS)
  {
    printf("You have reached the max amount of available appointments. Please upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [$(5)$] ");
    waitForEnter("continue");
    clearScreen();

    return;
  }*/

  sAppointment * app = malloc(sizeof(sAppointment));
  if (!app) exit(EXIT_FAILURE);

  STORE_POS;
  printf("  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:\n  %-12s:", "Date", "Time", "Description", "Location", "Duration");
  RESTORE_POS;

  if (!GetDate("Date", &(app->Date))) exit(EXIT_FAILURE);

  if (!GetTime("Time", &(app->Time), isEmptyTimeAllowed)) exit(EXIT_FAILURE);

  if (!GetText("Description", maxDescriptionLength, &(app->Description), isEmptyDescriptionAllowed)) exit(EXIT_FAILURE);

  if (!GetText("Location", maxLocationLength, &(app->Location), isEmptyLocationAllowed)) exit(EXIT_FAILURE);

  sTime time;
  if (!GetTime("Duration", &time, isEmptyDurationAllowed)) exit(EXIT_FAILURE);
  if (time.Hours != 255)
  {
    app->Duration = malloc(sizeof(sTime));
    if (app->Duration) *(app->Duration) = time; //pCal->Duration = &time; // TODO what happens here exactly? address to dynamic pointer or dynamic pointer to address?
    else
    {
      RaiseMallocException("pCal->Duration");
      exit(EXIT_FAILURE);
    }
  }

  InsertInDList(app, Sort_date_time);

  printf("\n  Appointment has been created!\n\n");
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
  if (!AppointmentCount) // No arms no cookies
  {
    printFunctionHeader("Delete appointment");
    printLine('=', 77);
    PrintNewLine(1);

    printf("\nThere is no appointment to delete in the calendar! ");
    waitForEnter("continue");
    return;
  }

  int i = 0, maxStringLength = 24 + maxDescriptionLength + 2; // Length of the max full string to be displayed for user deletion choice
  char * menuItems[maxStringLength];
  sAppointment * app = First;
  menuItems[i++] = "To return to the main menu"; // First menu choice is 0 which is return to main menu; After setting that i is incremented
  for (; i <= AppointmentCount; i++) // <= since we need one more iteration to account for the displacement from inserting at 0
  {
    menuItems[i] = malloc(maxStringLength);
    if (!menuItems[i]) exit(!RaiseMallocException("menuItems[i]"));
    int printResult = snprintf(menuItems[i], maxStringLength, "%s, %02d.%02d.%04d, %02d:%02d: %s", getAppointmentDay(app->Date.DayOfTheWeek), app->Date.Day, app->Date.Month, app->Date.Year, app->Time.Hours, app->Time.Minutes, app->Description ? app->Description : "No description available ...");
    if (printResult <= 0 || printResult >= maxStringLength)
    {
      printf("Something went wrong when trying to list the appointments to choose for deletion, program must exit!");
      waitForEnter("to exit");
      exit(EXIT_FAILURE);
    }
    app = app->Next;
  }
  int userChoice = GetMenu("Delete appointment", menuItems, AppointmentCount + 1, 0);

  for (i = 1; i < AppointmentCount; i++) // start at one since we manually added the first return to main menu string at pos 0
    if (menuItems[i])
    {
      free(menuItems[i]); // free every allocated memory for getting user menu choice acquisition
      menuItems[i] = NULL; // no dangling around here
    }

  if (!userChoice) return; // user chose 0 so we return to main menu
  else
  {
    app = First;
    for (i = 1; i < userChoice; i++) app = app->Next; // we go to the chosen appointment to delete it (would be way easier with index)
    sAppointment * rm = RemoveFromDList(app, Sort_date_time); // remove the linking of the appointment from the doubly linked list
    freeAppointment(rm); // free the dynamically reserved memory of the appointment
    rm = NULL;
    AppointmentCount--; // decrement the global appointment counter
  }
};

void SearchAppointment()
{
  printf("Search appointment\n\n");
  waitForEnter("continue");
};

/*void SortCalendar()
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
};*/

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

  sDate * dates = calloc(AppointmentCount + 1, sizeof(sDate)); // creating an array where all the different appointment dates are stored
  if (!dates) exit(!RaiseMallocException("dates"));

  sDate * pDates = dates;
  unsigned short diffDatesFound = 1; // we need diffDatesFound later to know how many different date groups have to be printed

  getDiffDates(pDates, &diffDatesFound);

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
  sAppointment * app = First; // resetting appointment counter to first appointment
  for (i = 0; i < diffDatesFound; i++) // for every different date we found ...
  {
    if (pDates->DayOfTheWeek == NotADay) return; // hopefully we never see this one equal to true

    while (app) // same as in loop above => if appointment "exists/is set" TODO doesnt this loop go outofbounds?
    {
      if (app->Date.Year == (*pDates).Year && app->Date.Month == (*pDates).Month && app->Date.Day == (*pDates).Day) // if the current appointment date matches the current date to be output
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
        if (app->Duration) end_time = add_time(app);

        printf("  %02d:%02d %7s -> %-15s | ", app->Time.Hours, app->Time.Minutes, app->Duration ? end_time : " ", (app->Location) ? app->Location : "No location set");
        printf(((app->Description ? strlen(app->Description) : 0) < 41) ? "%-40s" : "%-.36s ...", (app->Description) ? app->Description : "No description available ...");
        PrintNewLine(1);
        outputCount++;
        if (end_time) free(end_time);
      }
      app = app->Next; // goto next appointment

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
      printf("\n%s, %02i.%02i.%04d\n", getAppointmentDay(pDates->DayOfTheWeek), pDates->Day, pDates->Month, pDates->Year); // prints header for every different date
      printLine('-', 15);
      PrintNewLine(1);
    }
    else pDates++; // goto next date group that should be printed
    app = First; // reset to first appointment
  }
  free(dates);
  dates = NULL;
  tmpDates = NULL;
  app = NULL;
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

void getDiffDates(sDate * dates, unsigned short * diffDatesFound)
{
  sAppointment * app = First;
  unsigned short isNewDate; // isNewDate is set 1 if a date is not found in dates else if it is 0. If it is 1 at the end of the iteration it is added to dates and 1 is added to diffDatesFound
  // creating a pointer pDates to iterate through dates; creating a pointer pNextDateStorePtr to know where the next date is to be stored
  sDate * pDates = dates, * pNextDateStorePtr = dates;
  *pDates = (*First).Date; // storing the first date into dates first position

  pNextDateStorePtr++;
  app = app->Next; // start with second date
  int i;
  for (i = 0; i < AppointmentCount - 1; i++) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
  {
    while (pDates->Day) // same as above but in the dates array. We iterate through every in dates saved different date
    {
      /* HELLO WHY CANNOT I COMPARE TWO STRUCTS AGAINST EACH OTHER?!?!?!
      * If the current date is already in dates, we break and go to next appointment otherwise we set isNewDate to 1 and compare against the next date in dates.
      * If it could not find the current appointment date in dates (isNewDate is still 1 at the end of the loop) it is added to dates.*/
      if (app->Date.Year == (*pDates).Year && app->Date.Month == (*pDates).Month && app->Date.Day == (*pDates).Day)
      {
        isNewDate = 0; // no we already got this one
        break; // so we leave and go next appointment
      }
      else isNewDate = 1; // yes date is different
      pDates++; // next date in dates to be compared against
    }
    if (isNewDate)
    {
      *pNextDateStorePtr++ = app->Date; // saves the current date and moves to the next save position afterward
      (*diffDatesFound)++;
    }
    app = app->Next; // Go to next appointment
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
  sAppointment * app = First, *appNext;
  for (int i = 0; i < AppointmentCount; i++)
  {
    appNext = app->Next;
    freeAppointment(app);
    app = appNext;
  }
}

void freeAppointment(sAppointment * app)
{
  if (app->Description) free(app->Description);
  if (app->Location) free(app->Location);
  if (app->Duration) free(app->Duration);
  if (app) free(app);
}
