#include "Textbox.h"

Textbox::Textbox()
{
	setSize();
	setPos();
	setBoxColor();
	setTextColor();
	_font.loadFromFile(FONT_NAME);
	_text.setFont(_font);
	_clicked = false;
	_t = "";
}

void Textbox::storeInput(sf::Event::TextEvent t)
{
	if (sf::Keyboard::isKeyPressed
	(sf::Keyboard::Return)) {
		_clicked = false;
	}
	else if (sf::Keyboard::isKeyPressed
	(sf::Keyboard::Space)) {
		_t += " ";
		_text.setString(_t);
	}
	else if (sf::Keyboard::isKeyPressed
	(sf::Keyboard::BackSpace)) {
		if (_t.length() > 0)
			backspce();
	}
	else if (t.unicode < 128) {
		_t += static_cast<char>(t.unicode);
		_text.setString(_t);
	}
}

void Textbox::setInput(string str)
{
	_t = str;
	_text.setString(str);
}

string Textbox::getText()
{
	remove_space();
	return _t;
}

void Textbox::backspce()
{
	string temp = "";
	for (int i = 0; i < _t.length() - 1; i++) {
		temp += _t[i];
	}
	_t = temp;
	_text.setString(_t);
}

void Textbox::remove_space()
{
	string temp = "";

	for (int i = 0; i < _t.length(); i++) {
		if (_t[i] != ' ')
			temp += _t[i];
	}

	_t = temp;
	_text.setString(_t);
}

void Textbox::draw(sf::RenderWindow& win)
{
	win.draw(_box);
	win.draw(_text);
}

bool Textbox::hover(sf::RenderWindow& win)
{
	double mouseX = sf::Mouse::getPosition(win).x;
	double mouseY = sf::Mouse::getPosition(win).y;

	if (mouseX > _xL&& mouseX < _xR
		&& mouseY > _yD&& mouseY < _yU)
		return true;

	return false;
}

void Textbox::setPos(double x, double y)
{
	x /= SCALER;
	y /= SCALER;

	_xL = x; _xR = x + _width;
	_yU = y + _height; _yD = y;

	_box.setPosition(x, y);
	_text.setPosition(x, y);
}

void Textbox::setSize(double width, double height)
{
	width /= SCALER;
	height /= SCALER;
	_box.setSize(sf::Vector2f(width, height));

	_width = width;
	_height = height;

	int size = 40;

	_text.setCharacterSize(size / SCALER);
	//Scale text with box
}

void Textbox::setBoxColor(sf::Color c)
{
	_box.setFillColor(c);
}

void Textbox::setTextColor(sf::Color c)
{
	_text.setFillColor(c);
}