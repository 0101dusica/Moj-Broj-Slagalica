#pragma once
#include "Izraz.h"

class Racunar {
protected:
	Izraz izraz;
	int trazeni_rezultat;
	std::list<int> brojevi;
	int broj_x;
	int broj_y;

public:
	Racunar();
	~Racunar();
	void racunaj_izraze();
	void ispis_na_konzolu();
	std::string int_to_str(int broj);

	Izraz get_izraz();
	int get_trazeni_rezultat();
	std::list<int> get_brojevi();
	int get_broj_x();
	int get_broj_y();

	void set_izraz(Izraz izraz);
	void set_trazeni_rezultat(int trazeni_rezultat);
	void set_brojevi(std::list<int> brojevi);
	void set_broj_x(int broj_x);
	void set_broj_y(int broj_y);
};