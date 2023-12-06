//
// Created by Liance on 12.10.23.
//
#include <stdio.h>
#include <string.h>
#include "tools.h"

int GetMenu(char *menuTitle, char *menuItems[], int countMenuItems)
{
    if (!menuTitle || !menuItems || countMenuItems <= 0)
        return 0;

    int scanRes = 0, userChoice = 0, titleLength = strlen(menuTitle);

    do
    {
        clearScreen();
        printf("%s\n", menuTitle);
        printLine('=', titleLength);
        PrintNewLine(2);

        for (int i = 0; i < countMenuItems; i++)
        {
            printf("  %i. %s\n\n", i + 1, menuItems[i]);
        }
        printf("Please enter your choice: ");
        scanRes = scanf("%i", &userChoice);
        clearBuffer();
        if (userChoice > countMenuItems || userChoice <= 0)
        {
            printf("\nNo option with that number! ");
            scanRes = 0;
            waitForEnter("continue");
        }
    } while (!scanRes);
    return userChoice;
}