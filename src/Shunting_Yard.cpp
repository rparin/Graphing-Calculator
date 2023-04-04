#include "Shunting_Yard.h"

Shunt_Yard::Shunt_Yard(string in)
{
	_in = in;
	_infix = tokenize(_in);
	_postfix = shunting_yard(_infix);
}

bool Shunt_Yard::invalid(string in)
{
	string temp = remove_spaces(in);
	if(temp == "") return true;

	//Check if operator at the front
	if (isarith(temp[0]) && temp[0] != '-') return true;
	if (temp.length() == 1) {
		if (isarith(temp[0])) return true;
	}

	//Check for invalid operators
	temp += " ";
	int count = 0;
	for (int i = 0; i < temp.length()-1; i++) {
		if (temp[i] =='.' && isalpha(temp[i + 1]))
			return true;
		if (isalpha(temp[i]) && isdigit(temp[i + 1]))
			return true;
		if (temp[i] == '-') count++; else count = 0;
		if (count >= 2) return true;
		if (temp[i] == ')' && temp[i + 1] == '(')
			return true;
		if (temp[i] == '(' && temp[i + 1] == ')') {
			return true;
		}
		if (temp[i] == '(' && isarith(temp[i + 1])) {
			if (temp[i + 1] != '-')
				return true;
		}
		if (isarith(temp[i]) && isarith(temp[i + 1])) {
			if(temp[i] != '-' && temp[i+1] != '-')
				return true;
		}
		if (ispunct(temp[i]) && ispunct(temp[i + 1])) {
			if ((temp[i] != '-' && temp[i + 1] != '(') 
			  && temp[i] != '(' && temp[i + 1] != '-' 
			  && temp[i] != '(' && temp[i + 1] != '('
			  && temp[i] != ')' && temp[i + 1] != ')'
			  && temp[i] != '^' && temp[i + 1] != '('
			  && temp[i] != ')' && temp[i + 1] != '-')
				return true;
		}

		if (ispunct(temp[i]) && !isoperator(temp[i])) {
			if(temp[i] != ',' && temp[i] != '.')
				return true;
		}
	}
	//Check if last item is an arithmatic value
	if (isarith(in[in.length() - 1])) return true;

	//Check if invalid functions entered
	string checkFunc = remove_spaces(in);
	checkFunc += " ";
	temp = "";
	for (int i = 0; i < checkFunc.length()-1; i++) {
		if(isalpha(checkFunc[i])) temp += checkFunc[i];
		if (isfunc(temp)) {
			if (checkFunc[i + 1] != '(') return true;
			temp = "";
			cout << temp << endl;
		}
		if (isdigit(checkFunc[i])) temp = "";
		if (isoperator(checkFunc[i])) temp = "";
	}

	//Check for wrong amount of parenthesis
	temp = remove_spaces(in);
	int lPar = 0;
	int rPar = 0;
	string checkVar = "";
	for (int i = 0; i < temp.length(); i++) {
		if (isalpha(temp[i])) checkVar += temp[i];
		if (isfunc(checkVar)) checkVar = "";
		if (temp[i] == '(') lPar++;
		if (temp[i] == ')') rPar++;
		if(temp[i] == '(' || temp[i] == ')') checkVar = "";
	}
	if (lPar != rPar) return true;

	//Check for multiple variables
	char var = checkVar[0];
	for (int i = 0; i < checkVar.length(); i++) {
		if (checkVar[i] != var) return true;
	}

	//Check decimals
	string digit = "";
	int cnt = 0;
	temp = remove_spaces(in);
	for (int i = 0; i < temp.length(); i++) {
		if (isdigit(temp[i])) digit += temp[i];
		if(isalpha(temp[i])) digit = "";
		if (temp[i] == '.') {
			digit += temp[i];
			for (int j = 0; j < digit.length(); j++) {
				if (digit[j] == '.') cnt++;
			}
		}
		if (cnt >= 2) return true;
	}

	return false;
}

void Shunt_Yard::insertNeg1(string& in)
{
	string temp = remove_spaces(in);
	temp += " ";
	bool insert = false;
	int count = 1;
	for (int i = 0; i < temp.length()-1; i++) {
		if (temp[i] == '-' && temp[i + 1] == '(') {
			insert = true;
			count++;
		}
	}
	if (insert) {
		string newIn = "";
		int length = temp.length();
		for (int i = 0; i < length - 1; i++) {
			if (count == 0) break;
			if (temp[i] == '-' && temp[i + 1] == '(') {
				newIn += "-1*";
				count--;
			}
			else {
				newIn += temp[i];
			}
			length = temp.length();
		}
		in = newIn;
	}

}

