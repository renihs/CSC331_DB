/* Author: Stephen Austin Shiner
 * Account #28
 * Author: Sarah Nolasco
 * Account #23
 * Created: 10/31/2014
 * Completed: TODO
 * Purpose: CSC 331 File System Term Project
 * Holds preprocessor directives such as include directives and define directives
 * Also contains class and function prototypes
 */

// Preprocessor directives
#include <iostream> // Basic (console) I/O functionality
#include <fstream> // For file I/O to read input file
#include <cstdlib> // For use of exit
#include <string> // Needed to use string objects


#ifndef FILESYSTEM_H_ // Check for namespace collisions
#define FILESYSTEM_H_

// Class prototypes

class Record
{
private:
	int key; // Will hold Record key
	std::string name; // Will hold Record name/description
	int code; // To hold Record secondary key
	double cost; // Holds value/cost as a decimal number

public:
	Record(); // Default Constructor - Creates a dummy (blank/empty) Record
	Record(int keyInit, std::string nameInit, int codeInit, double costInit); // Initialization Constructor
	int getCode() const;
	void setCode(int code);
	double getCost() const;
	void setCost(double cost);
	int getKey() const;
	void setKey(int key);
	const std::string& getName() const;
	void setName(std::string& name);
};

class PrimaryIndex
{
private:
	int key; // Will hold Record key
	int relativeRecordNumber; // Numerical position of the indexed record in the data file

public:
	PrimaryIndex(); // Default Constructor - Creates an empty primary index object
	PrimaryIndex(int keyInit, int relativeRecordNumberInit); // Initialization Constructor sets member variables to constructor arguments
	int getKey() const;
	void setKey(int key);
	int getRelativeRecordNumber() const;
	void setRelativeRecordNumber(int relativeRecordNumber);
};


#endif /* FILESYSTEM_H_ */
