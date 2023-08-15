#include "Izraz.h"

Izraz::Izraz()
{
	this->izraz = "";
	this->rezultat = 0;
	this->postfix_izraz = "";
}

Izraz::~Izraz()
{
}

Izraz::Izraz(std::string izraz)
{
	this->izraz = izraz;
	//this->rezultat = izracunaj_rezultat();
	this->rezultat = 0;
}

int Izraz::prioritet(char q)
{
	if (q == '+' || q == '-')
		return 1;

	if (q == '*' || q == '/')
		return 2;

	return 0;
}

std::string Izraz::convert_to_postfix()
{
	std::string infix = this->izraz;
	char poslednji_prepisani = ' ';
	int i = 0;
	std::string postfix = "";
	// using inbuilt stack< > from C++ stack library
	std::stack<int> s; //na steku se cuvaju operadni

	while (infix[i] != '\0')
	{

		// if opening bracket then push the stack
		if (infix[i] == '(')
		{
			s.push(infix[i]);
			poslednji_prepisani = ' ';
			i++;
		}
		// if closing bracket encounted then keep popping from stack until 
		// closing a pair opening bracket is not encountered
		else if (infix[i] == ')')
		{
			while (s.top() != '(') {

				postfix += " ";
				postfix += s.top();
				
				s.pop();
			}
			s.pop();
			poslednji_prepisani = ' ';
			i++;
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
		{
			while (!s.empty() && prioritet(infix[i]) <= prioritet(s.top())) {
				postfix += " ";
				postfix += s.top();
				s.pop();
			}
			s.push(infix[i]);
			poslednji_prepisani = ' ';
			i++;
		}
		else {
			// if operand add to the postfix expression
			if (poslednji_prepisani == ' ') {
				postfix += " ";
			}

			postfix += infix[i];
			poslednji_prepisani = infix[i];
			i++;
		}
	}

	while (!s.empty()) {//dodajemo operacije
		postfix += " ";
		postfix += s.top();
		s.pop();
	}

	this->postfix_izraz = postfix;
	return postfix;
}

std::string Izraz::convert_to_infix()
{
	std::string exp = this->postfix_izraz;

	char poslednji_prepisani = ' ';
	std::stack<std::string> s;
	char razmak = ' ';

	for (int i = 0; exp[i] != '\0'; i++)
	{
		// Push operands
		if (exp[i] >= '0' && exp[i] <= '9') {
			if (poslednji_prepisani == razmak) {//upisuje se potpuno novi broj
				std::string op(1, exp[i]); //u string upisujemo jedan char exp[i]
				if (exp[i + 1] == ' ') {
					s.push(op);
				}
				else {
					poslednji_prepisani = exp[i];
				}
			}
			else {//cifra se nadovezuje na predhodnu, sto znaci da je broj dvoocifren
				if (poslednji_prepisani != '|') {
					if (exp[i + 1] == ' ') {
						std::string op(1, exp[i - 1]);
						op = op + exp[i];
						s.push(op);
					}
					else {
						std::string op(1, exp[i - 1]);
						op = op + exp[i] + exp[i + 1];
						s.push(op);
						poslednji_prepisani = '|';
					}
				}
			}
		}
		else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
		{
			std::string op1 = s.top();
			s.pop();
			std::string op2 = s.top();
			s.pop(); //skidamo dva operanda sa steka

			//prioritet(exp[i]);
			s.push("(" + op2 + exp[i] + op1 + ")");
		}
		else if(exp[i] == ' ') {
			poslednji_prepisani = ' ';
		}
	}

	this->postfix_izraz = s.top();
	return s.top();
}

int Izraz::izracunaj_rezultat() //dodati stablo preko kog se racuna razultat izraza
{
	std::stack<char> stack;

	std::string izraz_posfix = this->convert_to_postfix();
	for (char c : izraz_posfix){

		if (c >= '0' && c <= '9' || c == ' ') {
			stack.push(c);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			std::string broj_x;
			std::string broj_y;
			int upisan_prvi = 0;
			int p = 0;
			while (p == 0) {
				char ch = stack.top();

				if (ch != ' ') {
					if (upisan_prvi == 0) {
						broj_x = broj_x + ch;
					}
					else if (upisan_prvi > 0) {
						broj_y = broj_y + ch;
					}
				}
				else {
					if (broj_x.length() > 0) {
						upisan_prvi++;
					}
					
					if (broj_y.length() != 0 || stack.size() == 1) {
						p++;
					}
				}

				if (stack.size() == 1) {
					p++;
				}

				stack.pop();
			}

			int n = broj_x.length();

			for (int i = 0; i < n / 2; i++) {
				std::swap(broj_x[i], broj_x[n - i - 1]);
			}

			int n_y = broj_y.length();

			for (int i = 0; i < n_y / 2; i++) {
				std::swap(broj_y[i], broj_y[n_y - i - 1]);
			}

			int x = atoi(broj_x.c_str());
			int y = atoi(broj_y.c_str());

			if (c == '+') {
				int res = x + y;
				std::stringstream stream;
				stream << res;
				std::string res_str = stream.str();

				if (stack.size() != 0) {
					stack.push(' ');
				}
				for (char rs : res_str) {
					stack.push(rs);
				}
				stack.push(' ');
			}
			else if (c == '-') {
				int res = y - x;
				std::stringstream stream;
				stream << res;
				std::string res_str = stream.str();
				if (stack.size() != 0) {
					stack.push(' ');
				}
				for (char rs : res_str) {
					stack.push(rs);
				}
				stack.push(' ');
			}
			else if (c == '*') {
				int res = x * y;
				std::stringstream stream;
				stream << res;
				std::string res_str = stream.str();

				if (stack.size() != 0) {
					stack.push(' ');
				}
				for (char rs : res_str) {
					stack.push(rs);
				}
				stack.push(' ');
			}
			else if (c == '/') {
				int res = y / x;
				std::stringstream stream;
				stream << res;
				std::string res_str = stream.str();

				if (stack.size() != 0) {
					stack.push(' ');
				}
				for (char rs : res_str) {
					stack.push(rs);
				}
				stack.push(' ');
			}
		}
	}

	std::string rezultat;
	while (stack.size() != 0) {
		rezultat = rezultat + stack.top();
		stack.pop();
	}

	int n_y = rezultat.length();

	for (int i = 0; i < n_y / 2; i++) {
		std::swap(rezultat[i], rezultat[n_y - i - 1]);
	}

	int rez_int = atoi(rezultat.c_str());
	return rez_int;
}

void Izraz::set_izraz(std::string izraz)
{
	this->izraz = izraz;
	this->rezultat = izracunaj_rezultat();
}

void Izraz::set_rezultat()
{
	this->rezultat = this->izracunaj_rezultat();
}

void Izraz::set_posfix(std::string postfix)
{
	this->postfix_izraz = postfix;
}

std::string Izraz::get_izraz()
{
	return this->izraz;
}

int Izraz::get_rezultat()
{
	return this->rezultat;
}

std::string Izraz::get_postfix()
{
	return this->postfix_izraz;
}
