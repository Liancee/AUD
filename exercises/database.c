//
// Created by liance on 28/11/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "database.h"
#include "tools.h"
#include "datetime.h"
#include "escapesequenzen.h"

#ifdef _WIN32
  #include <Windows.h>
  #define PATH_SEPARATOR "\\"
#else
  #include <unistd.h>
  #include <errno.h>
  #define PATH_SEPARATOR "/"
#endif

const char * dirName = "./Data";
const char * fileName = "calendar.xml";

typedef enum
{
  dateOffset = 6,
  timeOffset = 6,
  descriptionOffset = 13,
  locationOffset = 10,
  durationOffset = 10,
  appointmentStartOffset = 13,
  appointmentEndOffset = 14,
  calendarEndOffset = 11
} eTagOffsets;

void saveAppointment(sAppointment, FILE *);
char* getValue(char *, eTagOffsets);
int raiseXmlLoadException(char *);
int loadAppointment(FILE *, sAppointment *);
void appointmentCleanup(sAppointment *);

int saveCalendar()
{
  // if (!CountAppointments) // we could ask if there are any appointments but then the file would not be created, so we create an empty file

  sAppointment * pCal = Calendar;

  FILE * file = createAndOpenXmlFile(); // TODO if the windows compiler is too old \\ has to be used instead of / (see line 11-17) (but probably somewhere inside of function)
  if (!file)
    return 0;

  fprintf(file, "<Calendar>\n");
  int i = 0;
  // TODO in the line below we get an error if we dont directly write into calendar in createAppointment() in calendar.c cuz we have to access the sDate struct differently
  while (pCal->Date.Day) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
  {
    i++;
    saveAppointment(*pCal, file);
    if (i == MAXAPPOINTMENTS)
      break;

    pCal++;
  }
  fprintf(file, "</Calendar>\n");

  fclose(file);

  FORECOLOR_GREEN;
  // snprintf(this: dirName, fileName -> into this: %s/%s) => filePath; realpath(filePath, actualPath) => output actualPath; but for some reason realpath() func cannot be found in stdlib.h?!
  printf("\nSaved in: \'%s/%s\'\n\n", dirName, fileName);
  FORECOLOR_WHITE;
  printf("Program will now exit. ");
  waitForEnter("continue");

  return 1;
}

void saveAppointment(sAppointment app, FILE * file)
{
  fprintf(file, "\t<Appointment>\n");

  fprintf(file, "\t\t<Date>%02i.%02i.%04i</Date>\n", app.Date.Day, app.Date.Month, app.Date.Year);

  fprintf(file, "\t\t<Time>%02i:%02i:%02i</Time>\n", app.Time.Hours, app.Time.Minutes, app.Time.Seconds == -1 ? 00 : app.Time.Seconds);

  if (app.Description)
    fprintf(file, "\t\t<Description>%s</Description>\n", app.Description);

  if (app.Location)
    fprintf(file, "\t\t<Location>%s</Location>\n", app.Location);

  if (app.Duration && (app.Duration->Hours || app.Duration->Minutes || app.Duration->Seconds > 0)) // TODO this has to be changed according to the duration input changes; >0 is important cuz if sec not set => -1
    fprintf(file, "\t\t<Duration>%02i:%02i:%02i</Duration>\n", app.Duration->Hours, app.Duration->Minutes, app.Duration->Seconds == -1 ? 00 : app.Duration->Seconds);

  fprintf(file, "\t</Appointment>\n");
}

FILE * createAndOpenXmlFile()
{
  FILE * file;
  char * fileMode = "wt";

#ifdef _WIN32
  if (!mkdir(dirName) || errno == EEXIST)
  {
    file = openSaveFile(fileMode);
    if (!file)
      return NULL;
  }
  /*else if (errno == EEXIST)
  {
    file = openSaveFile(fileMode);
    if (!file)
      return NULL;
  }*/
  else
  {
    fprintf(stderr, "Error when creating '%s'. ", dirName);
    waitForEnter("continue");
    return NULL;
  }
#else
  if (!mkdir(dirName, 0777))
    {
      file = openSaveFile(fileMode);
      if (!file)
        return NULL;
    }
    else if (errno == EEXIST)
    {
      file = openSaveFile(fileMode);
      if (!file)
        return NULL;
    }
    else
    {
      fprintf(stderr, "Error when creating or setting the rights for '%s'. ", dirName);
      waitForEnter("continue");
      return NULL;
    }
#endif

  return file;
}

