
#ifndef EXERCISES_LIST_H
#define EXERCISES_LIST_H
#include "datastructure.h"

/***************************************************************************
 *  This module contains methods for manipulating the doubly linked list that
 *  holds all the different linked appointments as dynamically allocated
 *  sAppointments.
 *  Detailed information about each method and its arguments will be provided
 *  separately.
 ***************************************************************************/

/***************************************************************************
*  InsertInDList
*  A method that establishes the necessary linking in the list between the
*      new appointment struct and the old ones. (Inserted by Date -> Time)
*  Parameter:
*      - new: the appointments that is to be inserted into the doubly linked list
*      - (*cmp_method): the inserting specifier (Date -> Time by default)
*  Result: Returns 0 on success and 1 by failure.
***************************************************************************/
int InsertInDList(sAppointment * new, int (*cmp_method)(sAppointment *, sAppointment *));

/***************************************************************************
 *  RemoveFromDList
 *  A method that removes the linking in the list between the appointment
 *       struct to be removed and the old ones. Since the appointment is
 *       allocated dynamically, a pointer is removed for freeing or other
 *       purposes.
 *  Parameter:
 *      - rm: the first appointment that is to be removed from the doubly linked list
 *      - (*cmp_method): the specifier to find the appointment that is to be
 *        removed (Date -> Time by default)
 *  Result: Returns a pointer to the now detached sAppointment for further
 *    usage (e.g. freeing).
 ***************************************************************************/
sAppointment * RemoveFromDList(sAppointment * rm, int (*cmp_method)(sAppointment *, sAppointment *));

/***************************************************************************
 *  AppendInSList
 *  A method that establishes the necessary linking in the hash list between the
 *      new appointment struct and the other ones.
 *  Parameter:
 *      - hashEntry: The hash entry in which is to be appended.
 *      - app: The appointment that is to be appended with a new sListEntry.
 *  Result: Returns 0 on success and 1 by failure.
 ***************************************************************************/
int AppendInSList(sHashEntry * hashEntry, sAppointment * app);

/***************************************************************************
 *  RemoveFromSList
 *  A method that removes the linking in the hash list between the sListEntry
 *       struct to be removed and the other ones. Since the appointment is
 *       allocated dynamically, a pointer is removed for freeing or other
 *       purposes.
 *  Parameter:
 *      - hashEntry: One hash table element that can hold multiple sListEntries.
 *      - app: The appointment that indicates which sListEntry is to be removed.
 *  Result: Returns a pointer to the now detached sListEntry for further
 *    usage (e.g. freeing).
 ***************************************************************************/
sListEntry * RemoveFromSList(sHashEntry * hashEntry, sAppointment * app);

#endif //EXERCISES_LIST_H
