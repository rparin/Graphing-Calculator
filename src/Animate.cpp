#include "Animate.h"

Animate::Animate(Plot& plt):
	_plot(plt), _graph(&_plot._graph), 
	translate_graph(&_plot._graph)
{
	//Create and set up Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), 
		TITLE, sf::Style::Default, settings);
	_window.setVerticalSyncEnabled(VSYNC);

	//Set up animate bools
	_update_graph = true;
	_click = false;

	//Set up list of graphs
	for (int i = 0; i < 3; i++)
		_graphList.push_back("");

	//Set UP Multiple Graphs
	cur_graph = 0;

	//Set up Multiple Buttons
	for (int i = 0; i < H_MAX; i++) {
		h_button.push_back(new Button);
	}

	//Display
	_window.display();
	set_BG_Sprite();
}

void Animate::set_text()
{
	//Load and setup font
	_font.loadFromFile(FONT_NAME);
	_cordinate.setFont(_font);
	_cordinate.setString("");
	set_his_text();
}

void Animate::set_size()
{	
	//Set text size and box size for history
	for (int i = 0; i < H_MAX; i++) {
		h_button[i]->setTextSize(35);
		h_button[i]->setSize(398, 40);
	}

	//Set size for graph input buttons
	_graphInput0.setSize(pix_to_scrn(90), pix_to_scrn(10));
	_graphInput1.setSize(pix_to_scrn(90), pix_to_scrn(10));
	_graphInput2.setSize(pix_to_scrn(90), pix_to_scrn(10));

	//Set sizes for graph stuff
	_cordinate.setCharacterSize(40 / SCALER);
	_BG_graph.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	_BG_option.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	_Yaxis.setSize(sf::Vector2f(A_SIZE, CELL_SIZE));
	_Xaxis.setSize(sf::Vector2f(CELL_SIZE, A_SIZE));
	_point.setRadius(P_SIZE /1.5);

	//Set sizes for buttons
	_zOut.setSize(65, 63);
	_zIn.setSize(65, 63);
	_home.setSize(65, 63);
	_polar.setSize(65, 63);
	_cart.setSize(65, 63);
}

void Animate::set_color()
{
	//Set colors for graph stuff
	_cordinate.setFillColor
	(sf::Color::Black);
	_BG_graph.setFillColor
	(sf::Color::Color(CG_BG[0], CG_BG[1], CG_BG[2]));
	_BG_option.setFillColor
	(sf::Color::Color(CO_BG[0], CO_BG[1], CO_BG[2]));
	_Xaxis.setFillColor
	(sf::Color::Color(C_AX[0], C_AX[1], C_AX[2], C_AX[3]));
	_Yaxis.setFillColor
	(sf::Color::Color(C_AX[0], C_AX[1], C_AX[2], C_AX[3]));
}

void Animate::set_pos()
{
	//Mouse Point
	_cordinate.setPosition(0, 0);

	//Buttons
	_zIn.setPos(1290, 36);
	_zOut.setPos(1290, 112);
	_home.setPos(1290, 191);
	_polar.setPos(1290, 269);
	_cart.setPos(1290, 350);

	//Text Box
	_graphInput0.setPos(1420, 60);
	_graphInput1.setPos(1420, 120);
	_graphInput2.setPos(1420, 180);

	//History
	int start = 0;
	for (int i = 0; i < H_MAX; i++) {
		h_button[i]->setPos(1450, 940 + start);
		h_button[i]->setTextPos(1510, 934 + start);
		start -= 45;
	}
}

void Animate::set_his_text()
{
	//Reset history buttons
	for (int i = 0; i < h_button.size(); i++) {
		h_button[i]->setButtonText();
	}

	//Set history buttons
	for (int i = _h._graphs.size()-1; i >= 0; i--) {
		h_button[i]->setButtonText(_h._graphs[i][0]);
	}
}

void Animate::set_BG_Sprite()
{
	//Set up Background image
	_BG_texture.loadFromFile(BG_IMAGE);
	_BG_image.setTexture(_BG_texture);
	_BG_image.scale(sf::Vector2f(I_SCALE, I_SCALE));

	//Set up Side Image
	_Side_texture.loadFromFile(SD_IMAGE);
	_Side_image.setTexture(_Side_texture);
	_Side_image.scale(sf::Vector2f(I_SCALE, I_SCALE));
}

