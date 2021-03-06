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
 * This file contains the "bag of functions" utilized by the 4 driver programs
 * This allows function reuse between the various driver programs, and makes them
 * cleaner in terms of readability.
 *
 */

// Preprocessor directives
#include "FileSystem.h"
using namespace std;

/**
 * Updates the primary index file using the argument Record's RRN and key values
 */
void updatePrimaryIndexFile(const int &key, const int &relativeRecordNumber)
{
	// Open primary index file as binary, opened in ios::app (append) mode with cursor set to the file end
	ofstream primaryIndexFile("primaryindex.idx", ios::binary | ios::out | ios::ate);
	if (primaryIndexFile.fail()) // If index output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Index output file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	PrimaryIndex index(key, relativeRecordNumber); // Create new primary index object to write to index output file

	primaryIndexFile.write((char *) &index, sizeof(PrimaryIndex)); // Write new primary index object out to the primary index file

	primaryIndexFile.close(); // Terminate program/file connection with index file
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

	indexFile.close(); // Terminate program/file connection with primary index file

	insertionSort(indexes); // Call insertion sort function to sort the primary indexes

	// Call binary search function to search the sorted vector of primary indexes, and return the location
	location = binarySearch(indexes, key);

	if (location != -1) // Target was found in the index file
		return indexes[location].getRelativeRecordNumber(); // Return target's relative record number
	else // Target record was not found
		return location; // Return -1
}

/**
 * Accepts a reference to a vector of PrimaryIndex objects
 * Vector is sorted according to the key value, in ascending order using a basic insertion sort algorithm
 */
void insertionSort(vector<PrimaryIndex>& indexes)
{
	PrimaryIndex tempIndex; // Will temporarily hold IndexRecord object to be swapped
	unsigned int i, j, len = indexes.size();

	// Loop iterates over each element and sorts it using a naive insertion algorithm,
	// beginning at array index 1
	for (i = 1; i < len; i++)
	{
		j = i; // Pivot element number is the next unsorted index

		// Inner loop checks adjacent elements and performs swaps until none remain
		while (j > 0 && indexes[j - 1].getKey() > indexes[j].getKey())
		{
			tempIndex = indexes[j]; // Temporarily store element to be swapped
			indexes[j] = indexes[j - 1]; // Swap lesser element to proper position
			indexes[j - 1] = tempIndex; // Swap old element to new position
			j -= 1; // Decrement j by one
		}
	}
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

/**
 * Deletes record from the primary index file using the argument's key value
 */
void deleteFromPrimaryIndexFile(const int &key)
{
	// Open primary index file as binary, opened in ios::app (append) mode with cursor set to the file end
	fstream indexFile("primaryindex.idx", ios::binary | ios::in | ios::out | ios::app);
	if (indexFile.fail()) // If index output file was not successfully opened
	{	// Inform user of file opening failure and exit program run
		cout << "Primary Index file failed to open. Program is ending. Goodbye." << endl;
		exit(1); // End program run with error value
	}

	bool found = false; // Flag for finding the target record
	PrimaryIndex tempIndex; // Temporarily holds each PrimaryIndex object

	// Loop reads each Index object into memory until end of file
	while (!indexFile.eof() && !found)
	{
		indexFile.read((char *) &tempIndex, sizeof(PrimaryIndex)); // Read primary index into temp object

		if (tempIndex.getKey() == key) // We've got a hit
		{
			tempIndex.setKey(-1); // "Delete" primary index by setting its key value to -1
			found = true; // Flip flag
		}
		else // Not a hit yet
			indexFile.seekg(sizeof(PrimaryIndex), ios::cur); // Move file cursor forward to next entry
	}

	if (found) // If target primary index was found, move cursor back to start of index record and write deleted version
	{
		indexFile.seekp(sizeof(PrimaryIndex) * -1, ios::cur); // Reset pointer to start of record
		indexFile.write((char *) &tempIndex, sizeof(PrimaryIndex)); // Write deleted primary index object out to primary index file
	}

	indexFile.close(); // Terminate program/file connection with primary index file
}
