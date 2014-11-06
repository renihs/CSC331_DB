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
	int targetRRN = search(atoi(argv[1])); // Call search function and assign its return value to local variable

	if (targetRRN == -1)
	{

	}
	else // Target was found in the index file, open the data file and
	{

	}
}

/**
 * Function searches the index file for the target primary key and returns the index record's RRN
 */
int search(int key)
{	// Open output binary file in append mode, cursor at the beginning
	fstream indexFile("primaryindex.idx", ios::binary | ios::out | ios::app);
	if (indexFile.fail()) // If index file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Index file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	bool found = false; // Flag for finding the target record
	int location; // Will hold value of target record's location
	PrimaryIndex tempIndex; // Temporarily holds each PrimaryIndex object
	vector<PrimaryIndex> indexes; // Holds all the PrimaryIndex objects converted from the primary index file

	indexFile.read((char *) &tempIndex, sizeof(PrimaryIndex)); // Priming read of binary primary index file

	// Loop reads each Index object into memory until end of file
	while (!indexFile.eof())
	{
		indexes.push_back(tempIndex); // Add Index object to PrimaryIndex vector
		indexFile.read((char *) &tempIndex, sizeof(PrimaryIndex)); // Read of binary primary index file
	}

	for (unsigned int i = 0; i < indexes.size(); i++)
	{
		if (indexes[i].getKey() == key) // Check if we've got a match
		{	// Flip the found flag to true and break

		}
	}

	indexFile.close(); // Terminate program/file connection with primary index file

	if (found) // Target record was found
		return location; // Return its relative record number
	else // Record was NOT found
		return -1; // Return -1 to indicate Record with target key wasn't found
}

/**
 * Accepts a pointer to a vector of PrimaryIndex objects and the target key value
 * Sorted array is searched using a binary algorithm, returning the position of the IndexRecord
 * with the target key value.
 */
int binarySearch(const vector<PrimaryIndex>& indexes, int target)
{
	int min = 0, max = indexes.size(); // Used for search range bounding

	// Loop continues searching while [min, max] is not empty
	while (max >= min)
	{
		int mid = (max + min) / 2; // Calculate middle index

		if (indexes[mid].getKey() == target) // Found target Index Record
			return mid;
		else if (indexes[mid].getKey() < target) // Target is in the upper subarray
			min = mid + 1;
		else // Target is in the lower subarray
			max = mid - 1;
	}
	return -1; // Target key wasn't found, return -1 to signify failure
}
