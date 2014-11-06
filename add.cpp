/* Author: Stephen Austin Shiner
 * Account #28
 * Author: Sarah Nolasco
 * Account #23
 * Created: 10/31/2014
 * Completed: 11/03/2014 (Alpha)
 * Purpose: CSC 331 File System Term Project
 * Utilizes primary and secondary keys along with an index file to create and
 * maintain a database-like information management system
 *
 * Driver program for adding a new entry to the information management system
 * Opens output data file, updates header record, then adds new record to the end of the
 * data file. Finally, program updates the primary index file, accounting for the new entry.
 */

// Preprocessor Directives
#include "FileSystem.h"
using namespace std;


int main(int argc, char * argv[])
{	
	ifstream fileExists("file.bin", ios::in | ios::binary);
	
	if (fileExists.fail()) // If failed to open, then file doesnt exist yet
	{
		fileExists.close();
		fstream newOutputFile("file.bin", ios::out | ios::binary); // Creates empty binary file
		newOutputFile.close(); // Terminate program/file connection with empty bianry file
	}
	else
		fileExists.close();

	// Open output binary file, with cursor at the end (ate)
	fstream outputFile("file.bin", ios::in | ios::out | ios::binary);

	if (outputFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}
	
	//fstream inputFile("file.bin", ios::in | ios::binary);

	outputFile.seekp(0, ios::end); // Move file cursor to the end

	Record headerRecord; // Create empty, dummy header Record, may hold actual header Record if file isn't empty

	if (outputFile.tellg() < 7) // Check if data file is empty, ie it has no header Record
	{
		headerRecord.setKey(headerRecord.getKey() + 1); // Increment header Record count by one
		outputFile.write((char *) &headerRecord, sizeof(Record)); // Write header record to file
	}
	else // File is NOT empty
	{
		outputFile.seekg(0, ios::beg); // Move extraction file cursor to beginning of the file
		outputFile.read((char *) &headerRecord, sizeof(Record)); // Read in header Record
		headerRecord.setKey(headerRecord.getKey() + 1); // Increment header Record count by one
		outputFile.seekp(0, ios::beg); // Move file cursor to beginning of the file
		outputFile.write((char *) &headerRecord, sizeof(Record)); // Write header record to file
	}

	// TODO: ADD COMMAND-LINE ERROR CHECKING

	// Create new Record object using the user's command-line input
	Record newRecord(atoi(argv[1]), argv[2], atoi(argv[3]), atof(argv[4]));

	// Call function to write primary index entry out to primary index file
	updatePrimaryIndexFile(newRecord.getKey(), headerRecord.getKey());

	outputFile.seekp(0, ios::end); // Move insertion pointer to the end of the binary output file

	outputFile.write((char *) &newRecord, sizeof(Record)); // Write serialized Record object out to the data file

	outputFile.close(); // Terminate program connection with output data file

	cout << "Record with key " << atoi(argv[1]) << " has been successfully added." << endl;

	return 0; // Return successful program run
}
