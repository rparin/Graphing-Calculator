#ifndef HISTORY_H
#define HISTORY_H
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cassert>
#include "Const_Variables.h"
#include "Graph_Info.h"
#include "!includes/myQueue.h"
#include "!includes/myVector.h"
using namespace std;

class History{
public:

	History(int size = H_MAX, string filename = FILE_NAME)
		: _filename(filename) {
		_size = size;
		openFile();
		readFile();
	};

	Queue<Vector<string>> _graphs;
	void print();
	void print_data_at(int x);
	void insertGraph(Graph_Info graph);
	void updateFile();
	void cleanVec();
private:
	ifstream _inFile;
	ofstream _outFile;
	string _filename;
	int _size;

	void openFile();
	string header();
	void readFile();
	void replace(string& source, 
		char search = ',', char item = ' ');
	string remove_space(string in);
	void updateVector(Graph_Info graph);
	void maintainSize();
};


#endif HISTORY_H