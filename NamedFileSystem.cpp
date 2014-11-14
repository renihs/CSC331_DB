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
 *
 */

// Preprocessor Directives
#include "FileSystem.h"
using namespace std;

//name this file system
int main(int argc, char * argv[])
{
	bool cont = true;
	while(cont)
	{
		cout<<"Please enter a command or Q to quit"<<endl;

		string userInput;
		getline(cin, userInput);
		istringstream iss(userInput);
		string command;
		iss>>command;

		//switch statement
		switch( command.at(0) )
		{
			case 'q' :
			{
				cout<<"Closing..."<<endl;
				cont = false;

			}
			break;

			case'm' :
			{
				string modKey;
				iss>>modKey;
				string datalabel;
				iss>>datalabel;
				string newdata;
				iss>>newdata;
			
				mod(atoi(modKey.c_str()), datalabel, newdata);
			}
			break;

			case 'd' :
			{
				string deleteKey;
				iss>>deleteKey;

				deleteItem(atoi(deleteKey.c_str()));
			}
			break;

			case 's' :
			{
				string searchKey;
				iss>>searchKey;

				searchItem(atoi(searchKey.c_str()));
			}
			break;

			case 'a' :
			{
				string addkey;
				iss>>addkey;
				string addname;
				iss>>addname;
				string code;
				iss>>code;
				string cost;
				iss>>cost;
				addItem(atoi(addkey.c_str()), addname, atoi(code.c_str()), atof(cost.c_str()) );
			}
			break;
		}
	}
	return(0);
}

int deleteItem(int key)
{

	fstream ioFile("file.bin", ios::binary | ios::in | ios::out); // Open data binary file
	if (ioFile.fail()) // If output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Data file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	int tempRRN = search(key);

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

		cout << "Record with key " << key << " was successfully deleted." << endl; // Output success message
	}
	else // record not found, output failure message to user
		cout << "Sorry, a record with key " << key << " was not found, and could not be deleted." << endl;

	ioFile.close(); // Terminate program/file connection with data file

	return 0; // Return successful program run


}


int searchItem(int key)
{

	// TODO: ADD COMMAND-LINE ERROR CHECKING

	int targetRRN = search(key); // Call search function and assign its return value to local variable

	if (targetRRN == -1) // Target not found, inform the user
		cout << "Sorry, record with primary key " << key << " was not found." << endl;
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


int mod( int key, string datalabel, string newdata)
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
		int tempRRN = search(key);

		Record modRecord; // Will hold record and its modified version

		ioFile.seekp(sizeof(Record) * tempRRN, ios::beg); // Move file cursor to beginning of record
		ioFile.read((char *) &modRecord, sizeof(Record)); // Read in record to be modified
		ioFile.seekp(sizeof(Record) * tempRRN, ios::beg); // Reset cursor to start of record

		if(strcmp(datalabel, "code") == 0)
		{
			// change code in record
			modRecord.setCode(atoi(newdata.c_str()));
			// TODO: add new value in secondary index
		}
		else if(strcmp(datalabel, "key") == 0)
		{
			// Change key for data Record
			modRecord.setKey(atoi(newdata.c_str()));

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

			modIndex.setKey(atoi(newdata.c_str())); // Set new key value

			// Move cursor to index position to update
			primaryIndexFile.seekp(sizeof(PrimaryIndex) * (tempRRN - 1), ios::beg);

			primaryIndexFile.write((char *) &modIndex, sizeof(PrimaryIndex));

			primaryIndexFile.close(); // Terminate program/file connection
		}
		else if (strcmp(datalabel, "cost") == 0) // edit cost in file
			modRecord.setCost(atof(newdata.c_str()));
		else if (strcmp(datalabel, "name") == 0)
		{
			// edit name in file
			modRecord.setName(newdata);
		}
		else // Invalid type, print failure message and exit program run after closing file
		{
			cout << "Sorry, " << datalabel << " is not a valid command parameter." << endl;
			ioFile.close(); // Terminate program/file connection
			exit(1); // End program run with error value
		}

		ioFile.write((char *) &modRecord, sizeof(Record)); // Write modified record to file
		ioFile.close(); // Terminate program/file connection

		// Output success message to user
		cout << "Record with key " << key << " was successfully modified by changing its "
				<< datalabel << " to " << newdata << endl;
	}

	return 0; // Return successful program run
}


int addItem(int key, string name, int code, float cost)
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
	Record newRecord(key, name, code, cost);

	// Call function to write primary index entry out to primary index file
	updatePrimaryIndexFile(newRecord.getKey(), headerRecord.getKey());

	outputFile.seekp(0, ios::end); // Move insertion pointer to the end of the binary output file

	outputFile.write((char *) &newRecord, sizeof(Record)); // Write serialized Record object out to the data file

	outputFile.close(); // Terminate program connection with output data file

	cout << "Record with key " << key << " has been successfully added." << endl;

	return 0; // Return successful program run
}

