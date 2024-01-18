#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "calendar.h"
#include "tools.h"
#include "database.h"

int main()
{
  int userChoice = 0;
  char * menuItems[] =
  {
      "Create appointment",
      "Edit appointment",
      "Delete appointment",
      "Search appointment",
      //"Sort appointments",
      "List appointments",
      "List hash table",
      "Exit program"
  };

  if (!loadCalendar()) exit(EXIT_FAILURE);

  do
  {
    userChoice = GetMenu("Appointment manager V 0.2", menuItems, sizeof(menuItems) / sizeof(menuItems[0]), 1);

    switch (userChoice)
    {
      case 0:
          printf("Parameter error for GetMenu() method! Program will exit.");
          waitForEnter("continue");
          return EXIT_FAILURE;
      case 1:
          CreateAppointment();
          break;
      case 2:
          printf("ToDo: ");
          EditAppointment();
          break;
      case 3:
          DeleteAppointment();
          break;
      case 4:
          SearchAppointment();
          break;
      /*case 5:
          SortCalendar();
          break;*/
      case 5:
        ListCalendar();
        break;
      case 6:
        ListHashTable();
        break;

      default:
          /* Could also handle wrong user input here instead of in menu.c cuz default would be exactly
          that => (if (userChoice > countMenuItems || userChoice <= 0)) but the task literally says it
          has to be handled in the GetMenu() method in menu.c*/
          if (askYesOrNo("Save appointments before exiting(y/n)? "))
            if (!saveCalendar())
            {
              FreeCalendar();
              exit(EXIT_FAILURE);
            }

          FreeCalendar();

          return EXIT_SUCCESS;
    }
  } while (userChoice);

  return EXIT_SUCCESS;
}