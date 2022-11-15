#include <iostream>
#include <chrono>

#include "BinaryFile.h"
#include "BSTree.h"
#include "RBTree.h"

void printMenu();
void printBSTreeMenu();
void printRBTreeMenu();
void initFile(const string&, size_t, size_t);
static TestData generateRandomTestData(size_t);
static bool isUniqueKey(const std::string&, const std::string&);
static void writeDataToFile(const string&, const TestData&);

int main()
{
	printMenu();

	std::cout << "\nYour choise is:\n";

	size_t path = 0; // Menu navigation variable
	std::cin >> path;

	// cin.clear and cin.ignore are used to prevent fake input:
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	
	while (path)
	{
		switch (path)
		{
		case 1: 
		{
			BinaryFile file("test.dat", "source.txt");
			BSTree tree(file);

			printBSTreeMenu();
			
			std::cout << "\nYour choise is:\n";
			size_t path = 0; // Menu navigation variable
			std::cin >> path;

			// cin.clear and cin.ignore are used to prevent fake input:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			
			while (path)
			{
				switch (path)
				{
				case 1: {
					tree.print();
					break;
				}
				case 2: { // Insertion
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;

					std::cout << "Enter the value:\n";
					TestData value(key);
					std::cin >> value.title;

					for (size_t i = 0; i < 5; i++)
					{
						value.questions.resize(value.questions.size() + 1);
						std::cin >> value.questions.back();
					}

					// Measure insertion time with chrono:
					auto start = std::chrono::high_resolution_clock::now();	
					tree.insert(key, value);
					auto end = std::chrono::high_resolution_clock::now();
					std::cout << "Insertion time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n";
					break;
				}
				case 3: { // Removing
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;
					tree.remove(key);
					break;
				}
				case 4: { // Searching
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;

					Node* node = tree.search(key);

					if (node)
					{
						std::cout << "Key: " << node->key << "\nValue: "
							<< node->value.title << "\n";
					}
					else
					{
						std::cerr << "There is no such key in the tree.\n";
					}
					break;
				}
				default:
					std::cerr << "\nError: Wrong path entered.\n"; // Error message
					break;
				}

				printBSTreeMenu();

				std::cout << "\nYour choise is:\n";
				std::cin >> path;

				// cin.clear and cin.ignore are used to prevent fake input:
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
			break;
		}
		case 2: 
		{
			BinaryFile file("test.dat", "source.txt");
			RBTree tree(file);

			printRBTreeMenu();

			std::cout << "\nYour choise is:\n";
			size_t path = 0; // Menu navigation variable
			std::cin >> path;

			// cin.clear and cin.ignore are used to prevent fake input:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');

			while (path)
			{
				switch (path)
				{
				case 1: {
					tree.print();
					
					// Output tree rotations_count
					std::cout << "\nRotations count: " << tree.get_rotations_count() << "\n";
					break;
				}
				case 2: { // Insertion
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;

					std::cout << "Enter the value:\n";
					TestData value(key);
					std::cin >> value.title;

					for (size_t i = 0; i < 5; i++)
					{
						value.questions.resize(value.questions.size() + 1);
						std::cin >> value.questions.back();
					}

					// Measure insertion time with chrono:
					auto start = std::chrono::high_resolution_clock::now();
					tree.insert(key, value);
					auto end = std::chrono::high_resolution_clock::now();
					std::cout << "Insertion time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns\n";
					break;
				}
				case 3: { // Removing
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;
					tree.remove(key);
					break;
				}
				case 4: { // Searching
					std::cout << "Enter the key:\n";
					std::string key;
					std::cin >> key;

					RBNode* node = tree.search(key);

					if (node)
					{
						std::cout << "Key: " << node->key << "\nValue: "
							<< node->value.title << "\n";
					}
					else
					{
						std::cerr << "There is no such key in the tree.\n";
					}
					break;
				}
				default:
					std::cerr << "\nError: Wrong path entered.\n"; // Error message
					break;
				}

				printRBTreeMenu();

				std::cout << "\nYour choise is:\n";
				std::cin >> path;

				// cin.clear and cin.ignore are used to prevent fake input:
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
			break;
		}
		case 3: 
		{
			// Enter the file size and init file
			std::cout << "Enter the file size:\n";
			size_t size = 0;
			std::cin >> size;

			// Enter the random range
			std::cout << "Enter the random range:\n";
			size_t range = 0;
			std::cin >> range;

			// cin.clear and cin.ignore are used to prevent fake input:
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			
			initFile("source.txt", size, range);
			break;
		}
		default:
			std::cerr << "\nError: Wrong path entered.\n"; // Error message
			break;
		}

		system("pause");
		system("cls"); // Clear screen

		printMenu();

		// Next menu navigation step:
		std::cout << "\nYour choise is:\n";
		std::cin >> path;

		// cin.clear and cin.ignore are used to prevent fake input
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');
	}
	
	return 0;
}

void printMenu()
{
	std::cout << "Practical task num.4\nIKBO-24-21 Nasevich V.V.\n"
		"Variant num. 16.\n\nMenu:\n"
		"1)Enter <1> to initialize binary search tree.\n"
		"2)Enter <2> to initialize red-black tree.\n"
		"3)Enter <3> to rewrite a txt file.\n"
		"4)Enter <0> to exit.\n";
}

void printBSTreeMenu()
{
	std::cout << "Binary search tree menu:\n"
		"1)Enter <1> to print a binary search tree.\n"
		"2)Enter <2> to insert an element to a binary search tree.\n"
		"3)Enter <3> to delete an element from binary search tree.\n"
		"4)Enter <4> to search an element in binary search tree.\n"
		"5)Enter <0> to exit.\n";
}

void printRBTreeMenu() 
{
	std::cout << "Red-black tree menu:\n"
		"1)Enter <1> to print a red-black tree.\n"
		"2)Enter <2> to insert an element to a red-black tree.\n"
		"3)Enter <3> to delete an element from a red-black tree.\n"
		"4)Enter <4> to search an element in a red-black tree.\n"
		"5)Enter <0> to exit.\n";
}

// Function to initialize txt file with random DataStruct objects:
void initFile(const std::string& fileName, size_t size, size_t range)
{
	// Clear file before initializing
	std::ofstream file(fileName, std::ios::trunc);
	file.close();
	
	for (size_t i = 0; i < size; i++)
	{
		TestData new_data = generateRandomTestData(range);
		writeDataToFile(fileName, new_data);
	}
}

// Generate random test data
static TestData generateRandomTestData(size_t range)
{
	TestData data;
	string temp_key = std::to_string(rand() % range);
	while (!isUniqueKey(temp_key, "source.txt"))
	{
		temp_key = std::to_string(rand() % range);
	}
	data.key_number = temp_key;
	data.title = "title-" + data.key_number;
	data.questions = { "Qfirst", "Qsec", "Qthird", "Qfourth", "Qfifth" };

	return data;
}

// Check that key_number is unique
static bool isUniqueKey(const std::string& key, const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Error: File is not open.\n";
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.find(key) != std::string::npos)
		{
			return false;
		}
	}
	
	file.close();
	return true;
}

// Write data to file
static void writeDataToFile(const std::string& fileName, const TestData& data)
{
	std::ofstream file(fileName, std::ios_base::app);

	if (file.is_open())
	{
		file << data.key_number << "_" << data.title;
		for (const auto& question : data.questions)
		{
			file << "_" << question;
		}
		file << ";\n";
	}
	
	file.close();
}