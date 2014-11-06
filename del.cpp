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

