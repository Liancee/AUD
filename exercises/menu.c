#include <stdio.h>
#include <string.h>
#include "tools.h"

int GetMenu(char * menuTitle, char * menuItems[], int countMenuItems, unsigned short startAtZero)
{
    if (!menuTitle || !menuItems || countMenuItems <= 0) return 0;

    int scanRes = 0, userChoice = 0, titleLength = strlen(menuTitle);

    do
    {
        clearScreen();
        printf("%s\n", menuTitle);
        printLine('=', titleLength);
        PrintNewLine(2);

        for (int i = 0; i < countMenuItems; i++) printf("  %*d. %s\n", DigitCount(countMenuItems), i + startAtZero, menuItems[i]);

        printf("\nPlease enter your choice: ");
        scanRes = scanf("%d", &userChoice);
        clearBuffer();
        if (userChoice > countMenuItems || startAtZero && userChoice <= 0)
        {
            printf("\nNo option with that number! ");
            scanRes = 0;
            waitForEnter("continue");
        }
    } while (!scanRes);
    return userChoice;
}