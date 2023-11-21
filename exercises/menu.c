//
// Created by Liance on 12.10.23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

int GetMenu(char *menuTitle, char *menuItems[], int countMenuItems)
{
    if (!menuTitle || !menuItems || countMenuItems <= 0)
        return 0;

    int scanRes = 0;
    int userChoice = 0;
    int titleLength = strlen(menuTitle);
    char *equalSpam = malloc(titleLength * sizeof(char)); // There is printLine function now.. Why did I do this exactly? Practice Ig..
    if (!equalSpam)
        return 0;
    char *tmp = equalSpam;

    for (int i = 0; i < titleLength; i++)
        *tmp++ = '=';

    do
    {
        clearScreen();
        printf("%s\n%s\n\n", menuTitle, equalSpam);

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
            waitForEnter();
        }

    } while (!scanRes);

    free(equalSpam);
    equalSpam = NULL; // NOTE: ASK USEFUL?
    tmp = NULL;       // NOTE: ASK USEFUL?
    
    return userChoice;
}