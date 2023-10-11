#ifndef TOOLS_H
#define TOOLS_H

/***************************************************************************
 *  AskAgain
 *  Fragt den Benutzer ob das Programm geschlossen oder erneut ausgefuehrt werden soll
 *  Parameter: keine
 *  Ergebnis : Gibt eine eins zurueck, wenn die Benutzereingabe ein j/J war und eine 0, wenn sie ein n/N war.
 ***************************************************************************/
int askAgain();

/***************************************************************************
 *  AskAgainPos
 *  Fragt den Benutzer ob das Programm geschlossen oder erneut ausgefuehrt werden soll in einer bestimmten Zeile/Spalte
 *  Parameter: Row, Col: Zeile und Spalte, in der die Benutzerfrage beginnt
 *  Ergebnis : Gibt eine eins zurueck, wenn die Benutzereingabe ein j/J war und eine 0, wenn sie ein n/N war.
 ***************************************************************************/
int askAgainPos(int Row, int Col);

/***************************************************************************
 *  askYesOrNo
 *  Fragt den Benutzer ob nach einer Antwort (ja/nein)
 *  Parameter:
 *  Ergebnis :
 ***************************************************************************/
int askYesOrNo(char *question);

/***************************************************************************
 *  clearScreen
 *  Fragt den Benutzer ob nach einer Antwort (ja/nein)
 *  Parameter:
 *  Ergebnis :
 ***************************************************************************/
void clearScreen();

/***************************************************************************
 *  clearScreen
 *  Fragt den Benutzer ob nach einer Antwort (ja/nein)
 *  Parameter:
 *  Ergebnis :
 ***************************************************************************/
void waitForEnter();

/***************************************************************************
 *  ClearBuffer
 *  Leert das Buffer bis zum letzten Zeilenumbruch
 *  Parameter: keine
 *  Ergebnis : nichts
 ***************************************************************************/
void clearBuffer();

/***************************************************************************
 *  ResetArray
 *  Setzt alle Werte im Array zurueck auf 0
 *  Parameter: a, count: Pointer auf Array welches auf null/reseted werden soll und Laenge des Arrays
 *  Ergebnis : nichts
 ***************************************************************************/
void resetArray(int *a, int count);

#endif // TOOLS_H
