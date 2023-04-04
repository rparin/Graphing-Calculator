#ifndef TOKEN_H
#define TOKEN_H

#include <cmath>
#include <string>
#include <cassert>
#include <iostream>
#include "!includes/myQueue.h"
#include "!includes/myStack.h"
#include "!includes/myVector.h"
#include "Const_Variables.h"
using namespace std;

class Token {
public:
	
	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();

	//Prints the Token using virtual print
	friend ostream& operator << (ostream& outs, const Token& t);
	friend ostream& operator << (ostream& outs, Token* t);

private:
};

//Number inheriting Token
class Variable : public Token {
public:

	Variable(string num) :
		_var(num) {
		_neg = false;
	}

	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();

	//Turns variable to negative
	void set_Neg();
	bool is_Neg();

private:
	string _var;
	bool _neg;
};

//Number inheriting Token
class Number : public Token {
public:

	Number(string num) :
		_num(stod(num)) {
	}

	Number(double num) :
		_num(num) {
	}

	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();

	//Accessor
	double get_Num();

	//Modifier for Unary
	void set_Neg();

private:
	double _num;
};

//Operator inheriting Token
class Operator : public Token {
public:

	//Default Constructor
	Operator(string op) {
		_op = op;
		_order = order();
	}

	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();
	virtual int order();
	virtual double eval(double x, double y);

private:
	int _order;
	string _op;
};

//LPar inheriting Token
class LPar : public Token {
public:

	//Default Constructor
	LPar(string op) {
		_op = op;
	}

	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();

private:
	int _order;
	string _op;
};

//RPar inheriting Token
class RPar : public Token {
public:

	//Default Constructor
	RPar(string op) {
		_op = op;
	}

	//Virtuals
	virtual ostream& print(ostream& outs = cout) const;
	virtual int get_type();

private:
	int _order;
	string _op;
};

//Func inheriting Token
class Func : public Token {
public:

	//Default Constructor
	Func(string func){
		_func = func;
		if (_func == "fmin" || _func == "fmax"
			|| _func == "min" || _func == "max") 
			_param = 2;
		else _param = 1;

		_neg = false;
	}

	//Virtuals
	virtual int get_type();
	virtual ostream& print(ostream& outs = cout) const;
	virtual double eval(double x);
	double eval(double x, double y);

	int get_param() const;
	void set_Neg();
	bool is_Neg();

private:
	string _func;
	int _param;
	bool _neg;
};

//Unary Minus Inheriting Token
class Minus : public Token {
public:

	//Default Constructor
	Minus(string minus) {
		_minus = minus;
	}

	//Virtuals
	virtual int get_type();
	virtual ostream& print(ostream& outs = cout) const;

private:
	string _minus;
};
#endif //TOKEN_H