#pragma once

#include "DataStruct.h"

#include <vector>
#include <string>
#include <fstream>

// Class for manipulating of the binary file
class BinaryFile
{
public:
	// Constructor
	BinaryFile(string operating, string source);

	// Create a new binary file from another txt file
	void create();

	// Read data from the file
	vector<TestData> read();

	// Read data element from the file
	string readWord(std::ifstream& bin_file);

	char readChar(std::ifstream& bin_file);

	//// Find value by key
	//TestData find(string key, BSTree& tree);

	// Get the name of the file
	string getName() { return bin_file_name; }
	
private:

	// File name
	string bin_file_name;
	string source_file_name;
};