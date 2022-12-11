#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class DisplayResults {
public:
	DisplayResults();
	void SelectionResults(int selection, vector<string> unfilteredItems, vector<string> filteredItems, vector<int> quantities);
	void DisplayItems(vector<string> unfilteredItems);
	void DisplayBoth(vector<string> filteredItems, vector<int> quantities);
	void DisplaySingle(vector<string> filteredItems, vector<int> quantities);
	void DisplayHistogram(vector<string> filteredItems, vector<int> quantities);
	void FileOutput(vector<string> filteredItems, vector<int> quantities, string fileName);
	string FillColumns(char c, size_t n);
	string StrToLower(string str);
};

