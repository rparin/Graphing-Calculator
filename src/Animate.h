#ifndef ANIMATE_H
#define ANIMATE_H
#include "Plot.h"
#include "Button.h"
#include "History.h"
#include "Textbox.h"

class Animate {
public:

	//Constructor
	Animate(Plot &plt);
	void run();		//call process, update, and render

private:
	//Setters
	void set_text();
	void set_size();
	void set_color();
	void set_pos();
	void set_his_text();
	void set_BG_Sprite();

	//Drawers
	void draw_BG();
	void draw_axis();
	void draw_points();
	void draw_buttons();
	void showCord(double x, double y);

	//Window things
	bool _update_graph;		//Decides to update or not
	void processEvents();	//handle keyboard and mouse events
	void update();			//Display Next Frame

	//Mouse Variables
	bool _click;
	double _mouseX;
	double _mouseY;

	//Scale Event
	void scale(double mx, double my, int delta);

	//Buttons
	Button _zOut;
	Button _zIn;
	Button _home;
	Button _polar;
	Button _cart;

	//History
	void h_button_clicked(int button_num);
	void rh_button_clicked(int button_num);
	Vector<Button*> h_button;
	void del_h_buttons();
	void hoverAll();
	void clickAll();
	void rclickAll();

	//Inputs
	Textbox _graphInput0;
	Textbox _graphInput1;
	Textbox _graphInput2;
	void _graphEvent(Textbox& obj, sf::Event e, int graph_num);
	void _setInputFalse();
	void _updateInputs();

	//Texts
	sf::Font _font;
	sf::Text _cordinate;

	//Shapes
	sf::RenderWindow _window;
	sf::RectangleShape _BG_graph;
	sf::RectangleShape _BG_option;
	sf::RectangleShape _Xaxis;
	sf::RectangleShape _Yaxis;
	sf::CircleShape _point;
	
	//Picture Background
	sf::Texture _BG_texture;
	sf::Sprite _BG_image;
	sf::Texture _Side_texture;
	sf::Sprite _Side_image;

	//Graph
	Plot _plot;
	Graph_Info* _graph;
	Vector<sf::Vector2f> _cord;
	Translate translate_graph;
	Vector<string> _graphList;
	History _h;
	int cur_graph;

	//Translations
	string cord_to_string(double x);
	double pix_to_scrn(double p);

	//Mouse movement
	void buttonHover(Button& obj, sf::Color col);
	void textHover(Textbox& obj, sf::Color col);

};

#endif //ANIMATE_H