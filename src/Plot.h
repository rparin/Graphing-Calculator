#ifndef PLOT_H
#define PLOT_H

#include "Shunting_Yard.h"
#include "RPN.h"
#include "Translate.h"

class Plot {
public:
	//Default constructor
	Plot(Graph_Info* graph);

	//Objects created
	Graph_Info _graph;
	Shunt_Yard _equ;

	//Hold points
	Vector<sf::Vector2f> getPoints();
	Vector<sf::Vector2f> getXYPoints();
	Vector<sf::Vector2f> getPolarPoints();

	//Calculate using rpn
	double eval(double x);

	//Delete token pointers
	void deallocate();

	//Create new graphs based on parameter input
	void new_graph(Graph_Info* graph);
	void new_graph(Graph_Info* graph, string infix);
	void new_graph(Graph_Info* graph, Vector<string>& info);

private:
	Translate translate_graph;
	RPN _rpn;
	Vector<sf::Vector2f> _cords;
};


#endif //PLOT_H