#include <iostream>
#include <stdio.h>
#include "Izraz.h"
#include "Racunar.h"

int main(int argc, char** argv) {

	std::cout << "POLUFNALE KVIZA 'SLAGALICA' - TEST PROJEKAT" << std::endl;

	std::cout << std::endl;
	Racunar racunar = Racunar();

	//test 1	
	racunar.set_brojevi({ 2,4,6,3 });
	racunar.set_broj_x(10);
	racunar.set_broj_y(25);
	racunar.set_trazeni_rezultat(634);

	racunar.ispis_na_konzolu();

	//test 2
	racunar.set_brojevi({1,6,5,3});
	racunar.set_broj_x(10);
	racunar.set_broj_y(25);
	racunar.set_trazeni_rezultat(977);

	racunar.ispis_na_konzolu();

	//test 3
	racunar.set_brojevi({ 2,4,6,3 });
	racunar.set_broj_x(10);
	racunar.set_broj_y(75);
	racunar.set_trazeni_rezultat(743);

	racunar.ispis_na_konzolu();

	//test 4
	racunar.set_brojevi({ 5,9,4,3 });
	racunar.set_broj_x(10);
	racunar.set_broj_y(15);
	racunar.set_trazeni_rezultat(823);

	racunar.ispis_na_konzolu();
	
	return 0;
}