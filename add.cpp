/* Author: Stephen Austin Shiner
 * Account #28
 * Author: Sarah Nolasco
 * Account #23
 * Created: 10/31/2014
 * Completed: TODO
 * Purpose: CSC 331 File System Term Project
 * Utilizes primary and secondary keys along with an index file to create and
 * maintain a database-like information management system
 *
 */

// Preprocessor Directives
#include "FileSystem.h"
using namespace std;
/*
int main(int argc, char * argv[])
{
	fstream outputFile("file.bin", ios::binary | ios::out | ios::app | ios::ate); // Open output binary file in append mode, cursor at the end (ate)
	if (outputFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	Record headerRecord; // Create empty, dummy header Record, may hold actual header Record if file isn't empty

	if (outputFile.tellg() < 7) // Check if data file is empty, ie it has no header Record
	{
		headerRecord.setKey(headerRecord.getKey() + 1); // Increment header Record count by one
		outputFile.write((char *) &headerRecord, sizeof(Record)); // Write header record to file
	}
	else // File is NOT empty
	{
		outputFile.seekg(ios::beg); // Move extraction file cursor to beginning of the file
		outputFile.read((char *) &headerRecord, sizeof(Record)); // Read in header Record
		headerRecord.setKey(headerRecord.getKey() + 1); // Increment header Record count by one
		outputFile.seekp(ios::beg); // Move file cursor to beginning of the file
		outputFile.write((char *) &headerRecord, sizeof(Record)); // Write header record to file
	}

	// TODO: ADD COMMAND-LINE ERROR CHECKING

	// Create new Record object using the user's command-line input
	Record newRecord(atoi(argv[1]), argv[2], atoi(argv[3]), atof(argv[4]));

	// Call function to write primary index entry out to primary index file
	updatePrimaryIndexFile(newRecord.getKey(), headerRecord.getKey());

	outputFile.seekp(ios::end); // Move insertion pointer to the end of the binary output file

	outputFile.write((char *) &newRecord, sizeof(Record)); // Write serialized Record object out to the data file

	outputFile.close(); // Terminate program connection with output data file

	return 0; // Return successful program run
}
*/

/**
 * Updates the primary index file using the argument Record's RRN and key values
 */
void updatePrimaryIndexFile(const int &key, const int &relativeRecordNumber)
{
	// TODO: Read primary index file contents into memory and insert new PrimaryIndex object into the correct position
	// Open primary index file as binary, opened in ios::app (append) mode with cursor set to the file end
	ofstream primaryIndexFile("primaryindex.idx", ios::binary | ios::out | ios::app | ios::ate);
	if (primaryIndexFile.fail()) // If index output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Index output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	PrimaryIndex index(key, relativeRecordNumber); // Create new primary index object to write to index output file

	primaryIndexFile.write((char *) &index, sizeof(PrimaryIndex)); // Write new primary index object out to the primary index file

	primaryIndexFile.close(); // Terminate program/file connection with index file
}

