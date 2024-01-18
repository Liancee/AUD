#include <stdio.h>
#include <string.h>
#include "search.h"
#include "tools.h"


sListEntry * searchFirst(sHashEntry * hashTable, sAppointment * searchAppointment, int (*cmp)(sAppointment *, sAppointment *))
{
  int hash = DivRest(searchAppointment->Description);
  sListEntry * tmp = (hashTable + hash)->First;
  while (tmp)
  {
    // strcmp is gating us from a case-insensitive search
    if (!strcmp(tmp->Appointment->Description, searchAppointment->Description)) return tmp; // the task needs us to add a 'Sort_Only_Description' method in sort.c and use it here
    tmp = tmp->Next;
  }
  return NULL;
}

sListEntry * searchNext(sHashEntry * hashTable, sAppointment * result, int (*cmp)(sAppointment *, sAppointment *))
{
  int hash = DivRest(result->Description);
  sListEntry * tmp = (hashTable + hash)->First;
  while (tmp)
  {
    if (tmp->Appointment == result) // skip first already found one from searchFirst()
    {
      tmp = tmp->Next;
      break;
    }
    tmp = tmp->Next;
  }
  while (tmp)
  {
    // strcmp is gating us from a case-insensitive search

    if (!strcmp(tmp->Appointment->Description, result->Description)) return tmp;
    tmp = tmp->Next;
  }
  return NULL;
}

int DivRest(char * desc)
{
  int result = 0;
  while (*desc) result += ToUpper(*desc++);
  return result % MAXINDEX;
}