void Animate::draw_BG()
{
	//Values for Cordinates
	int vectorY;
	int vectorX;

	//Draw Graph BG
	for (int row = 0; row < GRAPH_HEIGHT; row++) {
		for (int col = 0; col < GRAPH_WIDTH; col++) {

			vectorY = row * CELL_SIZE;
			vectorX = col * CELL_SIZE;

			_BG_graph.setPosition
			(sf::Vector2f(vectorX, vectorY));
			_window.draw(_BG_graph);
		}
	}

	//Draw Option BG
	for (int row = 0; row < GRID_HEIGHT; row++) {
		for (int col = GRAPH_WIDTH; col < GRID_WIDTH; col++) {

			vectorY = row * CELL_SIZE;
			vectorX = col * CELL_SIZE;

			_BG_option.setPosition
			(sf::Vector2f(vectorX, vectorY));
			_window.draw(_BG_option);
		}
	}

}

void Animate::draw_axis()
{
	int vectorY;
	int vectorX;

	//Draw X Axis
	for (int col = 0; col < GRAPH_WIDTH; col++) {

		vectorX = col * CELL_SIZE;
		vectorY = (Y_AXIS + _graph->_offsetY) * CELL_SIZE;

		_Xaxis.setPosition(sf::Vector2f(vectorX, vectorY));
		_window.draw(_Xaxis);
	}

	//Draw Y Axis
	for (int row = 0; row < GRAPH_HEIGHT; row++) {

		vectorX = (X_AXIS + _graph->_offsetX) * CELL_SIZE;
		vectorY = row * CELL_SIZE;

		_Yaxis.setPosition(sf::Vector2f(vectorX, vectorY));
		_window.draw(_Yaxis);
	}
}

void Animate::run()
{
	//Set items once
	set_text();
	set_size();
	set_pos();
	set_color();

	//Display and Update Graph
	while (_window.isOpen()) {

		processEvents();

		if (_update_graph) {

			update();
		}
	}
}

