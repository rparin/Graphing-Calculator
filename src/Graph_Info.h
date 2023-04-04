#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <string>
#include "!includes/myVector.h"
#include <SFML/Graphics.hpp>
#include "Const_Variables.h"
using namespace std;

struct Graph_Info{

	Graph_Info(string infix = "") {
		_equ = infix;

		setWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
		setGrid(GRID_WIDTH, GRID_HEIGHT);
		setOrigin(CX, CY);

		_polar = 0;
		_polarL = -3.14;
		_polarR = 3.14;
		_interval = .01;
		_amt_points = 1000;
		_scale = 30;
		_offsetX = 0;
		_offsetY = 0;
		_mouse_oX = 0;
		_mouse_oY = 0;
	}

	//Setters
	void setDomain(double start, double end) {
		_domain[0] = start;
		_domain[1] = end;
	}

	void setWindow(double width, double height) {
		_window_dimension[0] = width;
		_window_dimension[1] = height;
	}

	void setGrid(double width, double height) {
		_grid_dimension[0] = width;
		_grid_dimension[1] = height;
	}

	void setOrigin(double x, double y) {
		_origin[0] = x;
		_origin[1] = y;
	}

	void shiftOrigin(double x, double y) {
		_offsetX = (x - _origin[0]) / CELL_SIZE;
		_offsetY = (y - _origin[1]) / CELL_SIZE;
	}

	void zoomIn() {
		if (_scale < 2000000000000)
			_scale /= ZOOM;
	}

	void zoomOut() {
		if (_scale > 0.00000000248931)
			_scale *= ZOOM;
	}

	void reset() {
		_interval = .01;
		_offsetX = 0;
		_offsetY = 0;
		_polarR  = PI;
		_polarL  = -PI;
		_scale = 30;
		_mouse_oX = 0;
		_mouse_oY = 0;
		_origin[0] = CX;
		_origin[1] = CY;
	}

	//Get equatiohn with no spaces
	string get_equ() {
		string temp = "";
		for (int i = 0; i < _equ.length(); i++) {
			if(!isspace(_equ[i])) temp += _equ[i];
		}
		_equ = temp;
		return _equ;
	}

	//member access operator
	Graph_Info* operator ->() {
		return this;
	}

	string _equ;
	double _grid_dimension[2];
	double _window_dimension[2];
	double _origin[2];
    double _domain[2];
	double _offsetX;
	double _offsetY;
	int _polar;
	double _interval;
	double _scale;
	double _polarL;
	double _polarR;
	double _mouse_oX;
	double _mouse_oY;
	int _amt_points;
	Vector<sf::Vector2f> _cords;
};
#endif GRAPH_INFO_H