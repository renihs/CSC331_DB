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

// Preprocessor directives
#include "FileSystem.h"
using namespace std;


/**
 * Default Constructor
 * Sets key and relativeRecordNumber to zero
 */
PrimaryIndex::PrimaryIndex()
{
	setKey(0);
	setRelativeRecordNumber(0);
}

/**
 * Initialization Constructor
 * Uses constructor arguments to set the key and RRN (relative record number) values
 */
PrimaryIndex::PrimaryIndex(int keyInit, int relativeRecordNumberInit)
{
	setKey(keyInit);
	setRelativeRecordNumber(relativeRecordNumberInit);
}

int PrimaryIndex::getKey() const
{
	return key;
}

void PrimaryIndex::setKey(int key)
{
	this->key = key;
}

int PrimaryIndex::getRelativeRecordNumber() const
{
	return relativeRecordNumber;
}

void PrimaryIndex::setRelativeRecordNumber(int relativeRecordNumber)
{
	this->relativeRecordNumber = relativeRecordNumber;
}
