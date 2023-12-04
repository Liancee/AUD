//
// Created by Liance on 12.10.23.
//

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "calendar.h"
#include "tools.h"
#include "database.h"

int main()
{
  int userChoice = 0;
  char *menuTitle = "Appointment manager V 0.2";
  char *menuItems[] = {
      "Create appointment",
      "Edit appointment",
      "Delete appointment",
      "Search appointment",
      "Sort appointments",
      "List appointments",
      "Exit program"};
  int countMenuItems = 7;

  if (!loadCalendar())
    exit(EXIT_FAILURE);

  do
  {
    userChoice = GetMenu(menuTitle, menuItems, countMenuItems);

    switch (userChoice)
    {
      case 0:
          printf("Parameter error for GetMenu() method! Program will exit.");
          waitForEnter();
          return 0;
      case 1:
          CreateAppointment();
          break;
      case 2:
          printf("ToDo: ");
          EditAppointment();
          break;
      case 3:
          printf("ToDo: ");
          DeleteAppointment();
          break;
      case 4:
          printf("ToDo: ");
          SearchAppointment();
          break;
      case 5:
          printf("ToDo: ");
          SortCalendar();
          break;
      case 6:
          ListCalendar();
          break;

      default:
          /* Could also handle wrong user input here instead of in menu.c cuz default would be exactly
          that => (if (userChoice > countMenuItems || userChoice <= 0)) but the task literally says it
          has to be handled in the GetMenu() method in menu.c*/
          if (askYesOrNo("Save appointments before exiting(y/n)? "))
            saveCalendar();

          FreeCalendar();

          return 0;
    }
  } while (userChoice);

  return 0;
}