#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "Const_Variables.h"
using namespace std;

class Textbox {
public:

	Textbox();

	//Drawers
	void draw(sf::RenderWindow& win);
	bool hover(sf::RenderWindow& win);

	//Setters
	void setPos(double x = 0.0, double y = 0.0);
	void setSize(double width = 100.0, double height= 100.0);
	void setBoxColor(sf::Color c = sf::Color::Transparent);
	void setTextColor(sf::Color c = sf::Color::Black);
	void storeInput(sf::Event::TextEvent t);
	void setInput(string str = "");

	//Get text from box
	string getText();

	//Keep track if button clicked
	bool _clicked;

private:	
	sf::RectangleShape _box;
	sf::Text _text;
	sf::Font _font;
	string _t;


	void backspce();
	void remove_space();
	
	//Button Dimensions
	double _xL;
	double _xR;
	double _yU;
	double _yD;
	double _width;
	double _height;
};

#endif //TEXTBOX_H