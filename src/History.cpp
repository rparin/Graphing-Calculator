#include "History.h"

void History::print()
{
	for (int i = 0; i < _graphs.size(); i++) {
		cout << _graphs[i] << endl;
	}
}

void History::print_data_at(int x)
{
	assert(x < _graphs.size());
	for (int j = 0; j < _graphs[x].size(); j++) {
		cout << _graphs[x][j] << " ";
	}
}

void History::insertGraph(Graph_Info graph)
{
	//open file to read
	_outFile.open(_filename, ios_base::app);

	string to_insert;

	to_insert += remove_space(graph._equ);
	replace(to_insert, ',', '|');
	to_insert += ",";
	to_insert += to_string(graph._domain[0]);
	to_insert += ",";
	to_insert += to_string(graph._domain[1]);
	to_insert += ",";
	to_insert += to_string(graph._scale);
	to_insert += ",";
	to_insert += to_string(graph._amt_points);
	to_insert += ",";
	to_insert += to_string(graph._offsetX);
	to_insert += ",";
	to_insert += to_string(graph._offsetY);
	to_insert += ",";
	to_insert += to_string(graph._mouse_oX);
	to_insert += ",";
	to_insert += to_string(graph._mouse_oY);
	to_insert += ",";
	to_insert += to_string(graph._polar);

	_outFile << to_insert << endl;

	//close file
	_outFile.close();

	//Update graph and file and maintain its size
	updateVector(graph);
	if (_graphs.size() > _size) {
		maintainSize();
		updateFile();
	}
}


void History::updateVector(Graph_Info graph)
{
	//Prep infix to store
	string infix = remove_space(graph._equ);

	//Store data to Queue
	Vector<string> temp;
	temp.push_back(infix);
	temp.push_back(to_string(graph._domain[0]));
	temp.push_back(to_string(graph._domain[1]));
	temp.push_back(to_string(graph._scale));
	temp.push_back(to_string(graph._amt_points));
	temp.push_back(to_string(graph._offsetX));
	temp.push_back(to_string(graph._offsetY));
	temp.push_back(to_string(graph._mouse_oX));
	temp.push_back(to_string(graph._mouse_oY));
	temp.push_back(to_string(graph._polar));

	//Save to Vector
	_graphs.push(temp);
}

void History::maintainSize() {
	while (_graphs.size() > _size)
		_graphs.pop();
}

void History::updateFile()
{
	//Open and Clear File
	_outFile.open(_filename);

	//insert header
	_outFile << header() << endl;

	//Write New Data to file
	for (int i = 0; i < _graphs.size(); i++) {
		for (int j = 0; j < _graphs[i].size(); j++) {
			if (j == 0) {
				replace(_graphs[i][j], ',', '|');
				_outFile << _graphs[i][j];
				replace(_graphs[i][j], '|', ',');
			}
			else
				_outFile << _graphs[i][j];
			if(j != _graphs[i].size()-1) _outFile << ",";
			
		}
		_outFile << endl;
	}

	//close file
	_outFile.close();

}

void History::cleanVec()
{
	Queue<Vector<string>> _newgraphs;
	for (int i = 0; i < _graphs.size(); i++) {
		if (_graphs[i][0] != "del") {
			_newgraphs.push(_graphs[i]);
		}
	}

	_graphs = _newgraphs;
}

string History::remove_space(string in)
{
	string out = "";

	for (int i = 0; i < in.length(); i++) {
		if (in[i] != ' ')
			out += in[i];
	}

	return out;
}

void History::openFile()
{
	//open file to read
	_inFile.open(_filename);

	//create file if can't open
	if (_inFile.fail())
	{

		//create file to write to
		_outFile.open(_filename);

		//insert header
		_outFile << header() << endl;

		//close file
		_outFile.close();
	}
	else
		//close file
		_inFile.close();
}

string History::header()
{
	string out;
	out = "Infix,DomainL,DomainR,Scale,Amount of Points,";
	out += "Offset X,Offset Y,Mouse Offset x,Mouse Offset y,Polar";
	return out;
}

void History::readFile()
{
	stringstream ss;
	string line;
	string data = "";

	//open file to read
	_inFile.open(_filename);

	//Ignore first line
	getline(_inFile, line);


	while (getline(_inFile, line)) {
		int count = 0;
		Vector<string> temp;

		//Remove Commas in string
		replace(line);

		//store the line in sstream
		ss << line;

		//Read and store data
		while (ss >> data) {
			if (count == 0) replace(data, '|', ',');
			temp.push_back(data);
			count++;
		}

		_graphs.push(temp);

		if (_graphs.size() >= _size) break;

		//Clear stream to allow another line to be read
		ss.clear();
	}

	//close file
	_inFile.close();
}

void History::replace(string& source, char search, char item)
{
	for (int i = 0; i < source.length(); i++) {
		if (source[i] == search) {
			source[i] = item;
		}
	}
}
