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

    int scanRes = 0, userChoice, titleLength = strlen(menuTitle);
    char *equalSpam = malloc(titleLength * sizeof(char)); // There is printLine function now.. Why did I do this exactly? Practice Ig..
    if (!equalSpam)
        return 0;
    char *tmp = equalSpam;

    for (int i = 0; i < titleLength; i++)
    {
        *tmp++ = '='; // NOTE: works?
        // tmp++;
    }

    do
    {
        clearScreen();
        printf("%s\n%s\n\n", menuTitle, equalSpam);

        for (int i = 0; i < countMenuItems; i++)
        {
            printf("\t%i. %s\n\n", i + 1, menuItems[i]);
        }
        printf("Please enter your choice: ");
        scanRes = scanf("%i", &userChoice);
        clearBuffer();
        if (userChoice > countMenuItems)
        {
            printf("\nNo option with that number, please enter again!");
            scanRes = 0;
        }

    } while (!scanRes);

    free(equalSpam);
    tmp = NULL; // NOTE: ASK USEFUL?

    return userChoice;
}