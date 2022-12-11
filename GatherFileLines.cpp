#include "GatherFileLines.h"

GatherFileLines::GatherFileLines() {
	vector<string> linesVector;
}

vector<string> GatherFileLines::FileLinesAsVector(string filename) {
	// Add grocery items into string vector
	vector<string> linesVector;

	// Declare GroceryItems file name and open for reading
	ifstream file; file.open(filename);

	// Validate file existence for reading
	if (!file.is_open()) {
		cout << "Failed to open file." << endl;
	}
	else {
		//string line;
		while (!file.fail()) {

			// Declare a line instance to fill with each read line
			string line;

			// Read the current line and assign it to the line variable
			getline(file, line);

			// Assign the populated line variable to an element within the line vector
			linesVector.push_back(line);
		}
	}
	// Exit file reading
	file.close();

	// Return file lines vector
	return linesVector;
}