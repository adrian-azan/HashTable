#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*************************************************************************//**
 * @file functions.h
 * @brief Functions for retrieving and formatting words from source file
 *****************************************************************************/

#include "HashTable.h"

using namespace std;

void ArguementCheck(int NumberOfArguments);

void getWords(string inputLine, HashTable &temp);

string makeLowerCase(string input);

string formatWords(string input);


/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Opens files and checks for completion
 *
 * @param[in] fileName - name of file
 * @param[in,out]  fileObject - type of filestream
 *
 ****************************************************************************/
template <class FileType>
void OpenAndCheckFile(string fileName, FileType &fileObject)
{
  fileObject.open(fileName);

  if (!fileObject)
  {
    cout << fileName <<" COULD NOT OPEN..... EXITING" << endl;
    exit(1);
  }
}




#endif
