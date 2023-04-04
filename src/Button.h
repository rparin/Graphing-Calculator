#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "Const_Variables.h"
using namespace std;

class Button {
public:

	//Default Constructor
	Button();

	//Drawers
	void drawButton(sf::RenderWindow& win);
	bool hover(sf::RenderWindow& win);

	//Setters
	void setPos(double x = 0.0, double y= 0.0);
	void setTextPos(double x, double y);
	void setSize(double width = 100.0, double height= 100.0);
	void setButtonColor(sf::Color c = sf::Color::Transparent);
	void setTextColor(sf::Color c = sf::Color::Black);
	void setButtonText(string text = "");
	void setTextSize(double size = 0.0);

	//Getter
	string getText();

	//Get Dimension of button
	void print_D();

private:	
	sf::RectangleShape _button;
	sf::Text _text;
	sf::Font _font;
	string _t;

	//Button Dimensions
	double _xL;
	double _xR;
	double _yU;
	double _yD;
	double _width;
	double _height;
};

#endif //BUTTON_H