Queue<Token*> Shunt_Yard::tokenize(string& in)
{
	//Check string if input is valid
	Queue<Token*> infix;
	if (invalid(in)) {
		_in = "";
		return infix;
	}
	insertNeg1(in);
	//Separate string into tokens
	string equ = remove_spaces(in);
	unary_minus(equ);
	equ = add_spaces(equ);
	equ = unary_minus_func(equ);
	equ = add_spaces(equ);
	edit(equ);
	equ = add_spaces(equ);

	string tok;
	stringstream ss;
	ss << equ;

	int option;
	bool multiply = false;
	bool rightP = false;
	while (ss >> tok) {

		if (tok == "|")
			ss >> tok;

		option = get_Type(tok);

		//Functions
		if (isfunc(tok)) {
			if (rightP)
				infix.push(new Operator("*"));
			rightP = false;
			infix.push(new Func(tok));
			multiply = false;
		}

		//Variable
		else if (is_str_alpha(tok)) {
			infix.push(new Variable(tok));
			multiply = true;
		}

		//Number
		else if (option == 1) {
			infix.push(new Number(tok));
			multiply = true;
		}

		//Number * Variable
		else if (option == 2) {
			split_num_var(tok, infix);
			multiply = true;
		}

		//Operators
		else if (option == 3) {

			if (tok == "+") {
				infix.push(new Operator(tok));
				rightP = false;
			}
			else if (tok == "-") {
				infix.push(new Operator(tok));
				rightP = false;
			}
			else if (tok == "*") {
				infix.push(new Operator(tok));
				rightP = false;
			}
			else if (tok == "/") {
				infix.push(new Operator(tok));
				rightP = false;
			}
			else if (tok == "^") {
				infix.push(new Operator(tok));
				rightP = false;
			}
			else if (tok == "(") {
				if (multiply || rightP)
					infix.push(new Operator("*"));
				infix.push(new LPar(tok));
			}
			else if (tok == ")") {
				rightP = true;
				infix.push(new RPar(tok));
			}
			else if (tok == "#") {
				infix.push(new Minus("-"));
			}
			multiply = false;
		}
	}

	equ = remove_spaces(in);
	return infix;
}

string Shunt_Yard::remove_spaces(string in)
{
	string out = "";

	for (int i = 0; i < in.length(); i++) {
		if (in[i] != ' ')
			out += tolower(in[i]);
	}

	return out;
}

void Shunt_Yard::unary_minus(string& in)
{
	string temp = "";
	int start = 0;

	if (in.length() >= 1) {
		if (in[0] == '-' && (isdigit(in[1]) || isalpha(in[1]))) {
			start = 1;
			temp += "#";
		}
	}

	for (int i = start; i < in.length() - 1; i++) {

		if (in[i] == '-') {
			if (isoperator(in[i + 1])) {
				temp += in[i];
			}
			else if (isdigit(in[i + 1]) || isalpha(in[i + 1])) {
				if (!isalpha(in[i - 1]))
					temp += "#";
				else
					temp += in[i];
			}
		}
		else {
			temp += in[i];
		}
	}

	temp += in[in.length() - 1];
	in = temp;
	for (int i = 0; i < in.length(); i++) {
		if (in[i] == '#' && i-1 != -1) {
			if (in[i - 1] == ')')
				in[i] = '-';
		}
	}
}

string Shunt_Yard::unary_minus_func(string in)
{
	string temp = in;
	stringstream ss;
	ss << temp;
	string out = "";

	//Store infix to array
	string infix[100];  int size = 0;
	while (ss >> temp) {
		infix[size] = temp;
		size++;
	}

	//Check if - is unary and set to unary if necessary
	for (int i = 1; i < size; i++) {
		if (isfunc(infix[i])) {
			if (i - 1 >= 0 && infix[i - 1] == "#") {
				if (i - 2 >= 0 && get_Type(infix[i - 2]) == 1) {
					infix[i - 1] = "-";
				}
				else if (infix[i - 2] == ")") {
					infix[i - 1] = "-";
				}

			}
		}
	}

	//Create clean equation
	for (int i = 0; i < size; i++) {
		out += infix[i];
	}
	return out;
}

int Shunt_Yard::get_Type(string num) {

	string digits;

	for (int i = 0; i < num.length(); i++) {

		if (isoperator(num[i])) {
			return 3;
		}

		//Variable
		if (isalpha(num[i])) {
			return 2;
		}

	}

	//Whole String is digit
	return 1;
}

bool Shunt_Yard::isoperator(char op) {

	switch (op)
	{
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
	case '(':
	case ')':
	case '#':
	case '|':
		return true;
	default:
		return false;
	}
}

bool Shunt_Yard::isarith(char op) {

	switch (op)
	{
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
		return true;
	default:
		return false;
	}
}

