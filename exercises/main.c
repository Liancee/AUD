//
// Created by Liance on 12.10.23.
//

#include <stdio.h>
#include "menu.h"
#include "calendar.h"

int main()
{
    int userChoice = 0;
    char *menuTitle = "Terminverwaltung V 0.2";
    char *menuItems[] = {
        "Create appointment",
        "Edit appointment",
        "Delete appointment",
        "Search appointment",
        "Sort appointments",
        "List appointments",
        "Exit program"};
    int countMenuItems = 7;

    do
    {
        userChoice = GetMenu(menuTitle, menuItems, countMenuItems);

        printf("ToDo: ");
        switch (userChoice)
        {
        case 1:
            CreateAppointment();
            break;
        case 2:
            EditAppointment();
            break;
        case 3:
            DeleteAppointment();
            break;
        case 4:
            SearchAppointment();
            break;
        case 5:
            SortCalendar();
            break;
        case 6:
            ListCalendar();
            break;
        case 7:
            return 0;

        default:
            /* Could also handle wrong user input here instead of in menu.c cuz default would be exactly
            that => (if (userChoice > countMenuItems || userChoice <= 0)) but the task literally says it
            has to be handled in the GetMenu() method in menu.c*/
            return 0;
        }
    } while (userChoice);

    return 0;
}