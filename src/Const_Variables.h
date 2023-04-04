#ifndef CONST_VARIABLES_H
#define CONST_VARIABLES_H
#include <string>
using namespace std;

//Grid GUI Constants
const double SCALER = 1.4;
const double GRID_WIDTH = 380 / SCALER; //Right Bar
const double GRID_HEIGHT = 200 / SCALER; //Right Bar
const int CELL_SIZE = 5;
const int BORDER = 0;
const double SCREEN_WIDTH = (CELL_SIZE * GRID_WIDTH); //950
const double SCREEN_HEIGHT = (CELL_SIZE * GRID_HEIGHT); //500
const int FRAME = 144;
const bool VSYNC = false;

//String Constants
const string TITLE = "Graphing Calculator";			//Title
const string BG_IMAGE = "Assets/BG.png";			//Image
const string SD_IMAGE = "Assets/SideBG.png";		//Side Bar
const string FONT_NAME = "Assets/Lib.ttf";			//Font
const string FILE_NAME = "Assets/graphs.csv";		//History

//Image Scaler
const double SCALE = SCALER;
const double I_SCALE = 
(SCREEN_WIDTH / (GRID_WIDTH * SCALE)) / 4.16667;

//Graph Constants
const double X_AXIS = 140 / SCALER;
const int Y_AXIS = 100 / SCALER;
const int GRAPH_WIDTH = 280 / SCALER;
const int GRAPH_HEIGHT = 200 / SCALER;
const long double CX = X_AXIS * CELL_SIZE;
const long double CY = SCREEN_HEIGHT / 2;

//Event Constants
const double PINC = .3;
const int INC = 1;
const double ZOOM = .7;
const double DRAG_SPEED = .01 / SCALER;

//Colors for GUI
const int C_AX[4] =  { 0, 0, 0 , 90 };
const int CG_BG[3] = { 21, 5, 15 };
const int CO_BG[3] = { 0, 76, 74 };
const int C_G1[4] =   { 255, 255, 255 , 100 };
const int C_G2[4] =   { 155, 155, 155 , 100 };
const int C_G3[4] =   { 127, 99, 6 , 100 };
const int C_HOV[4] =   { 69, 67, 59, 50 };

//Point size
const double P_SIZE = 3;
const double A_SIZE = 2;
const double OFFSET = static_cast<double>(A_SIZE - P_SIZE);

//Token Types
const int TOK_TYPE = 0;
const int NUM_TYPE = 1;
const int OP_TYPE = 2;
const int VAR_TYPE = 3;
const int LPAR_TYPE = 4;
const int RPAR_TYPE = 5;
const int FUNC_TYPE = 6;
const int MINUS_TYPE = 7;

//History Amount
const int H_MAX = 15;

//Math constants
const double PI = 3.14159265359;
const double E = 2.718281828459;

#endif //CONST_VARIABLES_H