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
 * Driver program for the delete "del" functionality of our information management system.
 * Accepts a target key value, searches for the associated record using the primary index file, and
 * deletes it by setting its key value to -1 in both the primary index file and in the data file.
 * Its code (secondary key) is also set to -1 in the data file.
 * To accomplish this, both the proper primary index record and the data record must be read
 * into the file as objects, modified, and written back out to the primary index file and the
 * data file, respectively.
 */

#include "FileSystem.h"
using namespace std;


int main(int argc, char * argv[])
{
	fstream ioFile("file.bin", ios::binary | ios::in | ios::out); // Open data binary file
	if (ioFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Data file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	int tempRRN = search(atoi(argv[1]));

	if(tempRRN != -1) // Delete record from index file
	{
		Record delRecord; // Record to be "deleted" by setting its keys to -1

		ioFile.seekp(sizeof(Record) * tempRRN); // Move file cursor to beginning of deleted record
		ioFile.read((char *) &delRecord, sizeof(Record)); // Read in record to be deleted
		ioFile.seekp(sizeof(Record) * tempRRN); // Reset pointer to start of record

		deleteFromPrimaryIndexFile(delRecord.getKey());

		delRecord.setKey(-1);
		delRecord.setCode(-1);
		ioFile.write((char *) &delRecord, sizeof(Record)); // Write record back to file

		cout << "Record with key " << argv[1] << " was successfully deleted." << endl; // Output success message
	}
	else // record not found, output failure message to user
		cout << "Sorry, a record with key " << argv[1] << " was not found, and could not be deleted." << endl;

	ioFile.close(); // Terminate program/file connection with data file

	return 0; // Return successful program run
}