bool Shunt_Yard::isfunc(string in) {

	if (in == "sin" || in == "cos" || in == "tan"
		|| in == "csc" || in == "sec" || in == "cot"
		|| in == "fmin" || in == "fmax" || in == "ln"
		|| in == "log" || in == "max" || in == "min"
		|| in == "sqrt")
		return true;

	return false;
}

void Shunt_Yard::split_num_var(string to_split, 
	Queue<Token*> &infix) {

	string num = "";
	string var = "";

	//Split to number * variable
	for (int i = 0; i < to_split.length(); i++) {

		if (!isalpha(to_split[i])) num += to_split[i];

		if (isalpha(to_split[i])) {

			for (int j = i; j < to_split.length(); j++) {


				var += to_split[j];
				if (!isalpha(to_split[j])) break;

			}
			break;
		}
	}

	infix.push(new Number(num));
	infix.push(new Operator("*"));
	infix.push(new Variable(var));
}

string Shunt_Yard::add_spaces(string in) {

	string equ = "";

	for (int i = 0; i < in.length() - 1; i++) {
		equ += in[i];

		if (isoperator(in[i]) || isoperator(in[i + 1])) {
			equ += " ";
		}
	}

	equ += in[in.length() - 1];

	return equ;
}

string Shunt_Yard::add_spaces_func(string in) {

	string equ = "";
	string temp = "";

	for (int i = 0; i < in.length(); i++) {
		equ += in[i];

		if (isalpha(in[i])) temp += in[i];
		if (isfunc(temp)) {
			temp = "";
			equ += " ";
		}
	}

	return equ;
}

bool Shunt_Yard::is_str_alpha(string str) {

	for (int i = 0; i < str.length(); i++) {

		if (!isalpha(str[i])) {
			return false;
		}
	}

	return true;
}

void Shunt_Yard::edit(string &str) {

	for (int i = 0; i < str.length(); i++) {

		//Lower case strings
		if (isalpha(str[i])) {
			str[i] = tolower(str[i]);
		}

		//Turn commas into '|'
		if (str[i] == ',') {
			str[i] = '|';
		}
	}

}

Queue<Token*> Shunt_Yard::shunting_yard(Queue<Token*> infix) {
	
	//Linked lists to create postfix
	Queue<Token*> output;
	Stack<Token*> operators;

	//Token to hold current value in link list
	Token* token;

	//Minus for unary operator
	bool minus = false;

	//Shunting yard algorithm
	while (!infix.is_empty()) {
		token = infix.pop();

		if (token->get_type() == NUM_TYPE) {
			Number* tok = static_cast<Number*>(token);
			if (minus) tok->set_Neg();
			output.push(token);
			minus = false;
		}
		if (token->get_type() == VAR_TYPE) {
			Variable* tok = static_cast<Variable*>(token);
			if (minus) tok->set_Neg();
			output.push(token);
			minus = false;
		}
		else if (token->get_type() == FUNC_TYPE) {
			Func* tok = static_cast<Func*>(token);
			if (minus) tok->set_Neg();
			operators.push(token);
			minus = false;
		}
		else if (token->get_type() == OP_TYPE) {

			Operator* tok = static_cast<Operator*>(token);

			if (operators.is_empty()) {
				operators.push(token);
			}
			else if (operators[0]->get_type() == FUNC_TYPE) {

				while (!operators.is_empty()
					&& operators[0]->get_type() == FUNC_TYPE) {
					output.push(operators.pop());
				}
				operators.push(token);
			}
			else if (operators[0]->get_type() == OP_TYPE) {

				Operator* top = static_cast<Operator*>(operators[0]);

				if (top->order() == 3 && 
					tok->order() == top->order()) {
					operators.push(token);
				}
				else if (top->order() >= tok->order()) {
					while (top->order() >= tok->order()
						&& !operators.is_empty()) {
						output.push(operators.pop());
						if (!operators.is_empty())
							top = static_cast<Operator*>(operators[0]);
						if (top->get_type() == LPAR_TYPE) break;
					}
					operators.push(token);
				}
				else {
					operators.push(token);
				}
			}
			else {
				operators.push(token);
			}
		}
		else if (token->get_type() == LPAR_TYPE) {
			operators.push(token);
		}
		else if (token->get_type() == RPAR_TYPE) {
			Token* top = static_cast<Token*>(operators[0]);
			while (top->get_type() != LPAR_TYPE) {
				output.push(operators.pop());
				top = static_cast<Token*>(operators[0]);
			}
			if (top->get_type() == LPAR_TYPE) {
				operators.pop();
			}
		}
		else if (token->get_type() == MINUS_TYPE) {
			minus = true;
		}
	}

	while (!operators.is_empty()) {
		output.push(operators.pop());
	}

	return output;
}
