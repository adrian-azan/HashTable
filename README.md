# HashTable

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
