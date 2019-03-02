/***************************************************************************//**
 * @file main.cpp
 * @mainpage CSC 315 - Fall 2017
 *
 * @brief Main function for project 3- Zipf's Law
 *
 * @section course_section Course Information
 *
 * @authors Adrian Azan, Emily Parks
 *
 * @date Nov. 6 , 2017
 *
 * @par Professor: Dr. Hinker
 *
 * @par Course:  CSC 315 - Section 1 - Fall 2017
 * @section program_section Program Description
 *
 * @par Description
 *   This program investigates the validity of Zipf's Law, which claims that
 * the frequency of a word is inversely proportional to its rank in the
 * frequency table. It reads in lines from a text file and determines the 
 * validity of each word, removing unneccesary chracters if needed. It then 
 * inserts the words into a hash table to store the data. Once all the words have
 * been read in from the file, the hash table is sorted, first by frequency and 
 * then alphabetically within each frequency group. The words are written to a 
 * word file which displays each word within a frequency group, the rank, and 
 * average rank of the word(s). It also outputs the data to a comma seperated 
 * file which displays the rank, frequency, and the result of rank * frequency.  
 *
 * @section compile_section Compile Section
 *
 * @par Build
   @verbatim
% make
   @endverbatim
 * @par Run
 * @verbatim
% ./zipf original.txt
   @endverbatim
 * @par Usage
 *  NA

 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 *
 * @par Revision History
 * https://gitlab.mcs.sdsmt.edu/7317924/csc315_fall2017_project3.git
 *
 *****************************************************************************/
#include "HashTable.h"
#include "functions.h"
#include "prints.h"



/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Main function to handle run of the program
 *
 * @param[in] argc - number of command line arguments
 * @param[in] argv - command line arguments
 *
 ****************************************************************************/
int main(int argc, char* argv[])
{
    ifstream fin;
    string inputLine;
    HashTable temp;

	//track elapsed time
    std::chrono::duration<double> elapsedTime;
    auto startTime = chrono::system_clock::now();

    ArguementCheck(argc);
    OpenAndCheckFile(argv[1], fin);

    cout << endl << endl << endl;

	//read in every line from file
    while( !fin.eof())
	{
		getline(fin, inputLine);
		inputLine = makeLowerCase(inputLine);
		inputLine = formatWords(inputLine);
        getWords(inputLine, temp);
    }
	//sort hashTable
	temp.sort();

	fin.close();

    auto endTime = chrono::system_clock::now();
	elapsedTime = (endTime - startTime);
	cout << "Elapsed Time: " << elapsedTime.count() * 1000 << endl;

	//output results 
	displayInfo(argv, temp, elapsedTime.count());

   return 0;
}
