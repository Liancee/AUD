#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"

void q_sort(sAppointment *, int, int, int (*cmp_method)(sAppointment *, sAppointment *));
int partition(sAppointment *, int, int, int (*cmp_method)(sAppointment *, sAppointment *));
void swap(sAppointment *, sAppointment *);
int date_cmp(sDate, sDate);
int time_cmp(sTime, sTime);
int text_cmp(char *, char *);
int int_cmp(int, int);
int raise_sort_exception(char *);

void Quick_sort(sAppointment * calendar, int count, int (*cmp_method)(sAppointment *, sAppointment *))
{
  q_sort(calendar, 0, count - 1, cmp_method);
}

void q_sort(sAppointment * calendar, int lower_limit, int upper_limit, int (*cmp_method)(sAppointment *, sAppointment *))
{
  if (lower_limit >= upper_limit) return; // checks whether the lower limit is greater than or equal to the upper limit and exits if necessary

  int idx = partition(calendar, lower_limit, upper_limit, cmp_method); // compares appointments between the lower and upper limit
  q_sort(calendar, lower_limit, idx - 1, cmp_method); // recursive call for comparison between new limits
  q_sort(calendar, idx + 1, upper_limit, cmp_method); // recursive call for comparison between new limits
}

int partition(sAppointment * calendar, int lower_limit, int upper_limit, int (*cmp_method)(sAppointment *, sAppointment *))
{
  int i = lower_limit + 1, j = upper_limit;
  sAppointment * cmp = calendar + lower_limit;
  while (i <= j) // checks if lower limit is less or equal to upper limit
  {
    while (i <= j && (cmp_method(calendar + i, cmp) <= 0)) i++;
    while (j >= i && (cmp_method(calendar + j, cmp) >= 0)) j--;

    if (i < j)
    {
      swap(calendar + i, calendar + j);
      i++;
      j--;
    }
  }
  i--;
  swap(calendar + i, cmp);

  return i;
}

void swap(sAppointment * app1, sAppointment * app2)
{
  sAppointment tmp = *app1;
  *app1 = *app2;
  *app2 = tmp;
}

int Sort_date_time(sAppointment * app1, sAppointment * app2)
{
  int cmp_result = date_cmp(app1->Date, app2->Date);
  if (cmp_result) return cmp_result;
  else
  {
    cmp_result = time_cmp(app1->Time, app2->Time);
    if (cmp_result) return cmp_result;
    else return 0;
  }
}

int Sort_description(sAppointment * app1, sAppointment * app2)
{
  if (app1->Description && app2->Description) // both pointers are set <==> both have descriptions
  {
    int cmp_result = text_cmp(app1->Description, app2->Description); // descriptions are checked char by char (note that upper case in ascii is < than lower case)
    if (cmp_result) return cmp_result; // if they were not equal, a value >0 is returned if the first different character in str1 was greater than in str2, a value <0 if it was less than in str2
    else // the description were equal text_cmp returned 0
    {
      cmp_result = date_cmp(app1->Date, app2->Date); // dates are checked for difference in order year > month > day
      if (cmp_result) return cmp_result; // if date1 is smaller -1 is returned, elif date1 is greater 1, in case of equality 0.
      else // case 0
      {
        cmp_result = time_cmp(app1->Time, app2->Time); // time is checked for difference in order hour > minute > second
        if (cmp_result) return cmp_result; // if time1 is smaller -1 is returned, elif time1 is greater 1, in case of equality 0.
        else return 0; // no further investigation for inequality, 0 is returned which basically count as app1 < app2 => while loop continuous to search for an app with a greater value in the sorting field
      }
    }
  }
  else if (!app1->Description && app2->Description) return -1; // no description was set for app1 => pointer is NULL => it is counted in a way that app1 is < app2
  else if (app1->Description) return 1; // no description was set for app2 => pointer is NULL => it is counted in a way that app1 is > app2
  else return 0; // no descriptions were set for apps => pointers are both NULL => it is counted in a way that app1 is = app2, which just continuous the while loop to search for a greater value in the sorting field
}

int Sort_location(sAppointment * app1, sAppointment * app2)
{
  if (app1->Location && app2->Location)
  {
    int cmp_result = text_cmp(app1->Location, app2->Location);
    if (cmp_result) return cmp_result;
    else
    {
      cmp_result = date_cmp(app1->Date, app2->Date);
      if (cmp_result) return cmp_result;
      else
      {
        cmp_result = time_cmp(app1->Time, app2->Time);
        if (cmp_result) return cmp_result;
        else return 0;
      }
    }
  }
  else if (!app1->Location && app2->Location) return -1;
  else if (app1->Location) return 1;
  else return 0;
}


int Sort_duration(sAppointment * app1, sAppointment * app2)
{
  if (app1->Duration && app2->Duration)
  {
    int cmp_result = time_cmp(*(app1->Duration), *(app2->Duration));
    if (cmp_result) return cmp_result;
    else
    {
      cmp_result = date_cmp(app1->Date, app2->Date);
      if (cmp_result) return cmp_result;
      else
      {
        cmp_result = time_cmp(app1->Time, app2->Time);
        if (cmp_result) return cmp_result;
        else return 0;
      }
    }
  }
  else if (!app1->Duration && app2->Duration) return -1;
  else if (app1->Duration) return 1;
  else return 0;
}

int date_cmp(sDate d1, sDate d2)
{
  int diff = int_cmp(d1.Year, d2.Year);
  if (diff) return diff;
  else
  {
    diff = int_cmp(d1.Month, d2.Month);
    if (diff) return diff;
    else
    {
      diff = int_cmp(d1.Day, d2.Day);
      if (diff) return diff;
      else return 0;
    }
  }
}

int time_cmp(sTime t1, sTime t2)
{
  int diff = int_cmp(t1.Hours, t2.Hours);
  if (diff) return diff;
  else
  {
    diff = int_cmp(t1.Minutes, t2.Minutes);
    if (diff) return diff;
    else
    {
      diff = int_cmp(t1.Seconds, t2.Seconds);
      if (diff) return diff;
      else return 0;
    }
  }
}

int text_cmp(char * s1, char * s2)
{
  return strcmp(s1, s2);
}

int int_cmp(int a, int b)
{
  return a - b;
}

int raise_sort_exception(char * text)
{
  fprintf(stderr, "Error while trying to sort by %s.\nProgram will now exit. ", text);
  waitForEnter("exit");

  return 1;
}
