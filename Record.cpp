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
 * Sets key, name, code, and cost to 0, " blank ", 0, and 0.0, respectively
 */
Record::Record()
{
	string str = " blank ";
	setKey(0);
	setName(str);
	setCode(0);
	setCost(0.0);
}

/**
 * Initialization Constructor
 * Uses constructor arguments to set the key, name, code, and cost
 */
Record::Record(int keyInit, string nameInit, int codeInit, double costInit)
{
	setKey(keyInit);
	setName(nameInit);
	setCode(codeInit);
	setCost(costInit);
}

int Record::getCode() const
{
	return code;
}

void Record::setCode(int code)
{
	this->code = code;
}

double Record::getCost() const
{
	return cost;
}

void Record::setCost(double cost)
{
	this->cost = cost;
}

int Record::getKey() const
{
	return key;
}

void Record::setKey(int key)
{
	this->key = key;
}

const string& Record::getName() const
{
	return name;
}

void Record::setName(string& name)
{
	if (name.size() < 7) // Check if string needs to be padded with spaces
	{
		int numSpaces = 7 - name.size(); // Determine number of spaces to add
		for (int i = 0; i < numSpaces; i++) // Loop pads with appropriate number of spaces
			name += " ";
		this->name = name; // Assign padded name to the name member variable
	}
	else if (name.size() > 7) // If string is too large
	{
		this->name = name.substr(0, 7); // Truncate and assign argument string
	}
	else
		this->name = name;
}

