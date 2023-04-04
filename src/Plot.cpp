#include "Plot.h"


Plot::Plot(Graph_Info* graph):
	_graph(*graph), _rpn(Shunt_Yard(graph->_equ)._postfix)
	,_equ(Shunt_Yard(graph->_equ)), translate_graph(graph){
}

Vector<sf::Vector2f> Plot::getPoints()
{
	Vector<sf::Vector2f> cord;
	if (_graph._polar == 1)
		return getPolarPoints();
	else 
		return getXYPoints();
}

Vector<sf::Vector2f> Plot::getXYPoints()
{
	Vector<sf::Vector2f> cord;
	double j;
	double vectorY;
	double vectorX;

	_graph._domain[0] = translate_graph.xScreen_to_Cord(0);
	_graph._domain[1] = translate_graph.xScreen_to_Cord(CX*2);
	_graph._interval = (_graph._domain[1] - _graph._domain[0])
		/ _graph._amt_points;

	for (double i = _graph._domain[0]; 
		i < _graph._domain[1]; 
		i += _graph._interval) {
		j = eval(i);

		vectorX = translate_graph.xCord_to_Screen(i);
		vectorY = translate_graph.yCord_to_Screen(j);

		if (vectorX < _graph._window_dimension[0] 
			&& vectorY < _graph._window_dimension[1]) {
			cord.push_back(sf::Vector2f(static_cast<float>(vectorX),
				static_cast<float>(vectorY)));
		}
	}
	return cord;
}

Vector<sf::Vector2f> Plot::getPolarPoints()
{
	Vector<sf::Vector2f> cord;
	double x, y, r;
	double vectorY;
	double vectorX;

	for (double i = _graph._polarL; 
		i < _graph._polarR; i += _graph._interval) {
        r = eval(i);
		x = r * cos(i);
		y = r * sin(i);
		vectorX = translate_graph.xCord_to_Screen(x);
		vectorY = translate_graph.yCord_to_Screen(y);

		if (vectorX < _graph._window_dimension[0]
			&& vectorY < _graph._window_dimension[1]) {
			cord.push_back(sf::Vector2f(static_cast<float>(vectorX),
				static_cast<float>(vectorY)));
		}

	}
	return cord;
}


double Plot::eval(double x)
{
	return _rpn.eval(x);
}

void Plot::deallocate()
{
	for (int i = 0; i < _equ._postfix.size(); i++) {
		delete _equ._postfix[i];
	}
}

void Plot::new_graph(Graph_Info* graph)
{
	deallocate();

	string infix;
	getline(cin,infix);

	//Create new graph info to reset variables
	Graph_Info temp(infix);
	*graph = temp;

	*this = Plot(graph);
}

void Plot::new_graph(Graph_Info* graph, string infix)
{
	deallocate();

	graph->_equ = infix;
}

void Plot::new_graph(Graph_Info* graph, Vector<string>& info)
{
	deallocate();

	Vector<string> t;
	t.push_back(graph->_equ);
	t.push_back(to_string(graph->_domain[0]));
	t.push_back(to_string(graph->_domain[1]));
	t.push_back(to_string(graph->_scale));
	t.push_back(to_string(graph->_amt_points));
	t.push_back(to_string(graph->_offsetX));
	t.push_back(to_string(graph->_offsetY));
	t.push_back(to_string(graph->_mouse_oX));
	t.push_back(to_string(graph->_mouse_oY));
	t.push_back(to_string(graph->_polar));

	//Create new graph info to reset variables
	Graph_Info temp(info[0]);
	temp.setDomain(stod(info[1]), stod(info[2]));
	temp._scale = stod(info[3]);
	temp._amt_points = stod(info[4]);
	temp._offsetX = stod(info[5]);
	temp._offsetY = stod(info[6]);
	temp._mouse_oX = stod(info[7]);
	temp._mouse_oY = stod(info[8]);
	temp._polar = stoi(info[9]);

	//Replace graph info in file
	info = t;
	//Set current Graph
	*graph = temp;


	*this = Plot(graph);
}