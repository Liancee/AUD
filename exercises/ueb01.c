#include <stdio.h>
#include "datastructure.h"
#include "datetime.h"
#include "tools.h"

void inputDate();

int main()
{
   do
   {
      clearScreen();
      inputDate();
   } while (askYesOrNo("Moechten Sie noch einmal (j/n) ? "));

   return 0;
}

/********************************************************************
 * Funktion void inputDate(void)
 *   - Benutzer soll ein Datum eingeben.
 *   - Eingabe wird mit Hilfe der Funktion getDateFromString geparst
 *     und geprueft. Bei gueltigem Datum steht dieses in der Datums-
 *     variable Date.
 *   - Ergebnis der Eingabe wird entsprechend angezeigt.
 * Paramater: keine
 * Funktionsergebnis: nichts
 *******************************************************************/
void inputDate()
{
   sDate Date;
   char Input[20];

   printf("Geben Sie bitte ein gueltiges Datum ein: ");
   *Input = '\0';
   scanf("%19[^\n]", Input);
   clearBuffer();
   if (getDateFromString(Input, &Date))
      printf("Das Datum %02i.%02i.%04i ist gueltig!\n", Date.Day, Date.Month, Date.Year);
   else
      printf("Das eingegebene Datum '%s' ist ungueltig!\n", Input);

   printf("\n");
}
