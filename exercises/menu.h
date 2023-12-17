#ifndef MENU_H
  #define MENU_H

  /***************************************************************************
   *  This module contains methods to display a menu
    Detailed information about each method and its arguments will be provided
    seperately.
   ***************************************************************************/

  /***************************************************************************
   *  GetMenu
   *  Method that outputs a given title for a menu and the given submenu,
   *      afterwards returns the selection of the submenu chosen by the user
   *  Parameter:
   *      menuTitle - Pointer to a string containing the title of the menu
   *      menuItems- Pointer to an array of strings containing the submenu choices
   *      countMenuItems - the count of the choosable submenu options as int
   *  Result: Returns the submenu choice of the user
   ***************************************************************************/
  int GetMenu(char *menuTitle, char *menuItems[], int countMenuItems);

#endif // MENU_H
