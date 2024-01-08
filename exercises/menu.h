#ifndef MENU_H
  #define MENU_H

  /***************************************************************************
   *  This module contains methods to display a menu
   *  Detailed information about each method and its arguments will be provided
   *  separately.
   ***************************************************************************/

  /***************************************************************************
   *  GetMenu
   *  Method that outputs a given title for a menu and the given submenu,
   *      afterwards returns the selection of the submenu chosen by the user
   *  Parameter:
   *      menuTitle - Pointer to a string containing the title of the menu
   *      menuItems- Pointer to an array of strings containing the submenu choices
   *      countMenuItems - the count of the choosable submenu options as int
   *      startAtZero - when 0 the menu listing will start at 0 and the user
   *        input of 0 is tolerated else from 1 onwards.
   *  Result: Returns the submenu choice of the user
   ***************************************************************************/
  int GetMenu(char *menuTitle, char *menuItems[], int countMenuItems, unsigned short startAtZero);

#endif // MENU_H