FILE * openSaveFile(char * fileMode)
{
  char * filePath = GetFilePath();
  if (!filePath || (strchr(fileMode, 'r') && access(filePath, F_OK)))
    return NULL;

  FILE * file;
  file = fopen(filePath, fileMode);
  if (!file)
  {
    fprintf(stderr, "Error could not open save file at: '%s'. ", filePath);
    free(filePath);
    filePath = NULL;
    waitForEnter("continue");
    return NULL;
  }
  free(filePath);
  filePath = NULL;
  return file;
}

char* GetFilePath()
{
  size_t pathLength = strlen(dirName) + strlen(fileName) + 5;  // extra characters for "/ + NULL terminator"
  char * filePath = malloc(pathLength);
  if (filePath)
    snprintf(filePath, pathLength, "%s/%s", dirName, fileName);
  else
    return RaiseMallocException("filePath") == 0 ? NULL : NULL;

  return filePath;
}

int loadCalendar()
{
  sAppointment * pCal = Calendar;

  char * fileMode = "rt";
  FILE * file = openSaveFile(fileMode);
  if (file)
  {
    char * row = malloc(20), * pRow; // TODO 20 => estimated max char count if longest tag + <> and \t or ' '; might be to change if longer tags get added; anything after 20 should be cleared by fclearBuffer()?
    if (!row)
      return RaiseMallocException("row");

    do
    {
      *row = '\0'; // why this? so it is initialized, or we definitely have an end?
      fscanf(file, "%19[^\n]", row);
      fclearBuffer(file);
      pRow = row;

      while (*pRow == ' ' || *pRow == '\t')
        pRow++;

      if (!strncmp(pRow, "<Appointment>", appointmentStartOffset))
      {
        if (!loadAppointment(file, pCal)) // TODO ask: instead of using a pointer pCal, replace it with Calendar[CountAppointments] everywhere? -> then loadAppointment would need pCal as parameter
          return 0;
        else
        {
          appointmentCleanup(pCal);

          pCal++;
          CountAppointments++;

          if (CountAppointments == MAXAPPOINTMENTS)
          {
            char * filePath = GetFilePath();
            fprintf(stderr, "Loading appointments from %s stopped at the allowed max. count (%i) of the standard version.\nPlease upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [$(5)$]\n\n", filePath, MAXAPPOINTMENTS);
            waitForEnter("continue");
            free(filePath);

            free(row);
            row = NULL;
            pRow = NULL;
            fclose(file);

            return 1;
          }
        }
      }
      else if (!strncmp(pRow, "</Calendar>", calendarEndOffset))
        break;
      else if (feof(file))
        return raiseXmlLoadException("</Calendar>"); // TODO if CRLF is missing at eof we get here too..
      /*else
        raiseXmlLoadException("file corrupt");*/

    } while (strncmp(pRow, "</Calendar>", calendarEndOffset));

    free(row);
    row = NULL;
    pRow = NULL;
  }
  else
    return 1; // there is no file to be loaded

  fclose(file);

  return 1;
}

void appointmentCleanup(sAppointment * app)
{
  if (!app->Date.Day && !app->Date.Month && !app->Date.Year)
    exit(!raiseXmlLoadException("<Date>"));

  if (!app->Time.Seconds && !app->Time.Minutes && !app->Time.Hours)
    exit(!raiseXmlLoadException("<Time>"));
  else if (!app->Time.Seconds)
    app->Time.Seconds = -1; // seconds are optional and if not set they are still saved in the xml as 00, so if that is the case seconds were not set and internally not set seconds are handled as -1

  if (app->Duration)
  {
    if (!app->Duration->Seconds && !app->Duration->Minutes && !app->Duration->Hours)
      exit(!raiseXmlLoadException("<Duration>")); // TODO THIS IS FALSE THO SINCE RN U STILL CAN INPUT 00:00:00
    else if (!app->Duration->Seconds)
      app->Duration->Seconds = -1; // TODO if duration will be nullable this has to be changed
  }
}

