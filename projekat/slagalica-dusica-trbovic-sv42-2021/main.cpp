#include <iostream>
#include <stdio.h>
#include "Runda.h" 
#include "Izraz.h"
#include "Racunar.h"

std::string citanje_ulazne_datoteke(std::string ulazna_datoteka, int line) {
	//ulazna datoteka je u formatu, 4 jednocifrena broja, 2 dvocifrena od toga prvi iz skupa {10,15,20,25} a drugi {25,50,75,100} i na kraju resenje koje se trazi
	std::fstream newfile;
	int line_now = 1;
	newfile.open(ulazna_datoteka, std::ios::in); //fajl se otvara u rezimu citanja
	if (newfile.is_open()) {
		std::string tp;
		while (getline(newfile, tp)) { //citaj liniju po liniju, kada dodje do linije koja je nama potrebna poziva se return 
			if (line_now == line) {
				return tp;
			}
			line_now++;
		}
		newfile.close(); //fajl se obavezno zatvara
	}
}

std::list<std::string> parse_string(std::string text, std::string delimiter) {
	std::list<std::string> new_text;
	size_t pos = 0;
	std::string token;
	while ((pos = text.find(delimiter)) != std::string::npos) {
		token = text.substr(0, pos);
		new_text.push_back(token);
		text.erase(0, pos + delimiter.length());
	}
	new_text.push_back(text);
	return new_text;
}

std::string int_to_str(int broj) {
	std::stringstream stream;
	stream << broj;
	std::string res_str = stream.str();

	return res_str;
}

std::vector<std::string> citanje_iz_fajla() //prebacujemo iscitan string u objekat tipa runda
{
	std::fstream newfile;
	std::vector<std::string> text;
	newfile.open("rezultati.txt", std::ios::in); //fajl se otvara u rezimu citanja
	if (newfile.is_open()) {
		std::string tp;
		while (getline(newfile, tp)) { //citaj liniju po liniju, kada dodje do linije koja je nama potrebna poziva se return 
			text.push_back(tp);
		}
		newfile.close(); //fajl se obavezno zatvara
	}

	return text;
}

void upis_u_fajl(Runda runda, std::list<std::string> new_podaci, Racunar racunar) //upisivanje cele jedne runde u rezultati.txt
{
	std::vector<std::string> text = citanje_iz_fajla(); //koristimo funkciju za citanje iz fajla kako bismo prepisali sve sto se do sada nalazilo u istom

	//upis je u formatu: broj_runde;dati_brojevi;trazeni_rezultat;izraz_takmicara_a;rezultat_takmicara_a;odstupanje_a;
	//					izraz_takmicara_b;rezultat_takmicara_b;odstupanje_b;pobednik_runde;resenje_kompjutera;
	std::string new_text = "RUNDA: " + int_to_str(runda.get_broj_runde()) + ";";

	for (const auto& str : new_podaci) {
		new_text = new_text + str + ";";
	}

	new_text = new_text + "PODACI O RUNDI: " + runda.get_izraz_takmicar_a().get_izraz() + ";";
	new_text = new_text + int_to_str(runda.get_izraz_takmicar_a().get_rezultat()) + ";";
	new_text = new_text + int_to_str(runda.get_odstupanje_a()) + ";";

	new_text = new_text + runda.get_izraz_takmicar_b().get_izraz() + ";";
	new_text = new_text + int_to_str(runda.get_izraz_takmicar_b().get_rezultat()) + ";";
	new_text = new_text + int_to_str(runda.get_odstupanje_b()) + ";";

	new_text = new_text + int_to_str(runda.get_pobednik_runde()) + ";";
	new_text = new_text + "Resenje_kompjutera: " + racunar.get_izraz().get_izraz() + ";" + int_to_str(racunar.get_izraz().get_rezultat());

	text.push_back(new_text);

	std::fstream newfile;
	newfile.open("rezultati.txt", std::ios::out);  // open a file to perform write operation using file object
	if (newfile.is_open()) //checking whether the file is open {
		for (const auto& str : text) {
			newfile << str + '\n'; //inserting text
		}
	newfile.close(); //close the file object

}

int main(int argc, char** argv) {

	std::cout << "Unesite naziv ulazne datoteke (u formatu naziv.txt): ";
	std::string ulazna_datoteka;
	std::cin >> ulazna_datoteka;

	std::cout << "POLUFNALE KVIZA 'SLAGALICA'" << std::endl;
	int pobednik_a = 0;
	int pobednik_b = 0;
	std::string konacan_pobednik;

	for (int i = 1; i < 7; i++) {
		std::cout << std::endl;
		Runda runda(i);
		Racunar racunar = Racunar();
		std::string podaci = citanje_ulazne_datoteke(ulazna_datoteka, i);

		std::list<std::string> new_podaci;
		std::list<int> upis_lista;
		new_podaci = parse_string(podaci, ";");
		int count = 0;
		for (const auto& str : new_podaci) {
			int x = atoi(str.c_str());
			upis_lista.push_back(x);
			if (count == 3) {
				runda.set_brojevi(upis_lista);
				racunar.set_brojevi(upis_lista);
			}
			if (count == 4) {
				runda.set_broj_x(x);
				racunar.set_broj_x(x);
			}
			if (count == 5) {
				runda.set_broj_y(x);
				racunar.set_broj_y(x);
			}
			if (count == 6) {
				runda.set_trazeni_rezultat(x);
				racunar.set_trazeni_rezultat(x);
			}
			count++;
		}

		runda.konzola_ispis();

		if (runda.get_pobednik_runde() == 1) {
			pobednik_a++;
		}
		else {
			pobednik_b++;
		}
		
		racunar.ispis_na_konzolu();
		upis_u_fajl(runda, new_podaci, racunar); //nakon svake runde upisuju se rezultati u rezultati.txt
	}

	std::cout << std::endl;
	if ((pobednik_a - pobednik_b) > 0) {
		std::cout << "POBEDNIK POLUFINALA KVIZA 'SLAGALICA' JE IGRAC 1!" << std::endl;
		std::cout << "Konacan Rezultat u Rundama je bio: " << pobednik_a << ":" << pobednik_b << std::endl;
		konacan_pobednik = "IGRAC A";
	}
	else if((pobednik_a - pobednik_b) < 0){
		std::cout << "POBEDNIK POLUFINALA KVIZA 'SLAGALICA' JE IGRAC 2!" << std::endl;
		std::cout << "Konacan Rezultat u Rundama je bio: " << pobednik_a << ":" << pobednik_b << std::endl;
		konacan_pobednik = "IGRAC B";
	}
	else {
		std::cout << "NERESENO JE!" << std::endl;
		std::cout << "Konacan Rezultat u Rundama je bio: " << pobednik_a << ":" << pobednik_b << std::endl;
		konacan_pobednik = "NERESENO JE";
	}

	std::vector<std::string> text = citanje_iz_fajla(); //koristimo funkciju za citanje iz fajla kako bismo prepisali sve sto se do sada nalazilo u istom
	std::string new_text = "KRAJ - BROJ OSVOJENIH RUNDI (IGRAC A:IGRAC B): " + int_to_str(pobednik_a) + ':' + int_to_str(pobednik_b) + '\n' + "POBEDNIK POLUFINALA JE: " + konacan_pobednik;

	text.push_back(new_text);

	std::fstream newfile;
	newfile.open("rezultati.txt", std::ios::out);  // open a file to perform write operation using file object
	if (newfile.is_open()) //checking whether the file is open {
		for (const auto& str : text) {
			newfile << str + '\n'; //inserting text
		}
	newfile.close(); //close the file object

	return 0;
}