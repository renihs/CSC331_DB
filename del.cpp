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

	//int tempRRN = search(atoi(argv[1]));
	int  tempRRN = 5;

	if(tempRRN != -1)
	{
		Record delRecord;

		ioFile.seekp(sizeof(Record)*tempRRN +1); // Move file cursor to beginning of deleted record
		ioFile.read((char *) &delRecord, sizeof(Record)); // Read in record to be deleted
		ioFile.seekp(sizeof(Record)*tempRRN+1);//reset pointer to start of record

		deleteFromPrimaryIndexFile(delRecord.getKey());

		delRecord.setKey(-1);
		delRecord.setCode(-1);
		ioFile.write((char *) &delRecord, sizeof(Record)); // Write record back to file
		ioFile.close();

		//delete record from index file
	}else
	{
		//record not found
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

