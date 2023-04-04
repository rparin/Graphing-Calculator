#include "RPN.h"

RPN::RPN(Queue<Token*> postfix){
	_postfix = postfix;
}

double RPN::eval(double value) {

	//Create a copy so push and pop don't affect postfix
	Queue<Token*> postfix = _postfix;

	//Hold answer
	Stack<double> answer;

	//Values to calculate answer
	double x, y;

	//Used for unary minus
	bool minus = false;

	//Hold Current value
	Token* tok;

	//RPN Algorithm
	while (!postfix.is_empty()) {
		tok = postfix.pop();
		if (tok->get_type() == NUM_TYPE) {
			answer.push(static_cast<Number*>(tok)->get_Num());
		}
		else if (tok->get_type() == OP_TYPE) {
			y = answer.pop(); x = answer.pop();
			Operator* op = static_cast<Operator*>(tok);
			answer.push(op->eval(x, y));
			minus = false;
		}
		else if (tok->get_type() == FUNC_TYPE) {
			Func* func = static_cast<Func*>(tok);
			if (func->get_param() == 1) {
				x = answer.pop();
				if (func->is_Neg())
					answer.push(-func->eval(x));
				else
					answer.push(func->eval(x));
			}
			else {
				y = answer.pop(); x = answer.pop();
				if(func->is_Neg())
					answer.push(-func->eval(x, y));
				else
					answer.push(func->eval(x, y));
			}
			minus = false;
		}
		else if (tok->get_type() == VAR_TYPE) {
			Variable* var = static_cast<Variable*>(tok);
			if(var->is_Neg()) answer.push(-value);
			else answer.push(value);
		}
		else if (tok->get_type() == MINUS_TYPE) {
			minus = true;
		}
	}

	return answer.pop();
}

double RPN::getR(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

double RPN::getTheta(double x, double y) {

	double theta;
	theta = atan(y / x);	//returns in radians
	theta = toDeg(theta);	//Convert to degrees

	//Q#1
	if (x >= 0 && y >= 0) {
		return theta;
	}

	//Q#2
	else if (x < 0 && y >= 0) {
		return theta + 180;
	}

	//Q#3
	else if (x < 0 && y < 0) {
		return theta + 180;
	}

	//Q#4
	else {
		return theta + 360;
	}

}

double RPN::toRad(double x) {
	return (x * (3.141592653589793238463 / 180));
}

double RPN::toDeg(double x) {
	return (x * (180 / 3.141592653589793238463));
}