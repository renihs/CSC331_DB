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
 * Driver program for the modification "mod" function of our information management system.
 * Accepts a key value of the target record to alter, followed by the property name the
 * user wishes to modify, then the new value. If this is anything but the key, the target
 * record is looked up using the primary index file, read into memory, altered, and written back out
 * to the data file. If the property to modify is the key property, the data file is updated
 * the same way, but the index file must also be updated with the new key value for that record.
 */

#include "FileSystem.h"
using namespace std;


int main(int argc, char * argv[])
{

	fstream ioFile("file.bin", ios::binary | ios::in | ios::out | ios::ate); // Open data binary file
	if (ioFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Data file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	Record headerRecord; // Create empty, dummy header Record, may hold actual header Record if file isn't empty

	if (ioFile.tellg() < 7) // Check if data file is empty, ie it has no header Record
	{	// empty file, cannot modify, inform user
		cout << "Sorry, but the data file is empty and therefore cannot be modified." << endl;
	}
	else // File is NOT empty
	{
		int tempRRN = search(atoi(argv[1]));

		Record modRecord; // Will hold record and its modified version

		ioFile.seekp(sizeof(Record) * tempRRN, ios::beg); // Move file cursor to beginning of record
		ioFile.read((char *) &modRecord, sizeof(Record)); // Read in record to be modified
		ioFile.seekp(sizeof(Record) * tempRRN, ios::beg); // Reset cursor to start of record

		if(strcmp(argv[2], "code") == 0)
		{
			// change code in record
			modRecord.setCode(atoi(argv[3]));
			// TODO: add new value in secondary index
		}
		else if(strcmp(argv[2], "key") == 0)
		{
			// Change key for data Record
			modRecord.setKey(atoi(argv[3]));

			// Update primary index file with new key value for the data item
			fstream primaryIndexFile("primaryindex.idx", ios::binary | ios::in | ios::out);
			if (primaryIndexFile.fail()) // If index file was not successfully opened
			{	// Inform user of file opening failure and exit program run
				cout << "Primary Index file failed to open. Program is ending. Goodbye." << endl;
				exit(1); // End program run with error value
			}

			PrimaryIndex modIndex; // To write out to the index file

			// Move cursor to index position to update
			primaryIndexFile.seekp(sizeof(PrimaryIndex) * (tempRRN - 1), ios::beg);

			primaryIndexFile.read((char *) &modIndex, sizeof(PrimaryIndex));

			modIndex.setKey(atoi(argv[3])); // Set new key value

			// Move cursor to index position to update
			primaryIndexFile.seekp(sizeof(PrimaryIndex) * (tempRRN - 1), ios::beg);

			primaryIndexFile.write((char *) &modIndex, sizeof(PrimaryIndex));

			primaryIndexFile.close(); // Terminate program/file connection
		}
		else if (strcmp(argv[2], "cost") == 0) // edit cost in file
			modRecord.setCost(atoi(argv[4]));
		else if (strcmp(argv[2], "name") == 0)
		{
			// edit name in file
			string name = argv[3];
			modRecord.setName(name);
		}
		else // Invalid type, print failure message and exit program run after closing file
		{
			cout << "Sorry, " << argv[2] << " is not a valid command parameter." << endl;
			ioFile.close(); // Terminate program/file connection
			exit(1); // End program run with error value
		}

		ioFile.write((char *) &modRecord, sizeof(Record)); // Write modified record to file
		ioFile.close(); // Terminate program/file connection

		// Output success message to user
		cout << "Record with key " << argv[1] << " was successfully modified by changing its "
				<< argv[2] << " to " << argv[3] << endl;
	}

	return 0; // Return successful program run
}
