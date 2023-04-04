#include "Button.h"

Button::Button()
{
	setSize();
	setPos();
	setTextSize();
	setButtonText();
	setTextColor();
	setButtonColor();
	_font.loadFromFile(FONT_NAME);
	_text.setFont(_font);
}

void Button::drawButton(sf::RenderWindow& win)
{
	win.draw(_button);
	win.draw(_text);
}

bool Button::hover(sf::RenderWindow& win)
{
	double mouseX =  sf::Mouse::getPosition(win).x;
	double mouseY =  sf::Mouse::getPosition(win).y;

	//				yU
	//		   -------------
	//		xL|	  Button	| xR
	//		  |				|
	//		   -------------
	//				yD

	if (mouseX > _xL && mouseX < _xR 
		&& mouseY > _yD && mouseY < _yU)
		return true;

	return false;
}

void Button::setPos(double x, double y)
{
	x /= SCALER;
	y /= SCALER;

	_xL = x; _xR = x + _width;
	_yU = y + _height; _yD = y;

	_button.setPosition(x, y);
	_text.setPosition(x+5, y-5);
}

void Button::setTextPos(double x, double y)
{
	x /= SCALER;
	y /= SCALER;
	_xL = x; _xR = x + _width;
	_yU = y + _height; _yD = y;

	_text.setPosition(x, y);
}

void Button::setSize(double width, double height)
{
	width /= SCALER;
	height /= SCALER;
	_button.setSize(sf::Vector2f(width, height));

	_width = width;
	_height = height;
}

void Button::setButtonColor(sf::Color c)
{
	_button.setFillColor(c);
}

void Button::setTextColor(sf::Color c)
{
	_text.setFillColor(c);
}

void Button::setButtonText(string text)
{
	_text.setString(text);
	_t = text;
}

void Button::setTextSize(double size)
{
	_text.setCharacterSize(size / SCALER);
}

string Button::getText()
{
	return _t;
}

void Button::print_D()
{
	cout << endl;
	cout << "xL: " << _xL << endl;
	cout << "xR: " << _xR << endl;
	cout << "yU: " << _yU << endl;
	cout << "yD: " << _yD << endl;
	cout << endl;
}
