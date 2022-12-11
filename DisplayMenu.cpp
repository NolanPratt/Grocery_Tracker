#include "DisplayMenu.h"

// Object Constructor
DisplayMenu::DisplayMenu() {
	selection = -1;
}

// Displays user menu and gathers selection
int DisplayMenu::Menu(vector<string> items) {
	int option = 1;
	// Count through items
	for (string menuItem : items) {
		// Print items in menu format
		cout << option << ": " << menuItem << endl;
		option++;
		// Check for end of list
		if (option == items.size() + 1) {
			cout << option << ": Exit" << endl;
			// Prompt user selection
			cout << "Please enter desired menu option with corresponding number: ";
			selection = TypeCheck();
		}
	}
	return selection;
}

// Checks the input data type
int DisplayMenu::TypeCheck() {
	int val;
	try {
		cin >> val;
		if (cin.fail()) {
			throw (val);
		}
	}
	catch (...) {
		cout << "\n\nInvalid data entry" << endl;
		exit(-99);
	}
	return val;
}
