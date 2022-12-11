/*
 * Grocery Tracker
 * 
 * Nolan Pratt
 * 12/11/22
 * CS 210
 * Dr. Oluwayomi Adamo
 * Southern New Hampshire University
 * ---------------------------------------
 * This program is divided into three distinct blocks within the main() function,
 * Breakdown:
 * 
 * 1) The first block utilizes C++ and Python integration to achieve a user interface 
 * that takes in an integer input and outputs file data in the desired format.
 * 
 * 2) The second block achieves the same functionality with a few 
 * extra user options, fully processed within the C++ language
 * 
 * 3) The third block achieves the same functionality with a few extra 
 * user options, fully processed within the Python language
 * 
 * In order to access these distinct code blocks for running, insert a single line comment 
 * tag, "//", in front of the lone multi-line comment tag that heads each block. Delete the 
 * single line comment tag to comment out the code block when attempting to run another, so 
 * the processes are not conflicting.
 * 
 * Ex:	/*  -->  ///*  -->  /*
 * 
 */

#include "DisplayMenu.h"
#include "GatherFileLines.h"
#include "DisplayResults.h"
#include <sstream>

// Calls Python function without parameters
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	#pragma warning(suppress : 4996)
		strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// Calls int Python function and returns integer value
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	#pragma warning(suppress : 4996)
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// Calls str Python function and returns integer value
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	#pragma warning(suppress : 4996)
		std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	#pragma warning(suppress : 4996)
		std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

// Returns the vector parameter as a set
set<string> convertToSet(vector<string> v)
{
	// Declaring the set
	set<string> s;

	// Traverse the vector
	for (string x : v) {

		// Insert each element
		// into the set
		s.insert(x);
	}

	// Return the resultant set
	return s;
}

// Returns the set parameter as a vector
vector<string> convertToVector(set<string> s) 
{
	// Declaring the vector
	vector<string> v;

	// Traverse the set
	for (string x : s) {
		// Insert each element into the set
		v.push_back(x);
	}

	// Return resultant vector
	return v;
}

// Gather only strings within a string into a string vector
vector<string> extractNames(string str)
{
	/* Storing the whole string into string stream */
	stringstream ss;
	ss << str;
	string temp;
	string nameFound;
	vector<string> names;

	/* Running loop till the end of the stream */
	while (!ss.eof()) {
		/* Extracting word by word from stream */
		ss >> temp;

		/* Checking if the given word is integer or not */
		if (stringstream(temp) >> nameFound) {
			names.push_back(nameFound);
		}
	}
	// Return only the names
	return names;
}

// Gather integers within a string into an int vector
vector<int> extractNums(string str)
{
	/* Storing the whole string into string stream */
	stringstream ss;
	ss << str;
	string temp;
	int numFound;
	vector<int> nums;

	/* Running loop till the end of the stream */
	while (!ss.eof()) {
		/* Extracting word by word from stream */
		ss >> temp;

		/* Checking if the given word is integer or not */
		if (stringstream(temp) >> numFound) {
			nums.push_back(numFound);
		}
	}
	// Return only the numbers
	return nums;
}

