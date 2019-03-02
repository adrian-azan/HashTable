/*************************************************************************//**
 * @file HashTable.cpp
 * @brief Fucntions for HashTable Class
 *****************************************************************************/

#include "HashTable.h"

/*************************************************************************//**
 * @author Adrian Azan 
 *
 * @par Description
 * Creates an instance of the hash table with size 997
 *
 ****************************************************************************/
HashTable::HashTable()
{
	hashVals = new Hash[997];
}

/*************************************************************************//**
 * @author Adrian Azan 
 *
 * @par Description
 * Creates an instance of the hash table with a variable size 
 *
 ****************************************************************************/
HashTable::HashTable(int size)
{
	hashVals = new Hash[size];
	tableSize = size;
}

/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Destroys the instance of the hash table
 *
 ****************************************************************************/
HashTable::~HashTable()
{
	delete [] hashVals;
}


/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Hashes a word and inserts into HashTable. Checks if the word has been Added
 * before. Increases unique word count if word is unique. Increases totalWord
 * count. If unique words is 3/4 of HashTable size, Rehashing.
 *
 * @param[in] newWord - Word to be hashed and inserted
 *
 ****************************************************************************/
void HashTable::insert(string newWord)
{
	//find hash key
    int key = hashKey(newWord);

	if (hashVals[key].freq == 0)
	{
		hashVals[key].word = newWord;
		uniqueWords++;
	}

	hashVals[key].freq ++;
	totalWords++;


	//checks load factor of hash table and rehashes if necessary
	if ( double(uniqueWords) / double(tableSize) >= .75)
		rehash();
}


/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Hashes word to key. Returns key if the word at that index is original word
 *
 * @param[in] word - Word to be searched for
 *
 * @return key if found, -1 if not found
 ****************************************************************************/
int HashTable::find(string word)
{
	int key = hashKey(word);
	
	if (hashVals[key].word == word)
		return key;
	
	return -1;
}

/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Checks if word is found in the hash table. Clears values at that index if
 * the word was found
 *
 * @param[in] word - Word to be removed
 *
 ****************************************************************************/
void HashTable::remove(string word)
{
	int key = find(word);

	if(key != -1)
	{
		//reset node to empty
		hashVals[key].word = "";
		hashVals[key].freq = 0;
	}
}

/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Increases size of hashtable once it is 75% full. Creates a new hashtable, 
 * copies all values from old hashtable to new hashtable. Resizes old 
 * hashtable copies values back 
 *	
 ****************************************************************************/
void HashTable::rehash()
{
	int oldTableSize = tableSize;
	tableSize = nextPrime();
	HashTable newHash(tableSize);


	cout << "Rehashing" << endl;
	
	//Copies old words into newHash with different keys
	for (int i = 0; i < oldTableSize; i ++)
	{
		if (hashVals[i].word != "")
		{
			newHash.copyHash(hashVals[i]);
		}
	}
	
	//Deletes old hashVals to resize
	delete [] hashVals;
	hashVals = new Hash [tableSize];	
	
	for (int i = 0; i < tableSize; i ++)
	{
		//Returns all values to newly sized hashVals
		if (newHash.hashVals[i].word != "")
		{
			hashVals[i] = newHash.hashVals[i];
		}
	}
	
}

/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Copies values from old sized hash table into resized hash table
 *
 *@param[in] original - hash table before rehashing began	
 ****************************************************************************/
void HashTable::copyHash(Hash original)
{
	unsigned int key = hashKey(original.word);
	
	hashVals[key].freq = original.freq;
	hashVals[key].word = original.word;
	
}

/*************************************************************************//**
 * @author Prof. Weiss and Adrian Azan
 *
 * @par Description
 * Turns a word into an index. Multiplies word value by 37 and then adds
 * letter value.
 * Probes to find actual index to insert word, if necessary
 *
 * @param[in] word - Word to be turned into index value
 *
 * @return key index value for Hash Table
 *
 ****************************************************************************/
int HashTable::hashKey(string word)
{
  	unsigned int key = 0;

    for (char ch : word )
        key = 37 * key + ch;
	
	key = key % tableSize;
	
	//Linearly probes hashVals until correct word or blank space
	while (hashVals[key].word != "" && hashVals[key].word != word)
	{
		if (key < unsigned(tableSize-1))
			key++;
		else
			key = 0;
	}
	
    return key;
}


/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Finds the next prime number for Hash table size. Multiplies current
 * Hashtable size by 2 and then finds next biggest prime number
 *
 * @return New table size
 *
 ****************************************************************************/
int HashTable::nextPrime()
{
	int newPrime = tableSize * 2 + 1;
	bool isPrime = false;

	while (!isPrime)
	{
		isPrime = true;
		for (int i = 3; i < newPrime / 2; i += 2)
		{
			if (newPrime % i == 0)
			{

				isPrime = false;
				newPrime += 2;
				break;
			}
		}

	}

	return newPrime;
}

/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Retrieves the amount of words read from file
 *
 * @return Total amount of words read
 *
 ****************************************************************************/
int HashTable::getTotal()
{
	return totalWords;
}

/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Retrievs the amount of unique words read from file
 *
 * @return Total amount of unique words
 *
 ****************************************************************************/
int HashTable::getUnique()
{
	return uniqueWords;
}


/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Retrievs the hash table from the file
 *
 * @return Pointer to hash table
 *
 ****************************************************************************/
Hash* HashTable::getHash()
{
	return hashVals;
}


/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Compares the frequency of two words in the hash table
 *
 * @param[in] a - pointer to first word
 * @param[in] b - pointer to second word
 * 
 * @return If word frequency is out of order
 *
 ****************************************************************************/
int compareFreq(const void *a, const void* b)
{
  int l = ((struct Hash*)a)->freq;
  int r = ((struct Hash*)b)->freq; 
  return (r - l);
}


/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Compares the frequency and alphabetical order of two words in the hash 
 * table
 *
 * @param[in] a - pointer to first word
 * @param[in] b - pointer to second word
 *
 * @return If words aren't in alphabetical order based on frequency
 *
 ****************************************************************************/
int compareAlpha(const void *a, const void *b)
{
  int l = ((struct Hash*)a)->freq;
  int r = ((struct Hash*)b)->freq; 

  string one = ((struct Hash*)a)->word;
  string two = ((struct Hash*)b)->word;

  //only compare within same frequency
  if(l == r)
	return one.compare(two);  

  return 0;
}

/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Sorts the hash table first by word frequency and then alphabetically 
 * within the frequency
 *
 ****************************************************************************/
void HashTable::sort()
{
	qsort(hashVals, tableSize, sizeof(Hash), compareFreq);

	qsort(hashVals, tableSize, sizeof(Hash), compareAlpha);

}







