#include "DisplayResults.h"

DisplayResults::DisplayResults() {

}

// Switch check for which process user requests
void DisplayResults::SelectionResults(int selection, vector<string> unfilteredItems, vector<string> filteredItems, vector<int> quantities) {
	FileOutput(filteredItems, quantities, "Frequency.dat");
	switch (selection) {
	case (1):
		DisplayItems(unfilteredItems);
		break;
	case(2):
		DisplayItems(filteredItems);
		break;
	case(3):
		DisplayBoth(filteredItems, quantities);
		break;
	case (4):
		DisplaySingle(filteredItems, quantities);
		break;
	case(5):
		DisplayHistogram(filteredItems, quantities);
		break;
	case(6):
		cout << "Thank you for using this program!" << endl;
		break;
	default:
		cout << "Selection must be within range" << endl;
		break;
	}
}

// Method for displaying list of items
void DisplayResults::DisplayItems(vector<string> items)
{
	// Header
	cout << endl << "Items sold today: " << endl;
	for (size_t item = 1; item < items.size(); item++) {
		cout << items.at(item) << endl;
	}
	cout << endl;
}

// Method for displaying list of items and quantities
void DisplayResults::DisplayBoth(vector<string> filteredItems, vector<int> quantities)
{
	// Header
	cout << endl << "Items and quantities sold today: " << endl;
	// Displaying item name and number of each item
	int num = 1;
	for (size_t item = 1; item < filteredItems.size(); item++) {
		cout << filteredItems.at(item) << ":" << FillColumns(' ', (14 - filteredItems.at(item).length())) << quantities.at(num) << endl;
		num++;
	}
	cout << endl;
}

// Method for displaying quantity of the specified item
void DisplayResults::DisplaySingle(vector<string> filteredItems, vector<int> quantities)
{
	// Prompt user to enter desired item
	cout << "Enter an item name to view its purchase history: " << endl;
	string userName;
	cin >> userName;

	// Iterate through item list to find item name and quantity
	int q = 0;
	int leave = 1;
	for (string item : filteredItems) {
		// Check
		if (StrToLower(item) == StrToLower(userName)) {
			cout << "\nThe total number of " << item << " sold today is " << quantities.at(q) << endl << endl;
			leave = -1;
		}
		q++;
	}
	// Check whether the input is in the list
	if (leave != -1) {
		cout << "This item has not been sold today" << endl << endl;
	}
}

// Method for displaying histogram of gathered data
void DisplayResults::DisplayHistogram(vector<string> filteredItems, vector<int> quantities)
{
	// Header
	cout << endl << "Histogram of data:" << endl;

	// Find the maximum quantity
	int maxQuantity = *max_element(quantities.begin(), quantities.end());

	// For each item and its corresponding quantity
	for (size_t i = 1; i < filteredItems.size(); i++)
	{
		// Print the item name
		cout << filteredItems[i] << ":" << FillColumns(' ', 14 - filteredItems.at(i).size());

		// Calculate the number of character bars to print based on the quantity
		// and the maximum quantity
		int numBars = quantities[i] * 20 / maxQuantity;

		// Print the character bars
		for (int j = 0; j < numBars; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}

// Creates and opens the Frequency file for writing
void DisplayResults::FileOutput(vector<string> filteredItems, vector<int> quantities, string fileName)
{
	// Create and open file for writing
	ofstream file; file.open(fileName);

	// Validate file existence for reading
	if (!file.is_open()) {
		cout << "Failed to open file." << endl;
	}
	else {
		// Iterate through each item
		for (size_t i = 1; i < filteredItems.size(); i++) {
			// Write lines to file
			file << filteredItems[i] << ":" + FillColumns(' ', 14 - filteredItems.at(i).size()) << quantities[i] << endl;
		}
	}
	// Exit file reading
	file.close();
}

// Generates borders with n columns for menu display
string DisplayResults::FillColumns(char c, size_t n)
{
	// Fill return string with the number of desired characters
	string str = "";
	for (size_t i = 0; i < n; i++) {
		str += c;
	}
	return str;
}

// Returns the lowercase of a string
string DisplayResults::StrToLower(string str)
{
	// Converts each letter in string to lowercase
	transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}