int loadAppointment(FILE * file, sAppointment * app) // TODO is it better to give the struct oder pointer?
{
  char * row = malloc(150), * pRow;
  if (!row)
    return RaiseMallocException("row");

  do
  {
    *row = '\0'; // why this? so it is initialized, or we definitely have an end?
    fscanf(file, "%149[^\n]", row);
    fclearBuffer(file);
    pRow = row;

    while (*pRow == ' ' || *pRow == '\t')
      pRow++;
    if (!strncmp(pRow, "<Date>", dateOffset))
    {
      char * date = getValue(pRow, dateOffset);
      if (date)
      {
        if (!GetDateFromString(date, &(app->Date)))
          return raiseXmlLoadException("Date");
      }
      else
          return raiseXmlLoadException("Date");
    }
    else if (!strncmp(pRow, "<Time>", timeOffset))
    {
      char * time = getValue(pRow, dateOffset);
      if (time)
      {
        if (!GetTimeFromString(time, &(app->Time)))
          return raiseXmlLoadException("Time");
      }
      else
        return raiseXmlLoadException("Time");
    }
    else if (!strncmp(pRow, "<Description>", descriptionOffset))
    {
      char * desc = getValue(pRow, descriptionOffset);
      if (desc)
      {
        if (app->Description) // TODO If a tag occurs wrongly twice we free the first entry and take the second
          free(app->Description); // TODO maybe ask user if he wants the first or second? could even show both values with desc(new) and app->Description(old)

        app->Description = malloc(strlen(desc) + 1);
        if (app->Description)
          strcpy(app->Description, desc);
        else
          return RaiseMallocException("app->Description");
      }
      else
        app->Description = NULL;
    }
    else if (!strncmp(pRow, "<Location>", locationOffset))
    {
      char * loc = getValue(pRow, locationOffset);
      if (loc)
      {
        if (app->Location) // TODO If a tag occurs wrongly twice we free the first entry and take the second
          free(app->Location); // TODO maybe ask user if he wants the first or second? could even show both values with desc(new) and app->Description(old)

        app->Location = malloc(strlen(loc) + 1);
        if (app->Location)
          strcpy(app->Location, loc);
        else
          return RaiseMallocException("app->Location");
      }
      else
        app->Location = NULL;
    }
    else if (!strncmp(pRow, "<Duration>", durationOffset))
    {
      if (app->Duration)
        free(app->Duration); // TODO If a tag occurs wrongly twice we free the first entry and take the second; maybe ask user if he wants the first or second? cant show values here tho

      char * dur = getValue(pRow, durationOffset);
      if (dur)
      {
        app->Duration = malloc(sizeof(sTime));
        if (app->Duration)
        {
          if (!GetTimeFromString(dur, app->Duration)) // TODO has also to be changed perhaps later on if it should be nullable
            return raiseXmlLoadException("Duration");
        }
        else
          return RaiseMallocException("app->Duration");
      }
      else
        app->Duration = NULL;
    }
    else if (feof(file))
      return raiseXmlLoadException("</Appointment>");

  } while (strncmp(pRow, "</Appointment>", appointmentEndOffset));

  free(row);
  row = NULL;
  pRow = NULL;

  return 1;
}

char * getValue(char * row, eTagOffsets tagOffset)
{
  unsigned short len = 0;
  row += tagOffset;
  char * start = row;

  while ((*row != '<') && (*row != '\0'))
  {
    row++;
    len++;
  }
  if (len)
  {
    *(start + len) = '\0';
    return start;
  }
  else
    return NULL;
}

int raiseXmlLoadException(char* tag)
{
  char * filePath = GetFilePath();
  fprintf(stderr, "Critical error while trying to load appointments from %s.\n%s is a mandatory field and was either not found or illegally empty!\nProgram will now exit. ", filePath, tag); // TODO.11 ask can I somehow directly use GetFilePath() and free it afterwards?
  free(filePath);
  filePath = NULL;
  waitForEnter("continue");
  return 0;
}
