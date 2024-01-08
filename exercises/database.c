#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "database.h"
#include "tools.h"
#include "datetime.h"
#include "escapesequenzen.h"
#include "list.h"
#include "sort.h"

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
  date_offset = 6,
  time_offset = 6,
  description_offset = 13,
  location_offset = 10,
  duration_offset = 10,
  appointment_start_offset = 13,
  appointment_end_offset = 14,
  calendar_start_offset = 10,
  calendar_end_offset = 11
} eTagOffsets;

void saveAppointment(sAppointment, FILE *);
char* getValue(char *, eTagOffsets);
int raiseXmlLoadException(char *, unsigned short);
int loadAppointment(FILE *, sAppointment *,  unsigned short *);
void appointment_sanitization(sAppointment *, unsigned short);
int raiseAlreadyLoadedException(char *, unsigned short);

int saveCalendar()
{
  // if (!CountAppointments) // we could ask if there are any appointments but then the file would not be created, so we create an empty file

  sAppointment * pApp = First;

  FILE * file = createAndOpenXmlFile(); // TODO if the windows compiler is too old \\ has to be used instead of / (see line 11-17) (but probably somewhere inside of function)
  if (!file) return 0;

  fprintf(file, "<Calendar>\n");

  while (pApp) // since day is a mandatory field and is validated (>1) we use this to go through every created appointment
  {
    saveAppointment(*pApp, file);

    pApp = pApp->Next;
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

  if (app.Description) fprintf(file, "\t\t<Description>%s</Description>\n", app.Description);

  if (app.Location) fprintf(file, "\t\t<Location>%s</Location>\n", app.Location);
  // Seconds > 0 is important cuz if sec not set => -1
  if (app.Duration && (app.Duration->Hours || app.Duration->Minutes || app.Duration->Seconds > 0)) fprintf(file, "\t\t<Duration>%02i:%02i:%02i</Duration>\n", app.Duration->Hours, app.Duration->Minutes, app.Duration->Seconds == -1 ? 00 : app.Duration->Seconds);

  fprintf(file, "\t</Appointment>\n");
}

FILE * createAndOpenXmlFile()
{
  FILE * file;
  char * fileMode = "wt";

#ifdef _WIN32
  if (!mkdir(dirName) || errno == EEXIST) // TODO needed to add constants F_OK and EEXIST?
  {
    file = openSaveFile(fileMode);
    if (!file) return NULL;
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
  if (!filePath || (strchr(fileMode, 'r') && access(filePath, F_OK))) return NULL;

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
  if (filePath) snprintf(filePath, pathLength, "%s/%s", dirName, fileName);
  else return RaiseMallocException("filePath") == 0 ? NULL : NULL;

  return filePath;
}

int loadCalendar()
{
  char * fileMode = "rt";
  FILE * file = openSaveFile(fileMode);
  if (file)
  {
    char * row = malloc(20), * pRow; // TODO 20 => estimated max char count if longest tag + <> and \t or ' '; might be to change if longer tags get added; anything after 20 should be cleared by fclearBuffer()?
    if (!row) return RaiseMallocException("row");

    unsigned short line = 0;
    do
    {
      *row = '\0'; // why this? so it is initialized, or we definitely have an end?
      fscanf(file, "%19[^\n]", row);
      fclearBuffer(file);
      pRow = row;
      line++;

      while (*pRow == ' ' || *pRow == '\t') pRow++;

      if (!strncmp(pRow, "<Appointment>", appointment_start_offset))
      {
        /* the following initialization will 0/NULL is really important, cuz when only declared, it was always the same
        block, which resulted in following appointments when not having specified certain values having them from
        previous appointment since the values were still in memory. Now they are overwritten with NULL/0, so they will
        not have a value that is not theirs */
        sAppointment app = { { 0, 0, 0 }, { 0, 0, 0 }, NULL, NULL, NULL, NULL, NULL }, *appointment = NULL;
        //if (!app) return RaiseMallocException("app");

        if (!loadAppointment(file, &app, &line)) return 0;
        else
        {
          appointment_sanitization(&app, line);

          if (IsDateValid(app.Date.Day, app.Date.Month, app.Date.Year) && IsTimeValid(app.Time.Hours, app.Time.Minutes, app.Time.Seconds))
          {
            appointment = malloc(sizeof(sAppointment));
            if (appointment) *(appointment) = app; //appointment = &app; // TODO what happens here exactly? address to dynamic pointer or dynamic pointer to address?
            else return RaiseMallocException("appointment");
          }

          if(InsertInDList(appointment, Sort_date_time))
          {
            fprintf(stderr, "Critical error while trying to insert an appointment!\nProgram will now exit. ");
            waitForEnter("exit");
            return 0;
          }
          AppointmentCount++;

          // do not need below anymore after swapping to doubly linked list .. Sadge :(
          /*if (AppointmentCount == MAXAPPOINTMENTS)
          {
            char *filePath = GetFilePath();
            fprintf(stderr, "Loading appointments from %s stopped at the allowed max. count (%i) of the standard version.\nPlease upgrade to Appointment manager V 0.2 Pro to have more appointment slots! [$(5)$]\n\n", filePath, MAXAPPOINTMENTS);
            waitForEnter("continue");
            free(filePath);

            free(row);
            row = NULL;
            pRow = NULL;
            fclose(file);

            return 1;
          }*/
        }
      }
      else if (!strncmp(pRow, "<Calendar>", calendar_start_offset)) continue;
      else if (!strncmp(pRow, "</Calendar>", calendar_end_offset)) break;
      else if (feof(file)) return raiseXmlLoadException("</Calendar>", line);
      else
      {
        char *filePath = GetFilePath();
        fprintf(stderr, "Corrupt file, critical error while trying to load appointments from %s line %d. Program will now exit. \n", filePath, line);
        free(filePath);
        filePath = NULL;
        waitForEnter("continue");

        return 0;
      }

    } while (strncmp(pRow, "</Calendar>", calendar_end_offset));

    free(row);
    row = NULL;
    pRow = NULL;
  }
  else return 1; // there is no file to be loaded

  fclose(file);

  return 1;
}

void appointment_sanitization(sAppointment * app, unsigned short line)
{ // date was illegally loaded, we should never get here
  if (!app->Date.Day && !app->Date.Month && !app->Date.Year) exit(!raiseXmlLoadException("<Date>", line));
  // time was illegally loaded, we should never get here
  if (!app->Time.Seconds && !app->Time.Minutes && !app->Time.Hours) exit(!raiseXmlLoadException("<Time>", line));
  // seconds are optional and if not set they are still saved in the xml as 00, so if that is the case seconds were not set and internally not set seconds are handled as -1
  else if (!app->Time.Seconds) app->Time.Seconds = -1;

  if (app->Duration)
  {
    // *duration must either have values or duration is NULL, so we should never get here
    if (!app->Duration->Seconds && !app->Duration->Minutes && !app->Duration->Hours) exit(!raiseXmlLoadException("<Duration>", line));
    // same as in 'app->Time.Seconds = -1;' above
    else if (!app->Duration->Seconds) app->Duration->Seconds = -1;
  }
}

int loadAppointment(FILE * file, sAppointment * app, unsigned short * line)
{
  char * row = malloc(150), * pRow;
  if (!row) return RaiseMallocException("row");

  unsigned short d = 0, t = 0, de = 0, l = 0, du = 0;
  do
  {
    *row = '\0'; // why this? so it is initialized, or we definitely have an end?
    fscanf(file, "%149[^\n]", row);
    fclearBuffer(file);
    pRow = row;
    (*line)++;

    while (*pRow == ' ' || *pRow == '\t') pRow++;

    if (!strncmp(pRow, "<Date>", date_offset))
    {
      if (d)
        if(!raiseAlreadyLoadedException("Date", *line)) return 0;

      char * date = getValue(pRow, date_offset);
      if (date)
      {
        if (!GetDateFromString(date, &(app->Date))) return raiseXmlLoadException("Date", *line);
        else d = 1;
      }
      else return raiseXmlLoadException("Date", *line);
    }
    else if (!strncmp(pRow, "<Time>", time_offset))
    {
      if (t)
        if(!raiseAlreadyLoadedException("Time", *line)) return 0;

      char * time = getValue(pRow, date_offset);
      if (time)
      {
        if (!GetTimeFromString(time, &(app->Time))) return raiseXmlLoadException("Time", *line);
        else t = 1;
      }
      else return raiseXmlLoadException("Time", *line);
    }
    else if (!strncmp(pRow, "<Description>", description_offset))
    {
      char * desc = getValue(pRow, description_offset);
      if (desc)
      {
        if (de)
        {
          if(!raiseAlreadyLoadedException("Description", *line)) return 0;
          else if (app->Description) free(app->Description);
        }

        app->Description = malloc(strlen(desc) + 1);
        if (app->Description)
        {
          strcpy(app->Description, desc);
          de = 1;
        }
        else return RaiseMallocException("app->Description");
      }
      else app->Description = NULL;
    }
    else if (!strncmp(pRow, "<Location>", location_offset))
    {
      char * loc = getValue(pRow, location_offset);
      if (loc)
      {
        if (l)
        {
          if (!raiseAlreadyLoadedException("Location", *line)) return 0;
          else if (app->Location) free(app->Location);
        }

        app->Location = malloc(strlen(loc) + 1);
        if (app->Location)
        {
          strcpy(app->Location, loc);
          l = 1;
        }
        else return RaiseMallocException("app->Location");
      }
      else app->Location = NULL;
    }
    else if (!strncmp(pRow, "<Duration>", duration_offset))
    {
      char * dur = getValue(pRow, duration_offset);
      if (dur)
      {
        if (du)
        {
          if(!raiseAlreadyLoadedException("Duration", *line)) return 0;
          else if (app->Duration) free(app->Duration);
        }

        app->Duration = malloc(sizeof(sTime));
        if (app->Duration)
        {
          if (!GetTimeFromString(dur, app->Duration)) return raiseXmlLoadException("Duration", *line);
          else du = 1;
        }
        else return RaiseMallocException("app->Duration");
      }
      else app->Duration = NULL;
    }
    else if (feof(file)) return raiseXmlLoadException("</Appointment>", *line);

  } while (strncmp(pRow, "</Appointment>", appointment_end_offset));

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
  else return NULL;
}

int raiseXmlLoadException(char * tag, unsigned short line)
{
  char * filePath = GetFilePath();
  fprintf(stderr, "Critical error while trying to load appointments from %s line %d.\n%s is a mandatory field and was either not found or illegally empty!\nProgram will now exit. ", filePath, line, tag);
  free(filePath);
  filePath = NULL;
  waitForEnter("continue");
  return 0;
}

int raiseAlreadyLoadedException(char * tag, unsigned short line)
{
  char * filePath = GetFilePath();
  fprintf(stderr, "There was already a %s loaded for this appointment,\nperhaps there are two <%s> tags in line %d in one of your saved appointments?\n", tag, tag, line);
  if(!askYesOrNo("Press [y/Y] to continue loading (the second entry is loaded) or [n/N] to exit the program. "))
  {
    printf("\nSave file location: %s\n", filePath);
    waitForEnter("continue");
    free(filePath);
    filePath = NULL;
    return 0;
  }
  clearScreen();
  free(filePath);
  filePath = NULL;

  return 1;
}