// Enter main driver
int main() {

/*-------------------------------------------------------------*/
/*															   *
*					Integration Section:					   *
* This block can be uncommented to perform the program		   *
* functions using C++ and Python integration				   *
*/
/*-------------------------------------------------------------*/
/* Insert "//" in front of comment below to access integration */

	///*

	// Create menu options to display
	vector<string> menuOptions =
	{ "Return filtered list of items with corresponding quantities",
		"Return frequency of one specified item within the data set",
		"Return a text-based histogram of each item within the data set" };

	// Create DisplayMenu Object for prompting user input
	DisplayMenu GroceryMenu;
	// Create DisplayResults Object for interpreting user input
	DisplayResults userResults;

	int userSelection = 0;
	while (userSelection != 4)
	{
		// Call menu display and prompt user to desired process
		userSelection = GroceryMenu.Menu(menuOptions);
		// Pass selection to Python interface
		userSelection = callIntFunc("CppInterface", userSelection);

		string userName;
		int itemNum;
		// Conditional to check user selection from Python return value
		switch (userSelection)
		{
			// Prompt for single item and display frequency
		case (2):
			// Prompt user to enter desired item
			cout << "Enter an item name to view its purchase history: " << endl;
			cin >> userName;
			// Pass user entry to Python function
			itemNum = callIntFunc("CppDisplaySingle", userName);
			cout << "The total number of " << userName << " sold today is " << itemNum << "." << endl;

			// Interpret Fequency.dat file created from Python function
		case (3):
			// Read in Frequency.dat lines
			GatherFileLines freqFile;
			// Store lines into string vector
			vector<string> freqFileVector = freqFile.FileLinesAsVector("Frequency.dat");

			// Declare character string and append Frequency.dat lines
			string combinedLines = "";
			for (string line : freqFileVector) {
				for (char character : line) {
					if (!isdigit(character) && character != '.') {
						combinedLines += character;
					}
				}
			}

			// Call function to extract only names from combined string
			vector<string> itemNames = extractNames(combinedLines);

			// Declare number string and append item quantities
			string combinedNums = "";
			for (string line : freqFileVector) {
				for (char character : line) {
					if (isdigit(character) || character == '.') {
						combinedNums += character;
					}
				}
				combinedNums += " ";
			}

			// Call function to extract only integers from combined string
			vector<int> itemNums = extractNums(combinedNums);

			// Combine both name and num vectors within loop to print
			// item names and quantities represented by asterisks
			for (size_t p = 0; p < itemNames.size() - 1; p++) {
				cout << itemNames.at(p) << userResults.FillColumns(' ', 14 - itemNames.at(p).size()) << userResults.FillColumns('*', itemNums.at(p)) << endl;
			}
		}
	}
	//*/

/*-------------------------------------------------------------*/
/*															   *
*						C++ section:						   *
* This block can be uncommented to perform the functions	   *
* ran entirely in the C++ language with no Python usage.	   *
*/
/*-------------------------------------------------------------*/
/* Insert "//" in front of comment below to access C++ code	   */ 
	
	/*
	
	// Object Declarations
	// Declare file object to read lines in file
	GatherFileLines fileReader;
	// Declare DisplayResults object to output user selection results
	DisplayResults userResults;
	// Create DisplayMenu Object for prompting user input
	DisplayMenu GroceryMenu;

	// Create menu options to display
	vector<string> menuOptions =
	{ "Return unfiltered list of purchased items",
		"Return filtered list of purchased items",
		"Return filtered list of purchased items with corresponding quantities",
		"Return total quantity of only a specific item",
		"Return histogram of purchased items to quantity purchased" };

	// Store file lines in item vector
	vector<string> unfilteredItemVector = fileReader.FileLinesAsVector("InputFile.txt");
	
	// Convert item vector to set for automatic ordering 
	set<string> itemSet = convertToSet(unfilteredItemVector);
	
	// Setting count vector to the number of discrete items in set
	vector<int> numItems(itemSet.size());

	// Iterating through the set and counting each occurrence
	int itemTracker = 0;
	for (string setItem : itemSet) {
		for (string vectorItem : unfilteredItemVector) {
			if (setItem == vectorItem) {
				numItems[itemTracker] += 1;
			}
		}
		itemTracker++;
	}
	
	// Convert items set back to vector for easier iteration
	vector<string> filteredItemVector = convertToVector(itemSet);

	// Enter user interface loop
	int userSelection = -1;
	while (userSelection != 6) {
		// Call DisplayMenu object to create user interface
		userSelection = GroceryMenu.Menu(menuOptions);

		// Displaying results based on selection
		userResults.SelectionResults(userSelection, unfilteredItemVector, filteredItemVector, numItems);
	}

	//*/

/*-------------------------------------------------------------*/
/*															   *
*						Python section:						   *
* This block can be uncommented to perform the same functions  *
* ran only within the external Python environment			   *
*/
/*-------------------------------------------------------------*/
/* Insert "//" in front of comment below to access Python code */

	/*

	DisplayMenu GroceryMenu;
	int userSelection = -1;
	while (userSelection != 6) {
		// Call Python function to begin user interface
		callIntFunc("Interface", userSelection);
	}
	//*/

	return 0;
}