#include <stdio.h>
#include <stdlib.h>
#include "list.h"

sAppointment *First = NULL, *Last = NULL;

int InsertInDList(sAppointment * new, int (*cmp_method)(sAppointment *, sAppointment *))
{
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
