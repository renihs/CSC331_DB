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

int main(int argc, char * argv[])
{

	ofstream outputFile("file.bin", ios::binary | ios::app); // Open output binary file in append mode
	if (outputFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	// TODO: Create header Record and use its key value to hold number of Records, which will allow easy RRNs

	// TODO: ADD COMMAND-LINE ERROR CHECKING

	// Create new Record object using the user's command-line input
	Record newRecord(atoi(argv[1]), argv[2], atoi(argv[3]), atof(argv[4]));

	outputFile.seekp(ios::end); // Move insertion pointer to the end of the binary output file

	outputFile.write((char *) &newRecord, sizeof(Record)); // Write serialized Record object out to the data file

	outputFile.close(); // Terminate program connection with output data file

	return 0;
}

/**
 * Updates the primary index file using the argument Record
 */
void updatePrimaryIndexFile(Record& record)
{
	// TODO: Read primary index file contents into memory and insert new PrimaryIndex object into the correct position
	// TODO: primary index file is binary, opened in ios::app (append) mode
}

