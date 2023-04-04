#include "Token.h"

//Token Class

ostream & Token::print(ostream & outs) const
{
	int x = -1;
	assert(x != -1);

	return outs;
}

int Token::get_type()
{
	return TOK_TYPE;
}

ostream & operator<<(ostream & outs, const Token& t)
{
	t.print(outs);
	return outs;
}

ostream & operator<<(ostream & outs, Token * t)
{
	t->print(outs);
	return outs;
}
//End of Token Class

//Number Class
ostream& Number::print(ostream & outs) const
{
	outs << _num;
	return outs;
}

int Number::get_type()
{
	return NUM_TYPE;
}

double Number::get_Num()
{
	return _num;
}

void Number::set_Neg(){
	_num *= -1;
}
//END of Number Class

//Operator Class
ostream& Operator::print(ostream & outs) const
{
	outs << _op;
	return outs;
}

int Operator::get_type()
{
	return OP_TYPE;
}

int Operator::order()
{
	char op = _op[0];

	switch (op)
	{
	case '^':
		_order = 3;
		break;
	case '*':
	case '/':
		_order = 2;
		break;
	case '+':
	case '-':
		_order = 1;
		break;
	default:
		cout << "ERROR IN EVAL" << endl;
		break;
	}

	return _order;
}

double Operator::eval(double x, double y)
{
	//INCLUDE Checks for Trig 
	char op = _op[0];
	bool error = false;

	switch (op)
	{
	case '^':
		return pow(x, y);
	case '*':
		return x * y;
	case '/':
		return x / y;
	case '+':
		return x + y;
	case '-':
		return x - y;
	default:
		error = true;
		break;
	}

	assert(error == false);

}
//End Operator Class

//Variable Class
ostream& Variable::print(ostream & outs) const
{
	outs << _var;
	return outs;
}

int Variable::get_type()
{
	return VAR_TYPE;
}
void Variable::set_Neg()
{
	_neg = true;
}
bool Variable::is_Neg()
{
	return _neg;
}
//End of Variable Class

//LPar Class
ostream& LPar::print(ostream& outs) const
{
	outs << _op;
	return outs;
}

int LPar::get_type()
{
	return LPAR_TYPE;
}
//End of LPar Class

//RPar Class
ostream& RPar::print(ostream& outs) const
{
	outs << _op;
	return outs;
}

int RPar::get_type()
{
	return RPAR_TYPE;
}
//End of RPar Class

//Func Class
int Func::get_type()
{
	return FUNC_TYPE;
}

ostream& Func::print(ostream& outs) const
{
	outs << _func;
	return outs;
}

double Func::eval(double x)
{
	if (_func == "sin")
		return sin(x);
	if (_func == "cos")
		return cos(x);
	if (_func == "tan")
		return tan(x);
	if (_func == "csc")
		return (1 / sin(x));
	if (_func == "sec")
		return (1 / cos(x));
	if (_func == "cot")
		return (1 / tan(x));
	if (_func == "ln")
		return log(x);
	if (_func == "log")
		return log10(x);
	if (_func == "sqrt")
		return sqrt(x);
}

double Func::eval(double x, double y)
{
	if (_func == "fmax" || _func == "max")
		return fmax(x,y);
	if (_func == "fmin" || _func == "min")
		return fmin(x,y);
}
int Func::get_param() const
{
	return _param;
}
void Func::set_Neg()
{
	_neg = true;
}
bool Func::is_Neg()
{
	return _neg;
}
//End of Func CLass

//Unary Minus Class
int Minus::get_type()
{
	return MINUS_TYPE;
}

ostream& Minus::print(ostream& outs) const
{
	outs << _minus;
	return outs;
}
//End of Unary Minus Class