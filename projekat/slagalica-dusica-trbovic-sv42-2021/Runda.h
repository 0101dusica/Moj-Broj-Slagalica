#pragma once

#include "Izraz.h"

class Runda {
protected:
	int broj_runde;
	int trazeni_rezultat;
	std::list<int> brojevi;
	int broj_x;
	int broj_y;

	Izraz izraz_takmicar_a;
	int odstupanje_a;
	Izraz izraz_takmicar_b;
	int odstupanje_b;

	int pobednik_runde;

	//Kompjuter izraz;
	//int odstupanje_kompjuter;


public:
	Runda(int broj_runde);
	~Runda();
	void konzola_ispis();
	bool provera_unosa(std::string unos);

	//geteri i seteri
	int get_broj_runde();
	int get_trazeni_rezultat();
	std::list<int> get_brojevi();
	int get_broj_x();
	int get_broj_y();
	Izraz get_izraz_takmicar_a();
	int get_odstupanje_a();
	Izraz get_izraz_takmicar_b();
	int get_odstupanje_b();
	int get_pobednik_runde();

	void set_broj_runde(int broj_runde);
	void set_trazeni_rezultat(int trazeni_rezultat);
	void set_brojevi(std::list<int> brojevi);
	void set_broj_x(int broj_x);
	void set_broj_y(int broj_y);
	void set_izraz_takmicar_a(Izraz izraz_takmicar_a);
	void set_odstupanje_a(int odstupanje_a);
	void set_izraz_takmicar_b(Izraz izraz_takmicar_b);
	void set_odstupanje_b(int odstupanje_b);
	void get_pobednik_runde(int pobednik_runde);

};
