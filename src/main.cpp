/*
 * Author: Ralph Parin
 * Project: Graphing Calculator
 */

#include "Animate.h"
using namespace std;

int main() {

	Graph_Info graph;
	Plot cord(&graph);
	Animate g(cord);
	g.run();

	return 0; 
}