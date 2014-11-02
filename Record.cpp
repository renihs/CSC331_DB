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

void Record::setName(const string& name)
{
	this->name = name;
}

