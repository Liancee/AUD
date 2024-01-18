#ifndef EXERCISES_SEARCH_H
#define EXERCISES_SEARCH_H
#include "datastructure.h"

/***************************************************************************
 *  This module contains methods for searching in the hash table and the
 *  corresponding hashing method.
 *  Detailed information about each method and its arguments will be provided
 *  separately.
 ***************************************************************************/

/***************************************************************************
*  searchFirst
*  Searches for the first matching appointment in the hash table.
*  Parameter:
*      - hashTable: A pointer to the hash table where all the hash values
*         for searching are stored in.
 *     - searchAppointment: The appointment holding the value that is to be
*         searched for.
 *     - cmp: The comparing component for finding the matching appointment.
*  Result: Returns the sListEntry that holds the matching appointment, if
*     no matching appointment could be found NULL is returned.
***************************************************************************/
sListEntry * searchFirst(sHashEntry * hashTable, sAppointment * searchAppointment, int (*cmp)(sAppointment *, sAppointment *));

/***************************************************************************
*  searchNext
*  Searches for the next matching appointment in the hash table.
*  Parameter:
*      - hashTable: A pointer to the hash table where all the hash values
*         for searching are stored in.
 *     - result: Since this is searchNext, result is the previous found
*         appointment.
 *     - cmp: The comparing component for finding the matching appointment.
*  Result: Returns the sListEntry that holds the matching appointment, if
*     no matching appointment could be found NULL is returned.
***************************************************************************/
sListEntry * searchNext(sHashEntry * hashTable, sAppointment * result, int (*cmp)(sAppointment *, sAppointment *));

/***************************************************************************
*  DivRest
*  Converts a string into a hash by adding the ascii value of every char in
*      string as upper case and modulos it with the max count of the hashtable.
*  Parameter:
*      - desc: The string that is to be hashed.
*  Result: Returns the hashed value as int.
***************************************************************************/
int DivRest(char * desc);

#endif //EXERCISES_SEARCH_H
