#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tools.h"
#include "search.h"

sAppointment *First = NULL, *Last = NULL;

int InsertInDList(sAppointment * new, int (*cmp_method)(sAppointment *, sAppointment *))
{
  if (!new) return (EXIT_FAILURE);

  sAppointment * tmp = First;

  if (!First)
  {
    First = Last = new;
    First->Next = First->Previous = NULL;
    return EXIT_SUCCESS;
  }

  if (cmp_method(First, new) >= 0) // insert as first
  {
    First->Previous = new;
    new->Next = First;
    First = new;
    return EXIT_SUCCESS;
  }

  if (cmp_method(Last, new) <= 0) // insert as last
  {
    new->Previous = Last;
    Last = Last->Next = new;
    return EXIT_SUCCESS;
  }

  while (tmp->Next) // insert somewhere in the middle
  {
    if (cmp_method(tmp->Next, new) >= 0)
    {
      new->Previous = tmp;
      new->Next = tmp->Next;
      tmp->Next->Previous = new;
      tmp->Next = new;
      return EXIT_SUCCESS;
    }
    tmp = tmp->Next;
  }
  return EXIT_FAILURE;
}

sAppointment * RemoveFromDList(sAppointment * rm, int (*cmp_method)(sAppointment *, sAppointment *))
{
  sAppointment * tmp = First, * tmp2 = NULL;
  if (!First) return NULL; // Empty list
  if (!cmp_method(First, rm)) // First element is that to be removed
  {
    First = First->Next;
    if (!First) Last = NULL;
    else First->Previous = NULL;
    return tmp;
  }

  while (tmp->Next)
  {
    if (!cmp_method(tmp->Next, rm))
    {
      tmp2 = tmp->Next;
      tmp->Next = tmp2->Next;
      if (!tmp->Next) Last = tmp;
      else tmp->Next->Previous = tmp;
      return tmp2;
    }
    tmp = tmp->Next;
  }
  return NULL;
}

int AppendInSList(sHashEntry * hashEntry, sAppointment * app)
{
  if (!hashEntry || !app) return (EXIT_FAILURE);

  sListEntry * listEntry = malloc(sizeof(sListEntry));
  if (!listEntry) return !RaiseMallocException("listEntry");
  listEntry->Appointment = app;
  listEntry->Next = NULL;

  if (!hashEntry->First)
  {
    hashEntry->First = hashEntry->Last = listEntry;
    return EXIT_SUCCESS;
  }
  else
  {
    hashEntry->Last = hashEntry->Last->Next = listEntry;
    return EXIT_SUCCESS;
  }
}

sListEntry * RemoveFromSList(sHashEntry * hashEntry, sAppointment * app)
{
  sListEntry * tmp = hashEntry->First;

  if (hashEntry->First->Appointment == app)
  {
    hashEntry->First = hashEntry->Last = NULL;
    return tmp;
  }
  else
  {
    sListEntry * previousListEntry = NULL;
    while (tmp)
    {
      /* tmp is initialized with first and that is already checked for. So in the first iteration the if condition will ALWAYS be false
       * and previousListEntry will be set to tmp, so the warnings in the if condition that tmp2 may be NULL is false */
      if (tmp->Appointment == app)
      {
        sListEntry * tmp2 = previousListEntry;
        if (tmp->Next) tmp2->Next = tmp->Next; // element is in the middle so previous one is connected with next one
        else tmp2->Next = NULL; // element is at the end so previous one is now last
        return tmp;
      }
      previousListEntry = tmp;
      tmp = tmp->Next;
    }
  }
  return NULL;
}