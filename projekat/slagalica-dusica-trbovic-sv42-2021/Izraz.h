#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <sstream>
#include <fstream>
#include <iterator>

class Izraz {
protected:
	std::string izraz;
	int rezultat;
	std::string postfix_izraz;
public:
	Izraz();
	~Izraz();
	Izraz(std::string izraz);
	int prioritet(char q);
	std::string convert_to_postfix();
	std::string convert_to_infix();
	int izracunaj_rezultat();

	//geteri i seteri
	void set_izraz(std::string izraz);
	void set_rezultat();
	void set_posfix(std::string postfix);
	std::string get_izraz();
	int get_rezultat();
	std::string get_postfix();
};