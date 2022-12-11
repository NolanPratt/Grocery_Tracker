#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <Windows.h>
#include <cmath>
#include <Python.h>
#include <fstream>
using namespace std;

class DisplayMenu {
public:
	int Menu(vector<string> items);
	int TypeCheck();
	DisplayMenu();
private:
	int selection;
};