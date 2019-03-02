/*************************************************************************//**
 * @file functions.cpp
 * @brief Functions for retrieving and formatting words from source file
 *****************************************************************************/
#include "functions.h"


 /*************************************************************************//**
  * @author Adrian Azan
  *
  * @par Description
  * A function that checks if the right number of arguements. Exits program
  * if incorrect ammount is given.
  *
  * @param[in] NumberOfArguments - the number of arguments passed in
  *
  ****************************************************************************/
void ArguementCheck(int NumberOfArguments)
{
  if (NumberOfArguments != 2)
  {
    cout << "Incorrect Number of Arguements. Closing Program" << endl
    	 << "Program Usage: zipf textfile " << endl;
    exit(1);
  }
}

/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Tokenizes input line into words to be inserted into HashTable
 *
 * @param[in] inputLine - Line of words from original text file.
 * @param[in,out] hashTable - HashTable class.
 *
 ****************************************************************************/
void getWords(string inputLine, HashTable &hashTable)
{
  int size = inputLine.size();
  char* word;
  int i = 0;
  //list of symbols not allowed in words
  const char* badChars = "!@#$%^&*()_+-= `1234567890\"\n“:;<>,.?/\\|[]{}";

  char all[size+1];

  for(i = 0; i < size; i++)
    all[i] = inputLine[i];


  //null terminates end of string
  all[size] = '\0';

  //tokenizes words 
  word = strtok((char*)&all, badChars);

  //hashes word and inserts to hash table
  while(word != NULL)
    {
	if(isalpha(word[0]))
        	hashTable.insert(word);

		//tokenizes words
        word = strtok(NULL, badChars); 
    }

}

/*************************************************************************//**
 * @author Adrian Azan 
 *
 * @par Description
 * Takes input and converts all letters to lower case
 *
 * @param[in] input - Line of words from original text file.
 *
 * @return input in all lower case 
 ****************************************************************************/
string makeLowerCase(string input)
{
	char originalLetter;
	unsigned int i;
	for(i = 0; i < input.size(); i++)
    {
      originalLetter = input[i];
      input[i] = tolower(originalLetter);
    }
    
    return input;    
}

/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Looks for words ending/beginning with an apostrophe, removes apostrophe 
 * once found
 *
 * @param[in] input - Line of words from original text file
 *
 * @return input with single quotes removed where necessary
 ****************************************************************************/
string formatWords(string input)
{
  int i;
  int size = input.size();
	
  //removes quotes from the beginning of the line
  while (input[0] == '\'')
  	input.erase(0,1);

  //removes the single quote from the end of a word
  for(i = 0; i < size; i++)
    {
    	
    	if (input[i] == '\'' && (!isalpha(input[i+1]) || ( i-1 >=0 && !isalpha(input[i-1]))))
			{
				input.erase(i,1);
	 			i--;
	 		}
	}
	
	return input;	
}





