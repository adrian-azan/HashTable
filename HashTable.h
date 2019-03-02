#ifndef _HashTable_h_
#define _HashTable_h_

/*************************************************************************//**
 * @file HashTable.h
 * @brief HashTable Header File
 *****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h>
#include <chrono>

using namespace std;


/***************************************************************************//**
 * @struct Hash
 * @brief Hash structure to hold frequency and word
 ******************************************************************************/

struct Hash
{
	string word = "";	/*!<string to hold the word*/
	int freq = 0;	/*!<variable to hold the frequency of the word*/
};


/***************************************************************************//**
 * @class HashTable
 * @brief Includes interface for the hash table
 ******************************************************************************/

class HashTable
{
public:
	HashTable();
	HashTable(int size);
	~HashTable();

	void insert(string word);
	int find(string word);
	void remove(string word);
	void rehash();
	void copyHash(Hash original);
	int hashKey(string word);
	int getTotal();
	int getUnique();
	Hash* getHash();
	void sort();

private:
	int nextPrime();	/*!<variable to hold the next prime number for tableSize*/

protected:
	Hash* hashVals;		/*!<array of Hashes for the hash table*/
	int tableSize = 997;	/*!<variable to hold the size of the hash table*/
	int totalWords = 0;		/*!<variable to hold the total number of words read in*/
	int uniqueWords = 0;	/*!<variable to hold the number of unique words read in*/

};


#endif
