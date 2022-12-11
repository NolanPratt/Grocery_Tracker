#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class GatherFileLines {
public: 
	GatherFileLines();
	vector<string> FileLinesAsVector(string filename);
private:
	vector<string> linesVector;
};

