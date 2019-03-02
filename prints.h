#ifndef _PRINTS_H_
#define _PRINTS_H_

/*************************************************************************//**
 * @file prints.h
 * @brief Functions for displaying word statistics
 *****************************************************************************/

#include "HashTable.h"
#include "functions.h"
#include <iostream>
#include <iomanip>

void displayInfo(char** argv, HashTable &hash, double elapsedTime);
string getFilenames(string originalName);
void displayOutputwrd(string outputFile, int total, int unique, Hash* hash);
void displayOutputcsv(string outputFile, int total, int unique, Hash* hash);
double getAvgRank(Hash* hash, int start, int end, int unique);
void displayRanks(ofstream &fout, Hash* hash, int start, int end, int unique);

#endif
