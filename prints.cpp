/*************************************************************************//**
 * @file prints.cpp
 * @brief Functions for displaying word statistics
 *****************************************************************************/

#include "prints.h"

/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Displays the info gathered from the input file to a .csv (comma seperated
 * value) file and a .wrd file
 *
 * @param[in] argv - command line arguments
 * @param[in] hash - hash table
 * @param[in] elapsedTime - time passed since program started running
 *
 ****************************************************************************/
void displayInfo(char** argv, HashTable &hash, double elapsedTime)
{
	int total = hash.getTotal();
	int unique = hash.getUnique();
	Hash* hashes = hash.getHash();
	//gets filename without any extensions
	string fileName = getFilenames(argv[1]);
	//creates name for .wrd output file
	string outputFilewrd = fileName + ".wrd";
	//creates name for .csv output file
	string outputFilecsv = fileName + ".csv";

	cout << "Read " << total << " words from the file " << fileName << "." << endl;
	cout << "Inserted " << unique << " distinct words into the hash table." << endl;
	cout << "Elapsed time: " << elapsedTime * 1000 << " msec " << endl << endl << endl;


	displayOutputwrd(outputFilewrd, total, unique, hashes);

	displayOutputcsv(outputFilecsv, total, unique, hashes);

}


/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Removes extension from filename (if applicable) 
 *
 * @param[in] originalName - input filename from command line
 *
 * @returns string without extensions
 ****************************************************************************/
string getFilenames(string originalName)
{
	unsigned int found = originalName.find_last_of(".");
	if(found == string::npos)
		return originalName;
	return originalName.substr(0, found);
}



/*************************************************************************//**
 * @author Adrian Azan
 *
 * @par Description
 * Finds and displays the rank and average rank of each of the words
 * based on frequency
 *
 * @param[in, out] fout - output file stream
 * @param[in] hash - hash table
 * @param[in] start - index to begin at
 * @param[in] end - index to end at
 * @param[in] unique - number of unique words in file
 *
 ****************************************************************************/
void displayRanks(ofstream &fout, Hash* hash, int start, int end, int unique)
{
	double avgRank;
	avgRank = getAvgRank (hash, start, end, unique);
		
	fout << setw(31) << start + 1;
	
	//Finds end of rank for list of words
	while (end < unique - 1 && hash[end].freq == hash[end+1].freq)
		end++;
		
	//If there was more than one word
	if (start != end)
			fout << "-" << end+1;
	
			
	fout << setw(20) << setprecision(1) << fixed << avgRank << endl;
	
}



/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Returns the average rank of words of the same frequency
 *
 * @param[in] hash - hash table
 * @param[in] start - index to begin at
 * @param[in] end - index to end at
 * @param[in] unique - number of unique words in file
 *
 * @return average rank of frequency group
 ****************************************************************************/
double getAvgRank(Hash* hash, int start, int end, int unique)
{
	double avgRank;
	avgRank = 0;
	
	//while its withing the table and same frequency group	
	while (end < unique - 1 && hash[end].freq == hash[end+1].freq)
	{
		end++;
	}

	//calculate average rank
	for (int k = start+1; k <= end+1; k++)
	{
		avgRank += k;
	}		
	
	avgRank = avgRank/(end-start+1);
	return avgRank;
}


/*************************************************************************//**
 * @author Adrian Azan & Emily Parks
 *
 * @par Description
 * Displays the word concordance of the input file to the .wrd output file
 *
 * @param[in] outputFile - name of output file
 * @param[in] total - total number of words in the file
 * @param[in] unique - number of unique words in file
 * @param[in] hash - hash table
 *
 ****************************************************************************/
void displayOutputwrd(string outputFile, int total, int unique, Hash* hash)
{
	ofstream fout;
	int i, j, count;
	
	OpenAndCheckFile(outputFile, fout);

	fout << "Contents of output file " << outputFile << endl;
	fout << "-------------------------------------------------" << endl << endl;
	fout << "Zipf's Law: Word Concordance" << endl;
	fout << "-----------------------------" << endl;

	fout << "File:" << setw(20) << outputFile << endl;
	fout << "Total words:" << setw(20) << total << endl;
	fout << "Distinct words:" << setw(17) << unique << endl;

	fout << "Word Frequencies " << setw(40) << "Ranks " << setw(20) << "Avg Rank " << endl;
	fout << "-----------------" << setw(40) << "-------" << setw(20) << "----------" << endl;

	i = 0;
	j = 0;
	count = 1;

	while(i < unique)
	{
		if(hash[i].freq != 0)
		{
			if(hash[i].freq == 1)
				fout << "Words occurring once: " << setw(31) << right;
			else
				fout << "Words occurring " << hash[i].freq << " times: " << setw(31) << right;
				
			displayRanks(fout, hash, j, i, unique);
			
			while(hash[j].freq == hash[i].freq && j < unique)
			{
				//Only prints 5 words per line
				if (count >= 6)
				{
					fout << endl;
					count = 1;
				}
				fout << left << setw(15) << hash[j].word;
				j++;
				count++;
			}
			fout << endl << endl;
			i = j;
			count = 1;
		}
		else
			i++;
	}

	fout.close();
}


/*************************************************************************//**
 * @author Emily Parks
 *
 * @par Description
 * Displays the word concordance of the input file to the .csv output file
 *
 * @param[in] outputFile - name of output file
 * @param[in] total - total number of words in the file
 * @param[in] unique - number of unique words in file
 * @param[in] hash - hash table
 *
 ****************************************************************************/
void displayOutputcsv(string outputFile, int total, int unique, Hash* hash)
{
	ofstream fout;
	int i = 0, j = 0;
	double avgRank;
    OpenAndCheckFile(outputFile, fout);

	fout << "Contents of output file " << outputFile << endl;
	fout << "-------------------------------------------------" << endl << endl;

	fout << "Zipf's Law: rank * frequency = constant " << endl;
	fout << "-----------------------------------------" << endl;

	fout << "File:" << setw(20) << outputFile << endl;
	fout << "Total words:" << setw(20) << total << endl;
	fout << "Distinct words:" << setw(17) << unique << endl;

	fout << " rank," << setw(22) << "freq," << setw(19) << "r * f" << endl;
	
	while(i < unique)
	{
		if(hash[i].freq != 0)
		{
			avgRank = getAvgRank(hash, j, i, unique);
			while(hash[j].freq == hash[i].freq && j < unique)
				j++;
			fout << setw(6) << setprecision(1) << fixed << avgRank << "," 
			<< setw(20) << hash[i].freq << "," << setw(20) << setprecision(1)
			<< fixed << avgRank * double(hash[i].freq) << endl;
			i = j;
		}	
		else
			i++;	
	}	



	fout.close();
}
