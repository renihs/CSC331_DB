/* Author: Stephen Austin Shiner
 * Account #28
 * Author: Sarah Nolasco
 * Account #23
 * Created: 10/31/2014
 * Completed: 11/05/2014 (Alpha)
 * Purpose: CSC 331 File System Term Project
 * Utilizes primary and secondary keys along with an index file to create and
 * maintain a database-like information management system
 *
 * Driver program for the "search" command for our information management system.
 * Accepts a target key value and searches for it using the primary index file. If found,
 * the target record's information is retrieved from the data file and displayed
 * on the screen. If target record is not found, user is informed.
 *
 */

// Preprocessor Directives
#include "FileSystem.h"
using namespace std;

int main(int argc, char * argv[])
{
	// TODO: ADD COMMAND-LINE ERROR CHECKING

	int targetRRN = search(atoi(argv[1])); // Call search function and assign its return value to local variable

	if (targetRRN == -1) // Target not found, inform the user
		cout << "Sorry, record with primary key " << argv[1] << " was not found." << endl;
	else // Target was found in the index file, open the data file and seek to the appropriate position
	{	// Open output binary file in append mode, cursor at the end (ate)
		ifstream dataFile("file.bin", ios::binary | ios::in);
		if (dataFile.fail()) // If output file was not successfully opened
		{	// Inform user of file opening failure and exit program run
			cout << "Output file failed to open. Program is ending. Goodbye." << endl;
			exit(1); // End program run with error value
		}

		dataFile.seekg(sizeof(Record) * targetRRN, ios::beg); // Seek to proper position in file
		Record targetRecord; // Will hold target Record read in from data file

		// Read in target record as a Record object
		dataFile.read((char *) &targetRecord, sizeof(Record));

		dataFile.close(); // Terminate file/program connection with data file

		// Send target Record information to the console output stream
		cout << "Target record successfully located: " << endl
				<< targetRecord.getKey() << " " << targetRecord.getName() << " "
				<< targetRecord.getCode() << " " << targetRecord.getCost() << endl;
	}
}