void Animate::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type) {

		//Close Window and delete dynamically allocated buttons
		case sf::Event::Closed:
			del_h_buttons();
			_window.close();
			break;

		//Resize window if window resized
		case sf::Event::Resized:
			_window.setSize({static_cast<int>(SCREEN_WIDTH), 
				static_cast<int>(SCREEN_HEIGHT) });
			break;

		//Get graph equation user entered
		case sf::Event::TextEntered:
			_graphEvent(_graphInput0, event, 0);
			_graphEvent(_graphInput1, event, 1);
			_graphEvent(_graphInput2, event, 2);
			break;

		//Update graph based on user key input
		case sf::Event::KeyPressed:
			_mouseX = translate_graph.xCord_to_Screen(0);
			_mouseY = translate_graph.yCord_to_Screen(0);
			if (event.key.code == sf::Keyboard::P) {
				if (_graph->_polar)
					_graph->_polar = 0;
				else _graph->_polar = 1;
			}
			if (event.key.code == sf::Keyboard::U) {
				_graph->_polarL += PINC;
			}
			if (event.key.code == sf::Keyboard::I) {
				_graph->_polarR += PINC;
			}
			if (event.key.code == sf::Keyboard::K) {
				if(_graph->_interval >.001)
					_graph->_interval -= .001;
			}
			if (event.key.code == sf::Keyboard::L) {
				_graph->_interval += .001;
			}
			if (event.key.code == sf::Keyboard::Add) {
				_graph->_scale /= ZOOM;
			}
			if (event.key.code == sf::Keyboard::Subtract) {
				_graph->_scale *= ZOOM;
			}
			if (event.key.code == sf::Keyboard::Left)
				_graph->_offsetX -= INC;
			if (event.key.code == sf::Keyboard::Right)
				_graph->_offsetX += INC;
			if (event.key.code == sf::Keyboard::Down)
				_graph->_offsetY += INC;
			if (event.key.code == sf::Keyboard::Up)
				_graph->_offsetY -= INC;
			_graph->_mouse_oX += _mouseX - 
				translate_graph.xCord_to_Screen(0);
			_graph->_mouse_oY += _mouseY - 
				translate_graph.yCord_to_Screen(0);
			showCord(sf::Mouse::getPosition
			(_window).x, sf::Mouse::getPosition(_window).y);
			_update_graph = true;
			break;

		//Update graph based on user mouse input
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Right) {
				_mouseX = event.mouseButton.x;
				_mouseY = event.mouseButton.y;

				//Clear inputs
				if (_graphInput0.hover(_window)) {
					_graphInput0.setInput();
					_graphList[0] = "";

					//Update which graph user entered in
					cur_graph = 0;
				}
				if (_graphInput1.hover(_window)) {
					_graphInput1.setInput();
					_graphList[1] = "";

					//Update which graph user entered in
					cur_graph = 1;
				}
				if (_graphInput2.hover(_window)) {
					_graphInput2.setInput();
					_graphList[2] = "";

					//Update which graph user entered in
					cur_graph = 2;
				}

				//Clear x history button
				rclickAll();
				_update_graph = true;

				//Reset graph to original state if Rclicked on
				if(_mouseX < SCREEN_WIDTH - GRID_WIDTH - X_AXIS)
					_graph->reset();
				break;
			}
			if (event.mouseButton.button == sf::Mouse::Left) {
				_mouseX = event.mouseButton.x;
				_mouseY = event.mouseButton.y;
				if (_zIn.hover(_window)) {
					if (_graph->_polar) _graph->_polarR += PINC;
					else _graph->_scale /= ZOOM;
				}
				if (_zOut.hover(_window)) {
					if(_graph->_polar) _graph->_polarL += PINC;
					else _graph->_scale *= ZOOM;
				}
				if (_home.hover(_window)) {
					_graph->reset();
				}
				if (_polar.hover(_window)) {
					_graph->_polar = 1;
				}
				if (_cart.hover(_window)) {
					_graph->_polar = 0;
				}
				clickAll();
				if (_graphInput0.hover(_window)) {

					//Reset Clicks
					_graphInput0._clicked = true;
					_graphInput1._clicked = false;
					_graphInput2._clicked = false;

					//Update which graph user entered in
					cur_graph = 0;
					_update_graph = true;
					break;
				}
				if (_graphInput1.hover(_window)) {
					//Reset Clicks
					_graphInput0._clicked = false;
					_graphInput1._clicked = true;
					_graphInput2._clicked = false;

					//Update which graph user entered in
					cur_graph = 1;
					_update_graph = true;
					break;
				}
				if (_graphInput2.hover(_window)) {
					//Reset Clicks
					_graphInput0._clicked = false;
					_graphInput1._clicked = false;
					_graphInput2._clicked = true;

					//Update which graph user entered in
					cur_graph = 2;
					_update_graph = true;
					break;
				}
				if(_mouseX < CX*2) _click = true;
			}
			_setInputFalse();
			_update_graph = true;
			showCord(sf::Mouse::
				getPosition(_window).x, 
				sf::Mouse::getPosition(_window).y);
			break;

		//Update mouse moved offset
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == 
				sf::Mouse::Left && _click) {
				_graph->_mouse_oX += 
					_mouseX - event.mouseButton.x;
				_graph->_mouse_oY += 
					_mouseY - event.mouseButton.y;

				_update_graph = true;
				_click = false;
			}
			break;

		//Update graph based on mouse position
		case sf::Event::MouseMoved:
			showCord
			(sf::Mouse::getPosition(_window).x, 
				sf::Mouse::getPosition(_window).y);
			buttonHover
			(_zIn,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			buttonHover
			(_zOut,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			buttonHover
			(_home,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			textHover
			(_graphInput0,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			textHover
			(_graphInput1,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			textHover
			(_graphInput2,  sf::Color::Color(C_HOV[0], 
				C_HOV[1], C_HOV[2], C_HOV[3]));
			hoverAll();
			if (_click) {
				_graph->_offsetX = ((event.mouseMove.x - 
					(_mouseX + _graph->_mouse_oX)) / CELL_SIZE);
				_graph->_offsetY = ((event.mouseMove.y - 
					(_mouseY + _graph->_mouse_oY)) / CELL_SIZE);
				_update_graph = true;
			}
			break;

		//Update graph based on mouse wheel
		case sf::Event::MouseWheelMoved:

			scale(event.mouseButton.x, event.mouseButton.y, 
				event.mouseWheel.delta);

			showCord(sf::Mouse::getPosition(_window).x, 
				sf::Mouse::getPosition(_window).y);

			_update_graph = true;
			break;

		//Do nothing
		default:
			break;
		}
	}
}

void Animate::scale(double mx, double my, int delta)
{
	//Convert Screen Cord to graph Cord
	long double old_Sx = translate_graph.xScreen_to_Cord(mx);
	long double old_Sy = translate_graph.yScreen_to_Cord(my);

	//Scale
	if (delta > 0) _graph->zoomIn();
	else _graph->_scale *= ZOOM;

	//Convert Scaled Screen Cord to new graph Cord
	double new_Sx = translate_graph.xScreen_to_Cord(mx);
	double new_Sy = translate_graph.yScreen_to_Cord(my);

	//Calculate the difference
	double xOffset = new_Sx - old_Sx;
	double yOffset = new_Sy - old_Sy;

	//Convert difference to screen cordinates
	double diff_Sx = translate_graph.xCord_to_Screen(xOffset);
	double diff_Sy = translate_graph.yCord_to_Screen(yOffset);

	//Shift origin to difference
	_graph->shiftOrigin(diff_Sx, diff_Sy);

	//Get New Origin
	double new_xorgin = translate_graph.xCord_to_Screen(0);
	double new_yorgin = translate_graph.yCord_to_Screen(0);

	//Update Mouse Offset for Mouse Moved
	_graph->_mouse_oX = CX - new_xorgin;
	_graph->_mouse_oY = CY - new_yorgin;
}

void Animate::h_button_clicked(int button_num)
{
	//Prevent from going out of bounds
	if (_h._graphs.size() > button_num) {

		//Save equations
		string current = _graph->get_equ();
		string button = _h._graphs[button_num][0];

		//Set graph equations
		_graphList[cur_graph] = button;
		_graph->_equ = button;

		//Update graph input boxes
		if (cur_graph == 0) 
			_graphInput0.setInput(current);
		else if (cur_graph == 1)
			_graphInput1.setInput(current);
		else
			_graphInput2.setInput(current);
	}

	//Reset input clicks
	_setInputFalse();
}

void Animate::rh_button_clicked(int button_num)
{
	if (button_num < _h._graphs.size()) {
		_h._graphs[button_num][0] = "del";
		_h.cleanVec();
		_h.updateFile();
	}
}

void Animate::del_h_buttons()
{
	//Delete dynamically allocated history buttons
	for (int i = 0; i < H_MAX; i++) {
		delete h_button[i];
	}
}

void Animate::hoverAll()
{
	//Change button color if mouse over it
	buttonHover(*h_button[0], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[1], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[2], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[3], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[4], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[5], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[6], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[7], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[8], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[9], sf::Color::Color(C_HOV[0], 
C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[10], sf::Color::Color(C_HOV[0],
 C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[11], sf::Color::Color(C_HOV[0],
 C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[12], sf::Color::Color(C_HOV[0],
 C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[13], sf::Color::Color(C_HOV[0],
 C_HOV[1], C_HOV[2], C_HOV[3]));
	buttonHover(*h_button[14], sf::Color::Color(C_HOV[0],
 C_HOV[1], C_HOV[2], C_HOV[3]));
}

void Animate::clickAll()
{
	//Draw x graph based on history button clicked
	if (h_button[0]->hover(_window)) {
		h_button_clicked(0); _updateInputs();
	}
	else if (h_button[1]->hover(_window)) {
		h_button_clicked(1); _updateInputs();
	}
	else if (h_button[2]->hover(_window)) {
		h_button_clicked(2); _updateInputs();
	}
	else if (h_button[3]->hover(_window)) {
		h_button_clicked(3); _updateInputs();
	}
	else if (h_button[4]->hover(_window)) {
		h_button_clicked(4); _updateInputs();
	}
	else if (h_button[5]->hover(_window)) {
		h_button_clicked(5); _updateInputs();
	}
	else if (h_button[6]->hover(_window)) {
		h_button_clicked(6); _updateInputs();
	}
	else if (h_button[7]->hover(_window)) {
		h_button_clicked(7); _updateInputs();
	}
	else if (h_button[8]->hover(_window)) {
		h_button_clicked(8); _updateInputs();
	}
	else if (h_button[9]->hover(_window)) {
		h_button_clicked(9); _updateInputs();
	}
	else if (h_button[10]->hover(_window)) {
		h_button_clicked(10); _updateInputs();
	}
	else if (h_button[11]->hover(_window)) {
		h_button_clicked(11); _updateInputs();
	}
	else if (h_button[12]->hover(_window)) {
		h_button_clicked(12); _updateInputs();
	}
	else if (h_button[13]->hover(_window)) {
		h_button_clicked(13); _updateInputs();
	}
	else if (h_button[14]->hover(_window)) {
		h_button_clicked(14); _updateInputs();
	}
}

void Animate::rclickAll()
{
	//Delete history based on which button right clicked
	if (h_button[0]->hover(_window)) {
		rh_button_clicked(0);
	}
	else if (h_button[1]->hover(_window)) {
		rh_button_clicked(1);
	}
	else if (h_button[2]->hover(_window)) {
		rh_button_clicked(2);
	}
	else if (h_button[3]->hover(_window)) {
		rh_button_clicked(3);
	}
	else if (h_button[4]->hover(_window)) {
		rh_button_clicked(4);
	}
	else if (h_button[5]->hover(_window)) {
		rh_button_clicked(5);
	}
	else if (h_button[6]->hover(_window)) {
		rh_button_clicked(6);
	}
	else if (h_button[7]->hover(_window)) {
		rh_button_clicked(7);
	}
	else if (h_button[8]->hover(_window)) {
		rh_button_clicked(8);
	}
	else if (h_button[9]->hover(_window)) {
		rh_button_clicked(9);
	}
	else if (h_button[10]->hover(_window)) {
		rh_button_clicked(10);
	}
	else if (h_button[11]->hover(_window)) {
		rh_button_clicked(11);
	}
	else if (h_button[12]->hover(_window)) {
		rh_button_clicked(12);
	}
	else if (h_button[13]->hover(_window)) {
		rh_button_clicked(13);
	}
	else if (h_button[14]->hover(_window)) {
		rh_button_clicked(14);
	}
}

void Animate::_graphEvent(Textbox& obj, 
	sf::Event e, int graph_num)
{
	//Ensure button is clicked so inputs won't happen accidentally
	if (obj._clicked) {

		//Save text input
		obj.storeInput(e.text);

		//Store and plot the new graph input
		if (!obj._clicked) {
			_plot.new_graph(_graph, obj.getText());

			//Don't go out of bounds in array
			if (_graphList.size() > graph_num)
				_graphList[graph_num] = obj.getText();

			//Save current graph equation
			_graph->_equ = obj.getText();

			//Don't save empty inputs
			if (_graph->_equ != "")
				_h.insertGraph(*_graph);

			//Update which graph user entered in
			cur_graph = graph_num;
		}
		_update_graph = true;
	}
}

void Animate::_setInputFalse()
{
	//Reset button clicked bool
	_graphInput0._clicked = false;
	_graphInput1._clicked = false;
	_graphInput2._clicked = false;
}

void Animate::_updateInputs()
{
	//Update graph button text
	_graphInput0.setInput(_graphList[0]);
	_graphInput1.setInput(_graphList[1]);
	_graphInput2.setInput(_graphList[2]);
}

void Animate::showCord(double x, double y)
{	

	//Don't print out cordinates if mouse outside of window
	if (x < CX * 2 && x > 0 && y > 0 && y < CY * 2) {
		double _pointX = translate_graph.xScreen_to_Cord(x);
		double _pointY = translate_graph.yScreen_to_Cord(y);
		
		if (_pointX > 10000.0 || _pointY > 10000.0 
		 || _pointX < -10000.0 || _pointY < -10000.0) {
			_cordinate.setString("(INF,-INF)");
		}
		else {
			_cordinate.setString("(" + cord_to_string(_pointX)
				+ " , " + cord_to_string(_pointY) + ")");
		}
		
	}
	else
		_cordinate.setString("(DNE , DNE)");

	//Resize cordinates based to be consistent with screen
	double width = _cordinate.getLocalBounds().width;
	if (width > 200) {
		_cordinate.setScale(.8f, .8f);
		_cordinate.setPosition(0, 950 / SCALER);
	}
	else if (width > 150) {
		_cordinate.setPosition(0, 950 / SCALER);
	}
	else if (width > 130) {
		_cordinate.setPosition(0, 950 / SCALER);
	}
	else {
		_cordinate.setScale(1.f, 1.f);
		_cordinate.setPosition(0, 950 /SCALER);
	}

	_update_graph = true;
}

void Animate::update()
{
	//Draw History text
	set_his_text();

	//Draw graph background
	_window.draw(_BG_image);

	//Draw axis and points
	draw_axis();
	draw_points();

	//Draw side bard
	_window.draw(_Side_image);

	//Draw cordinates based on mouse pos
	_window.draw(_cordinate);

	//draw all buttons
	draw_buttons();

	//Display all drawn items
	_window.display();

	//Clear window
	_window.clear();

	//Reset update boolean
	_update_graph = false;
}

string Animate::cord_to_string(double x)
{
	//Convert decimal string to two decimal places
	string cord = "";
	string temp = to_string(x);
	bool dec = false;
	int count = 0;
	for (int i = 0; i < temp.length(); i++) {
		cord += temp[i];
		if (temp[i] == '.') dec = true;
		if (dec) count++;
		if (count > 2) break;
	}
	return cord;
}

double Animate::pix_to_scrn(double p)
{
	//Convert pixel to screen cordinate
	return p * CELL_SIZE;
}

void Animate::buttonHover(Button& obj, sf::Color col)
{
	//Highlight button if mouse over
	if (obj.hover(_window) && !_click) {
		obj.setButtonColor(col);
		_update_graph = true;
	}
	else {
		obj.setButtonColor();
		_update_graph = true;
	}
}

void Animate::textHover(Textbox& obj, sf::Color col)
{
	//Highlight text if mouse over
	if (obj.hover(_window) && !_click) {
		obj.setBoxColor(col);
		_update_graph = true;
	}
	else {
		obj.setBoxColor();
		_update_graph = true;
	}
}

void Animate::draw_points()
{
	//Save current graph 
	string temp_str = _graph->_equ;

	//Graph multiple graphs
	for (int i = 0; i < _graphList.size(); i++) {

		//Set and get graph equation to print
		_graph->_equ = Shunt_Yard(_graphList[i])._in;
		if (_graph->_equ != "" ) {

			//Get points to print graph
			Plot temp(_graph);
			_graph->_cords = temp.getPoints();

			//Set Colors for graphs
			if (i == 0)
				_point.setFillColor
				(sf::Color::Color(C_G1[0], C_G1[1], C_G1[2], C_G1[3]));

			else if (i == 1)
				_point.setFillColor
				(sf::Color::Color(C_G2[0], C_G2[1], C_G2[2], C_G2[3]));

			else
				_point.setFillColor
				(sf::Color::Color(C_G3[0], C_G3[1], C_G3[2], C_G3[3]));

			//Print graph
			for (int j = 0; j < _graph->_cords.size(); j++) {
				_point.setPosition(_graph->_cords[j]);
				_window.draw(_point);
			}
		}
	}

	//Revert back to current graph
	_graph->_equ = temp_str;
}

void Animate::draw_buttons()
{
	//Draw button options
	_zIn.drawButton(_window);
	_zOut.drawButton(_window);
	_home.drawButton(_window);

	//Set highlight based on graph mode
	if (_graph->_polar) {
		_polar.setButtonColor
		(sf::Color::Color(C_HOV[0], C_HOV[1], C_HOV[2], C_HOV[3]));
		_cart.setButtonColor();
	}
	else {
		_cart.setButtonColor
		(sf::Color::Color(C_HOV[0], C_HOV[1], C_HOV[2], C_HOV[3]));
		_polar.setButtonColor();
	}

	//Draw mode buttons
	_polar.drawButton(_window);
	_cart.drawButton(_window);

	//Draw history buttons
	for (int i = H_MAX -1; i >= 0; i--) {
		h_button[i]->drawButton(_window);
	}

	//Draw buttons for graph input
	_graphInput0.draw(_window);
	_graphInput1.draw(_window);
	_graphInput2.draw(_window);
}
