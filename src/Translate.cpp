#include "Translate.h"

Translate::Translate(Graph_Info* graph):
	_graph(graph){
}

double Translate::xCord_to_Screen(double x)
{
	return (X_AXIS + (x * _graph->_scale) 
		+ _graph->_offsetX) * CELL_SIZE + OFFSET;
}

double Translate::yCord_to_Screen(double y)
{
	return (Y_AXIS - (y * _graph->_scale) 
		+ _graph->_offsetY) * CELL_SIZE + OFFSET;
}

double Translate::xScreen_to_Cord(double x)
{
	return (x / (_graph->_scale * CELL_SIZE)) 
		- (X_AXIS / _graph->_scale) -
		(_graph->_offsetX / _graph->_scale) -
		(OFFSET / (_graph->_scale * CELL_SIZE));
}

double Translate::yScreen_to_Cord(double y)
{
	return ((-y / (_graph->_scale * CELL_SIZE) 
		+ (Y_AXIS / _graph->_scale) +
		(_graph->_offsetY / _graph->_scale) +
		(OFFSET / (_graph->_scale * CELL_SIZE))));
}
