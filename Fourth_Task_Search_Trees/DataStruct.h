#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct TestData
{
	string key_number, title;
	vector<string> questions;

	TestData() : key_number(""), title(""), questions() {};

	TestData(string key_number) : title(""), questions()
	{
		this->key_number = key_number;
	};

	TestData(string number, string title, vector<string> questions) : 
		key_number(number), 
		title(title), 
		questions(questions) 
	{};

	TestData(const TestData& other) :
		key_number(other.key_number),
		title(other.title),
		questions(other.questions)
	{};

	TestData& operator=(const TestData& other)
	{
		if (this != &other)
		{
			key_number = other.key_number;
			title = other.title;
			questions = other.questions;
		}

		return *this;
	};
};