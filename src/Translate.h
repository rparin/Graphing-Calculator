#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "Graph_Info.h"
using namespace std;

class Translate {
public:
	Translate(Graph_Info* graph);
	double xCord_to_Screen(double x);
	double yCord_to_Screen(double y);
	double xScreen_to_Cord(double x);
	double yScreen_to_Cord(double y);

private:
	Graph_Info* _graph;
};

#endif //TRANSLATE_H