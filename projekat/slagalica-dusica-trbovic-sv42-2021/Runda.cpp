#include "Runda.h"

Runda::Runda(int broj_runde)
{
	this->broj_runde = broj_runde;
	this->trazeni_rezultat = 0;
	this->broj_x = 0;
	this->broj_y = 0;
	this->izraz_takmicar_a = Izraz();
	this->odstupanje_a = -1;
	this->izraz_takmicar_b = Izraz();
	this->odstupanje_b = -1;
	this->pobednik_runde = 0;
}

Runda::~Runda()
{
}

void Runda::konzola_ispis(){

	//std::list<int> brojevi_x = { 10,15,20,25 };
	//std::list<int> brojevi_y = { 25,50,75,100 };
	std::cout << "RUNDA BROJ " << this->broj_runde << std::endl;

	//this->trazeni_rezultat = rand() % 999 + 1; //rezultat koji korisnici moraju da pronadju
	std::cout << "Rezultat koji je potrebno naci: " << this->trazeni_rezultat << std::endl << "Ponudjeni Brojevi: ";

	//for (int j = 0; j < 4; j++) {
		//int broj = rand() % 9 + 1; //raspon brojeva je od 1 do 9
		//this->brojevi.push_back(broj); //ispis prva cetiri jednocifrena broja
		//std::cout << broj << " ";
	//}

	for (auto it = this->brojevi.begin(); it != this->brojevi.end(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << "     ";

	//auto it_x = std::next(brojevi_x.begin(), rand() % 4);
	//auto it_y = std::next(brojevi_y.begin(), rand() % 4);

	//this->broj_x = *it_x; //peti broj koji se ispisuje na ekran
	std::cout << this->broj_x << " ";
	//this->broj_y = *it_y; //sesti broj koji se ispisuje na ekran
	std::cout << this->broj_y << " " << std::endl;

	std::cout << "Dozvoljene Operacije su: + - * / ()" << std::endl;

	if (this->broj_runde % 2 == 1) {
		std::cout << "Prvi igrac je na potezu! Unesite vas izraz: " << std::endl << std::endl;
		bool p = false;
		std::string unos_a;

		while (p == false) {
			std::cin >> unos_a;
			p = provera_unosa(unos_a);
			if (p == false) {
				std::cout << "Unos nije odgovarajuci! Pokusajte ponovo!" << std::endl;
			}
		}

		Izraz izraz_a(unos_a);
		izraz_a.set_rezultat();;
		this->set_izraz_takmicar_a(izraz_a);
		std::cout << "Rezultat izraza koji ste uneli je: " << this->izraz_takmicar_a.get_rezultat() << std::endl;
		this->odstupanje_a = abs(this->trazeni_rezultat - this->izraz_takmicar_a.get_rezultat());
		if (odstupanje_a != 0) {
			std::cout << "Odstupanje od trazenog rezultata je: " << this->odstupanje_a << ". Na redu je drugi igrac! " << std::endl;
			std::cout << "Drugi igrac je na potezu! Unesite vas izraz: " << std::endl << std::endl;
			std::string unos_b;
			bool p = false;
			while (p == false) {
				std::cin >> unos_b;
				p = provera_unosa(unos_b);
				if (p == false) {
					std::cout << "Unos nije odgovarajuci! Pokusajte ponovo!" << std::endl;
				}
			}
			Izraz izraz_b(unos_b);
			izraz_b.set_rezultat();;
			this->set_izraz_takmicar_b(izraz_b);
			std::cout << "Rezultat izraza koji ste uneli je: " << this->izraz_takmicar_b.get_rezultat() << std::endl;
			this->odstupanje_b = abs(this->trazeni_rezultat - this->izraz_takmicar_b.get_rezultat());
			if (odstupanje_b != 0) {
				std::cout << "Odstupanje od trazenog rezultata je: " << this->odstupanje_b << std::endl;
				if ((this->odstupanje_a - this->odstupanje_b) <= 0) {
					std::cout << "Pobednik u rundi " << this->broj_runde << " je Igrac 1!" << std::endl;
					if ((this->odstupanje_a - this->odstupanje_b) < 0) {
						std::cout<< "Njegovo odstupanje od trazenog rezultata je manje!" << std::endl;
					}
					else {
						std::cout<<"Odstupanja su jednaka ali je ovo runda koja pripada igracu 1!" << std::endl;
					}
					this->pobednik_runde = 1;
				}
				else {
					std::cout << "Pobednik u rundi " << this->broj_runde << " je Igrac 2! Njegovo odstupanje od trazenog rezultata je manje!" << std::endl;
					this->pobednik_runde = 2;
				}
			}
			else {
				std::cout << "Cestitamo. Pronasli ste tacno resenje! Pobedili ste u rundi " << this->broj_runde << std::endl;
				this->pobednik_runde = 2;
				this->odstupanje_a = abs(this->trazeni_rezultat - this->izraz_takmicar_a.get_rezultat());
			}
		}
		else {
			std::cout << "Cestitamo. Pronasli ste tacno resenje! Pobedili ste u rundi " << this->broj_runde << std::endl;
			this->pobednik_runde = 1;
			this->odstupanje_b = abs(this->trazeni_rezultat - this->izraz_takmicar_b.get_rezultat());
		}
	}
	else {
		std::cout << "Drugi igrac je na potezu! Unesite vas izraz: " << std::endl << std::endl;
		std::string unos_b;
		bool p = false;
		while (p == false) {
			std::cin >> unos_b;
			p = provera_unosa(unos_b);
			if (p == false) {
				std::cout << "Unos nije odgovarajuci! Pokusajte ponovo!" << std::endl;
			}
		}
		Izraz izraz_b(unos_b);
		izraz_b.set_rezultat();;
		this->set_izraz_takmicar_b(izraz_b);
		std::cout << "Rezultat izraza koji ste uneli je: " << this->izraz_takmicar_b.get_rezultat() << std::endl;
		this->odstupanje_b = abs(this->trazeni_rezultat - this->izraz_takmicar_b.get_rezultat());
		if (odstupanje_b != 0) {
			std::cout << "Odstupanje od trazenog rezultata je: " << this->odstupanje_b << ". Na redu je prvi igrac! " << std::endl;
			std::cout << "Prvi igrac je na potezu! Unesite vas izraz: " << std::endl << std::endl;
			std::string unos_a;
			bool p = false;
			while (p == false) {
				std::cin >> unos_a;
				p = provera_unosa(unos_a);
				if (p == false) {
					std::cout << "Unos nije odgovarajuci! Pokusajte ponovo!" << std::endl;
				}
			}
			Izraz izraz_a(unos_a);
			izraz_a.set_rezultat();
			this->set_izraz_takmicar_a(izraz_a);
			std::cout << "Rezultat izraza koji ste uneli je: " << this->izraz_takmicar_a.get_rezultat() << std::endl;
			this->odstupanje_a = abs(this->trazeni_rezultat - this->izraz_takmicar_a.get_rezultat());
			if (odstupanje_a != 0) {
				std::cout << "Odstupanje od trazenog rezultata je: " << this->odstupanje_a << ". Na redu je drugi igrac! " << std::endl;
				if ((this->odstupanje_a - this->odstupanje_b) < 0) {
					std::cout << "Pobednik u rundi " << this->broj_runde << " je Igrac 1! Njegovo odstupanje od trazenog rezultata je manje!" << std::endl;
					this->pobednik_runde = 1;
				}
				else {
					std::cout << "Pobednik u rundi " << this->broj_runde << " je Igrac 2! " << std::endl;
					this->pobednik_runde = 2;
					if ((this->odstupanje_a - this->odstupanje_b) > 0) {
						std::cout << "Njegovo odstupanje od trazenog rezultata je manje!" << std::endl;
					}
					else {
						std::cout << "Odstupanja su jednaka ali je ovo runda koja pripada igracu 2!" << std::endl;
					}
				}
			}
			else {
				std::cout << "Cestitamo. Pronasli ste tacno resenje! Pobedili ste u rundi " << this->broj_runde << std::endl;
				this->pobednik_runde = 1;
				this->odstupanje_b = abs(this->trazeni_rezultat - this->izraz_takmicar_b.get_rezultat());
			}
		}
		else {
			std::cout << "Cestitamo. Pronasli ste tacno resenje! Pobedili ste u rundi " << this->broj_runde << std::endl;
			this->pobednik_runde = 2;
			this->odstupanje_a = abs(this->trazeni_rezultat - this->izraz_takmicar_a.get_rezultat());
		}
	}
}

bool Runda::provera_unosa(std::string unos)
{
	std::list<int> mogucnosti = {this->broj_x, this->broj_y};
	for (auto it = this->brojevi.begin(); it != this->brojevi.end(); ++it) {
		mogucnosti.push_back(*it);
	}

	std::vector<std::string> mogucnosti_string = {};

	for (auto it = mogucnosti.begin(); it != mogucnosti.end(); ++it) {
		std::stringstream stream;
		stream << *it;
		std::string res_str = stream.str();
		mogucnosti_string.push_back(res_str);
	}

	mogucnosti_string.push_back("+");
	mogucnosti_string.push_back("-");
	mogucnosti_string.push_back("*");
	mogucnosti_string.push_back("/");

	Izraz iz(unos);
	std::string unos_postfix = iz.convert_to_postfix();
	//std::cout << "ovo je postfix: " << unos_postfix << std::endl;

	std::string space_delimiter = " ";
	std::list<std::string> new_text;
	size_t pos = 0;
	std::string token;
	int c = 0;
	while ((pos = unos_postfix.find(space_delimiter)) != std::string::npos) {
		token = unos_postfix.substr(0, pos);
		if (c != 0) {
			new_text.push_back(token);
		}
		c++;
		unos_postfix.erase(0, pos + space_delimiter.length());
	}
	new_text.push_back(unos_postfix);

	int str_size = new_text.size();
	for (const auto& str : new_text) {
		//std::cout << "proveravam trenutno " << str << " a size je: " <<str_size << std::endl;
		std::vector<std::string> iskoriscene_vrednosti = {};
		int count = 0;
		if (str != " ") {
			for (const auto& str_mo : mogucnosti_string) {
				//std::cout << "usao sam za mogucnosti " << str_mo << std::endl;
				if (str_mo == str) {
					int count_ponavljanje = 0;
					for (const auto& str_po : iskoriscene_vrednosti) {
						//std::cout << "tu sam gde su ponavljanja" << str_po << std::endl;
						if (str_po == str) {
							//std::cout << "PONAVLJANJE" << std::endl;
							count_ponavljanje++;
						}
					}
					//proveravamo da li se neka od cifara koje su unete koristila vise puta, naravno izbegavamo proveru za vise puta koriscene operande, to je dozvoljeno
					if (str_mo != "+" && str_mo != "-" && str_mo != "*" && str_mo != "/") {
						//std::cout << "prosli smo znakove" << std::endl;
						if (count_ponavljanje == 0) {
							//std::cout << "nije bilo ponavljanja wow" << std::endl;
							iskoriscene_vrednosti.push_back(str_mo);
							count++;
						}
					}
					else {
						count++;
					}

				}
			}
			if (count == 0) {
				//std::cout << "UPIS NIJE DOBAR!" << std::endl;
				return false;
			}
		}
	}

	//std::cout << "UPIS JE DOBAR! " << std::endl;
	return true;
}










//geteri i seteri

int Runda::get_broj_runde()
{
	return this->broj_runde;
}

int Runda::get_trazeni_rezultat()
{
	return this->trazeni_rezultat;
}

std::list<int> Runda::get_brojevi()
{
	return this->brojevi;
}

int Runda::get_broj_x()
{
	return this->broj_x;
}

int Runda::get_broj_y()
{
	return this->broj_y;
}

Izraz Runda::get_izraz_takmicar_a()
{
	return this->izraz_takmicar_a;
}

int Runda::get_odstupanje_a()
{
	return this->odstupanje_a;
}

Izraz Runda::get_izraz_takmicar_b()
{
	return this->izraz_takmicar_b;
}

int Runda::get_odstupanje_b()
{
	return this->odstupanje_b;
}

int Runda::get_pobednik_runde()
{
	return this->pobednik_runde;
}

void Runda::set_broj_runde(int broj_runde)
{
	this->broj_runde = broj_runde;
}

void Runda::set_trazeni_rezultat(int trazeni_rezultat)
{
	this->trazeni_rezultat = trazeni_rezultat;
}

void Runda::set_brojevi(std::list<int> brojevi)
{
	this->brojevi = brojevi;
}

void Runda::set_broj_x(int broj_x)
{
	this->broj_x = broj_x;
}

void Runda::set_broj_y(int broj_y)
{
	this->broj_y = broj_y;
}

void Runda::set_izraz_takmicar_a(Izraz izraz_takmicar_a)
{
	this->izraz_takmicar_a = izraz_takmicar_a;
}

void Runda::set_odstupanje_a(int odstupanje_a)
{
	this->odstupanje_a = odstupanje_a;
}

void Runda::set_izraz_takmicar_b(Izraz izraz_takmicar_b)
{
	this->izraz_takmicar_b = izraz_takmicar_b;
}

void Runda::set_odstupanje_b(int odstupanje_b)
{
	this->odstupanje_b = odstupanje_b;
}

void Runda::get_pobednik_runde(int pobednik_runde)
{
	this->pobednik_runde = pobednik_runde;
}
