//
// Created by liance on 28/11/2023.
//

#ifndef EXERCISES_DATABASE_H
#define EXERCISES_DATABASE_H

/***************************************************************************
 *  This module contains methods on saving and loading data to/from a xml file.
 *  It also holds the path to the save file and sanitizes the in,- output from the file.
 * Detailed information about each method and its arguments will be provided seperately.
 ***************************************************************************/

extern const char* dirName;
extern const char* fileName;

/***************************************************************************
 *  saveCalendar
 *  When the program is exited and the user agreed to saving, all appointments
 *      are saved in a xml. (See GetFilePath() for the location)
 *  Parameter: None
 *  Result: Returns 1 if everything went smoothly otherwise 0.
 ***************************************************************************/
int saveCalendar();

/***************************************************************************
 *  createAndOpenXmlFile
 *  Depending on the OS a folder and file is created at GetFilePath() and
 *      given rights if needed. Afterwards if the file did not already exist,
 *      a stream is opened and returned.
 *  Parameter:
 *      - windowsOS: 1 => windows, !=1 => other. Needed for file/folder creation.
 *  Result: Returns the opened file stream if successful and NULL if unsuccessful.
 ***************************************************************************/
FILE* createAndOpenXmlFile(unsigned short windowsOS);

/***************************************************************************
 *  openSaveFile
 *  Opens the xml save file in the given file mode.
 *  Parameter:
 *      - fileMode: r=read, w=write, a=append, t=text(default), b=binary
 *  Result: Returns the opened file stream if successful and NULL if unsuccessful.
 ***************************************************************************/
FILE* openSaveFile(char * fileMode);

/***************************************************************************
 *  loadCalendar
 *  When the program is started this function is called and tries to load all
 *      appointments saved in a xml file at GetFilePath() if it exists.
 *  Parameter: None
 *  Result: Returns 1 if everything went smoothly otherwise 0.
 ***************************************************************************/
int loadCalendar();

/***************************************************************************
 *  GetFilePath
 *  Tries to concatenate the dirName and fileName strings.
 *  Parameter: None
 *  Result: Returns the concatenated string if successful and NULL if unsuccessful.
 ***************************************************************************/
char* GetFilePath();

#endif //EXERCISES_DATABASE_H
