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

#include "FileSystem.h"
using namespace std;

int main(int argc, char * argv[]){

	fstream ioFile("file.bin", ios::binary | ios::out | ios::app | ios::ate ); // Open output binary file
	if (ioFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Input file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	Record headerRecord; // Create empty, dummy header Record, may hold actual header Record if file isn't empty

	if (ioFile.tellg() < 7) // Check if data file is empty, ie it has no header Record
	{
		//empty file cannot modify
	}
	else // File is NOT empty
	{

		//int tempRRN = search(atoi(argv[1]));
		int tempRRN = 5;

		Record modRecord;

		ioFile.seekp(sizeof(Record)*tempRRN +1); // Move file cursor to beginning of deleted record
		ioFile.read((char *) &modRecord, sizeof(Record)); // Read in record to be deleted
		ioFile.seekp(sizeof(Record)*tempRRN+1);//reset pointer to start of record


		if(strcmp(argv[3], "code") == 0)
		{
			//change code in record
			modRecord.setCode(atoi(argv[4]));
			//delete record from secondary index
			//add new value in secondary index
		}else if(strcmp(argv[3] , "key")==0)
		{
			//change key in memory
			modRecord.setKey(atoi(argv[4]));
			//completely delete record from files -------taken from del.cpp
			Record delRecord;
			ioFile.seekp(sizeof(Record)*tempRRN +1); // Move file cursor to beginning of deleted record
			ioFile.read((char *) &delRecord, sizeof(Record)); // Read in record to be deleted
			ioFile.seekp(sizeof(Record)*tempRRN+1);//reset pointer to start of record
			deleteFromPrimaryFile(delRecord.getKey());
			delRecord.setKey(-1);
			delRecord.setCode(-1);
			ioFile.write((char *) &delRecord, sizeof(Record)); // Write record back to file

			//add record -------Same code as from add.cpp---------------
			ioFile.seekg(ios::beg); // Move extraction file cursor to beginning of the file
			ioFile.read((char *) &headerRecord, sizeof(Record)); // Read in header Record
			headerRecord.setKey(headerRecord.getKey() + 1); // Increment header Record count by one
			ioFile.seekp(ios::beg); // Move file cursor to beginning of the file
			ioFile.write((char *) &headerRecord, sizeof(Record)); // Write header record to file

			// Create new Record object using the user's command-line input
			Record newRecord(atoi(argv[1]), argv[2], atoi(argv[3]), atof(argv[4]));

			// Call function to write primary index entry out to primary index file
			updatePrimaryIndexFile(newRecord.getKey(), headerRecord.getKey());

			ioFile.seekp(ios::end); // Move insertion pointer to the end of the binary output file

		}else if (strcmp(argv[3], "cost")==0)
		{
			//edit cost in file
			modRecord.setCost(atoi(argv[4]));
		}else if (strcmp(argv[3], "name")==0)
		{
			//edit name in file
			string name = argv[4];
			modRecord.setName(name);
		}else{
			//invalid type
		}

		ioFile.write((char *) &modRecord, sizeof(Record)); // Write header record to file
		ioFile.close();

	}
}



/**
 * Deletes record from the primary index file using the argument's key value
 */
void deleteFromPrimaryIndexFile(const int &key)
{
	// TODO: Read primary index file contents into memory and insert new PrimaryIndex object into the correct position
	// Open primary index file as binary, opened in ios::app (append) mode with cursor set to the file end
	fstream indexFile("primaryindex.idx", ios::binary | ios::out | ios::app | ios::ate);
	if (indexFile.fail()) // If index output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Index output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	int itemCount = 0;
	bool found = false; // Flag for finding the target record
		PrimaryIndex tempIndex; // Temporarily holds each PrimaryIndex object

		// Loop reads each Index object into memory until end of file
		while (!indexFile.eof() || !found)
		{
			if (tempIndex.getKey() == key)
				{
					tempIndex.setKey(-1);
				}
			indexFile.seekp(sizeof(PrimaryIndex)*itemCount);//reset pointer to start of record
			indexFile.write((char*) & tempIndex, sizeof(PrimaryIndex));
			indexFile.read((char *) &tempIndex, sizeof(PrimaryIndex)); // Priming read of binary primary index file
			itemCount++;
		}

			indexFile.close(); // Terminate program/file connection with primary index file
}




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

	primaryIndexFile.write((char *) &index, sizeof(Record)); // Write new primary index object out to the primary index file

	primaryIndexFile.close(); // Terminate program/file connection with index file
}



