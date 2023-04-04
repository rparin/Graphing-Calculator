#ifndef RPN_H
#define RPN_H

#include "Token.h"
using namespace std;

class RPN {
public:
	RPN(Queue<Token*> postfix);
	double eval(double value);
	double getR(double x, double y);
	double getTheta(double x, double y);
	double toRad(double x);
	double toDeg(double x);
private:
	Queue<Token*> _postfix;
};

#endif //RPN_H