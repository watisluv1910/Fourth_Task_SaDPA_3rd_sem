#include "BinaryFile.h"

#include <iostream>
#include <bitset>
#include <climits>

using std::ios;
using std::string;

BinaryFile::BinaryFile(string operating, string source)
{
	this->bin_file_name = operating;
	this->source_file_name = source;
	
	create();
}

void BinaryFile::create()
{
	std::ifstream source_file(source_file_name, ios::in); // Reading
	std::ofstream bin_file(bin_file_name, ios::out | ios::binary | ios::trunc); // Writing
	
	if (!source_file.is_open() || !bin_file.is_open())
	{
		throw std::exception("Cannot open the file(s).");
		return;
	}

	for (auto it = std::istream_iterator<char>(source_file);
		it != std::istream_iterator<char>();
		it++)
	{
		bin_file << std::bitset<CHAR_BIT>(*it) << std::endl;
	}

	bin_file.close();
	source_file.close();
}

vector<TestData> BinaryFile::read()
{
	std::ifstream bin_file(bin_file_name, std::ios::in | std::ios::binary); // Reading

	if (!bin_file.is_open())
	{
		throw std::exception("Cannot open the file(s).");
	}

	bin_file.seekg(0, std::ios_base::end); // go to end of the file
	auto bin_file_size = bin_file.tellg(); // current position is the size of the file
	bin_file.seekg(0, std::ios_base::beg); // go back to the beginning of the file

	vector<TestData> data;
	
	while (bin_file.tellg() != bin_file_size)
	{
		TestData data_cell;
		data_cell.key_number = readWord(bin_file);
		data_cell.title = readWord(bin_file);

		for (size_t i = 0; i < 5; i++)
		{
			data_cell.questions.push_back(readWord(bin_file));
		}

		data.push_back(data_cell);
	}
	
	bin_file.close();
	
	return data;
}

string BinaryFile::readWord(std::ifstream& bin_file)
{
	string str = "";
	char ch = readChar(bin_file);

	while (ch != '_' && ch != ';')
	{
		str.push_back(ch);
		ch = readChar(bin_file);
	}

	return str;
}

char BinaryFile::readChar(std::ifstream& bin_file)
{
	char c_str[CHAR_BIT + 1];
	int value;

	if (bin_file.read(reinterpret_cast<char*>(&c_str), sizeof(c_str)))
	{
		c_str[CHAR_BIT] = '\0';
		value = std::stoi(string(c_str), 0, 2);
	}
	else
	{
		return ';';
	}

	return (char)value;
}

//TestData BinaryFile::find(string key, BSTree& tree)
//{
//	return tree.search(key)->value;
//}