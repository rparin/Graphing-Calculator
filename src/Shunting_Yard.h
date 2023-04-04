#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include "Token.h"
#include <sstream>

class Shunt_Yard {
public:
	Shunt_Yard(string infix);
	string _in;
	Queue<Token*> _infix;
	Queue<Token*> _postfix;

private:

	//Takes in Equation String, Return Infix Queue
	Queue<Token*> tokenize(string& equ);

	//Takes in infix queue, Returns postfix Queue
	Queue<Token*> shunting_yard(Queue<Token*> infix);

	//Functions to tokenize input
	int get_Type(string num);
	bool isfunc(string in);
	bool isoperator(char op);
	bool isarith(char op);
	void split_num_var(string to_split, Queue<Token*> &infix);
	string add_spaces(string in);
	string add_spaces_func(string in);
	string remove_spaces(string in);
	void unary_minus(string &in);
	string unary_minus_func(string in);
	bool is_str_alpha(string str);
	void edit(string& str);
	bool invalid(string in);
	void insertNeg1(string& in);
};

#endif //SHUNTING_YARD_H