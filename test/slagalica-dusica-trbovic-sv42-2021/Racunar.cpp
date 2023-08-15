#include "Racunar.h"

Racunar::Racunar()
{
    this->izraz = Izraz();
    this->broj_x = 0;
    this->broj_y = 0;
    this->trazeni_rezultat = 0;
}

Racunar::~Racunar()
{
}

void Racunar::racunaj_izraze()
{
    int target_number = this->trazeni_rezultat;//rezultat koji racunar treba da pronadje
    int min_razlika = 10000;

    //formiramo prvi niz koji se sastoji od ponudjenih brojeva
    std::vector<std::string> operations = { "+", "-", "*", "/" };
    std::vector<int> numbers;

    std::vector<std::string> izrazi_dva_str;
    std::vector<std::vector<int>> izrazi_dva;
    std::vector<std::string> izrazi_tri_str;
    std::vector<std::vector<int>> izrazi_tri;
    std::vector<std::string> izrazi_cetiri_str;
    std::vector<std::vector<int>> izrazi_cetiri;
    std::vector<std::string> izrazi_pet_str;
    std::vector<std::vector<int>> izrazi_pet;
    std::vector<std::string> izrazi_sest_str;
    std::vector<std::vector<int>> izrazi_sest;

    int count = 0;
    for (const auto& number : this->brojevi) {
        numbers.push_back(number);
    }
    numbers.push_back(this->broj_x);
    numbers.push_back(this->broj_y);

    //sastavljamo izraze po postfixnoj notaciji -> prvi_broj drugi_broj operacija_jedan, izraze samo sa dva operanda za sada
    for (int i = 0; i < numbers.size(); i++) {
        std::vector<bool> is_number_used = { 0,0,0,0,0,0 }; //pamtimo koji se broj do sada korisio
        is_number_used[i] = 1;
        for (int k = 1; k < numbers.size(); k++) {
            if (is_number_used[k] == 0) {
                is_number_used[k] = 1;
                for (int j = 0; j < 4; j++) {
                    std::string expression = int_to_str(numbers.at(i)) + " " + int_to_str(numbers.at(k)) + " " + operations.at(j);
                    Izraz izraz = Izraz();
                    izraz.set_posfix(expression);
                    izraz.set_izraz(izraz.convert_to_infix());
                    std::string isp = izraz.convert_to_infix();
                    izraz.izracunaj_rezultat();
                    if (izraz.get_rezultat() > 0) {
                        if (operations.at(j) == "/" && (numbers.at(i) % numbers.at(k)) == 0) {
                            std::vector<int> upis = { i, k, j, izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                            izrazi_dva.push_back(upis);
                            izrazi_dva_str.push_back(expression);
                        }
                        if (operations.at(j) != "/") {
                            std::vector<int> upis = { i, k, j, izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                            izrazi_dva.push_back(upis);
                            izrazi_dva_str.push_back(expression);
                        }
                    }

                    if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                        this->izraz.set_izraz(izraz.convert_to_infix());
                        this->izraz.set_rezultat();
                        min_razlika = abs(target_number - izraz.get_rezultat());

                        if (min_razlika == 0) {
                            return;
                        }
                    }
                }
            }
            is_number_used[k] = 0;
        }
    }

    //sastavljamo izraze sa po tri operanda, prvi slucaj: broj izraz operacija, drugi slucaj: izraz broj operacija
    for (int i = 0; i < numbers.size(); i++) {
        std::vector<bool> is_number_used = { 0,0,0,0,0,0 }; //pamtimo koji se broj do sada korisio
        for (int k = 0; k < izrazi_dva.size(); k++) {

            if (i != izrazi_dva.at(k).at(0) && i != izrazi_dva.at(k).at(1)) {
                //std::cout << "brojevi su: " << numbers.at(i) << " " << numbers.at(izrazi_dva.at(k).at(0)) << " " << numbers.at(izrazi_dva.at(k).at(1)) << std::endl;

                for (int j = 0; j < 4; j++) {
                    for (int m = 0; m < 2; m++) {
                        if (m == 0) {
                            std::string expression = int_to_str(numbers.at(i)) + " " + izrazi_dva_str.at(k) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(numbers.at(i)) + " " + int_to_str(izrazi_dva.at(k).at(3)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (numbers.at(i) % izrazi_dva.at(k).at(3)) == 0) {
                                    std::vector<int> upis = { i, izrazi_dva.at(k).at(0), izrazi_dva.at(k).at(1), j, izrazi_dva.at(k).at(2), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_tri.push_back(upis);
                                    izrazi_tri_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_dva.at(k).at(0), izrazi_dva.at(k).at(1), j, izrazi_dva.at(k).at(2), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_tri.push_back(upis);
                                    izrazi_tri_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                        else {
                            std::string expression = izrazi_dva_str.at(k) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(izrazi_dva.at(k).at(3)) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza pod dva: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (izrazi_dva.at(k).at(3) % numbers.at(i)) == 0) {
                                    std::vector<int> upis = { i, izrazi_dva.at(k).at(0), izrazi_dva.at(k).at(1), j, izrazi_dva.at(k).at(2), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_tri.push_back(upis);
                                    izrazi_tri_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_dva.at(k).at(0), izrazi_dva.at(k).at(1), j, izrazi_dva.at(k).at(2), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_tri.push_back(upis);
                                    izrazi_tri_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                    }

                }
            }

        }
    }

    //sastavljamo izraze sa po cetiri operanda, prvi slucaj: broj izraz operacija, drugi slucaj: izraz broj operacija
    for (int i = 0; i < numbers.size(); i++) {
        std::vector<bool> is_number_used = { 0,0,0,0,0,0 }; //pamtimo koji se broj do sada korisio
        for (int k = 0; k < izrazi_tri.size(); k++) {
            if (i != izrazi_tri.at(k).at(0) && i != izrazi_tri.at(k).at(1) && i != izrazi_tri.at(k).at(2)) {
                //std::cout << "brojevi su: " << numbers.at(i) << " " << numbers.at(izrazi_tri.at(k).at(0)) << " " << numbers.at(izrazi_tri.at(k).at(1)) << " " << numbers.at(izrazi_tri.at(k).at(2)) << std::endl;

                for (int j = 0; j < 4; j++) {
                    for (int m = 0; m < 2; m++) {
                        if (m == 0) {
                            std::string expression = int_to_str(numbers.at(i)) + " " + izrazi_tri_str.at(k) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(numbers.at(i)) + " " + int_to_str(izrazi_tri.at(k).at(5)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (numbers.at(i) % izrazi_tri.at(k).at(5)) == 0) {
                                    std::vector<int> upis = { i, izrazi_tri.at(k).at(0), izrazi_tri.at(k).at(1), izrazi_tri.at(k).at(2), j, izrazi_tri.at(k).at(3), izrazi_tri.at(k).at(4), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_cetiri.push_back(upis);
                                    izrazi_cetiri_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_tri.at(k).at(0), izrazi_tri.at(k).at(1), izrazi_tri.at(k).at(2), j, izrazi_tri.at(k).at(3), izrazi_tri.at(k).at(4), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_cetiri.push_back(upis);
                                    izrazi_cetiri_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {

                                    return;
                                }
                            }
                        }
                        else {
                            std::string expression = izrazi_tri_str.at(k) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(izrazi_tri.at(k).at(5)) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza pod dva: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (izrazi_tri.at(k).at(5) % numbers.at(i)) == 0) {
                                    std::vector<int> upis = { i, izrazi_tri.at(k).at(0), izrazi_tri.at(k).at(1), izrazi_tri.at(k).at(2), j, izrazi_tri.at(k).at(3), izrazi_tri.at(k).at(4), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_cetiri.push_back(upis);
                                    izrazi_cetiri_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_tri.at(k).at(0), izrazi_tri.at(k).at(1), izrazi_tri.at(k).at(2), j, izrazi_tri.at(k).at(3), izrazi_tri.at(k).at(4), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_cetiri.push_back(upis);
                                    izrazi_cetiri_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    //sastavljamo izraze sa po pet operanda, prvi slucaj: broj izraz operacija, drugi slucaj: izraz broj operacija
    for (int i = 0; i < numbers.size(); i++) {
        std::vector<bool> is_number_used = { 0,0,0,0,0,0 }; //pamtimo koji se broj do sada korisio
        for (int k = 0; k < izrazi_cetiri.size(); k++) {
            if (i != izrazi_cetiri.at(k).at(0) && i != izrazi_cetiri.at(k).at(1) && i != izrazi_cetiri.at(k).at(2) && i != izrazi_cetiri.at(k).at(3)) {
                //std::cout << "brojevi su: " << numbers.at(i) << " " << numbers.at(izrazi_tri.at(k).at(0)) << " " << numbers.at(izrazi_tri.at(k).at(1)) << " " << numbers.at(izrazi_tri.at(k).at(2)) << std::endl;

                for (int j = 0; j < 4; j++) {
                    for (int m = 0; m < 2; m++) {
                        if (m == 0) {
                            std::string expression = int_to_str(numbers.at(i)) + " " + izrazi_cetiri_str.at(k) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(numbers.at(i)) + " " + int_to_str(izrazi_cetiri.at(k).at(7)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (numbers.at(i) % izrazi_cetiri.at(k).at(7)) == 0) {
                                    std::vector<int> upis = { i, izrazi_cetiri.at(k).at(0), izrazi_cetiri.at(k).at(1), izrazi_cetiri.at(k).at(2), izrazi_cetiri.at(k).at(3), j, izrazi_cetiri.at(k).at(4), izrazi_cetiri.at(k).at(5), izrazi_cetiri.at(k).at(6), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_pet.push_back(upis);
                                    izrazi_pet_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_cetiri.at(k).at(0), izrazi_cetiri.at(k).at(1), izrazi_cetiri.at(k).at(2), izrazi_cetiri.at(k).at(3), j, izrazi_cetiri.at(k).at(4), izrazi_cetiri.at(k).at(5), izrazi_cetiri.at(k).at(6), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_pet.push_back(upis);
                                    izrazi_pet_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                        else {
                            std::string expression = izrazi_cetiri_str.at(k) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(izrazi_cetiri.at(k).at(7)) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            //std::cout << "ispis izraza pod dva: " << za_racun << std::endl;
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (izrazi_cetiri.at(k).at(7) % numbers.at(i)) == 0) {
                                    std::vector<int> upis = { i, izrazi_cetiri.at(k).at(0), izrazi_cetiri.at(k).at(1), izrazi_cetiri.at(k).at(2), izrazi_cetiri.at(k).at(3), j, izrazi_cetiri.at(k).at(4), izrazi_cetiri.at(k).at(5), izrazi_cetiri.at(k).at(6), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_pet.push_back(upis);
                                    izrazi_pet_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_cetiri.at(k).at(0), izrazi_cetiri.at(k).at(1), izrazi_cetiri.at(k).at(2), izrazi_cetiri.at(k).at(3), j, izrazi_cetiri.at(k).at(4), izrazi_cetiri.at(k).at(5), izrazi_cetiri.at(k).at(6), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_pet.push_back(upis);
                                    izrazi_pet_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    //sastavljamo izraze sa po sest operanda, prvi slucaj: broj izraz operacija, drugi slucaj: izraz broj operacija
    for (int i = 0; i < numbers.size(); i++) {
        std::vector<bool> is_number_used = { 0,0,0,0,0,0 }; //pamtimo koji se broj do sada korisio
        for (int k = 0; k < izrazi_pet.size(); k++) {
            if (i != izrazi_pet.at(k).at(0) && i != izrazi_pet.at(k).at(1) && i != izrazi_pet.at(k).at(2) && i != izrazi_pet.at(k).at(3) && i != izrazi_pet.at(k).at(4)) {
                for (int j = 0; j < 4; j++) {
                    for (int m = 0; m < 2; m++) {
                        if (m == 0) {
                            std::string expression = int_to_str(numbers.at(i)) + " " + izrazi_pet_str.at(k) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(numbers.at(i)) + " " + int_to_str(izrazi_pet.at(k).at(9)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (numbers.at(i) % izrazi_pet.at(k).at(9)) == 0) {
                                    std::vector<int> upis = { i, izrazi_pet.at(k).at(0), izrazi_pet.at(k).at(1), izrazi_pet.at(k).at(2), izrazi_pet.at(k).at(3),izrazi_pet.at(k).at(4), j, izrazi_pet.at(k).at(5), izrazi_pet.at(k).at(6), izrazi_pet.at(k).at(7),izrazi_pet.at(k).at(8), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_sest.push_back(upis);
                                    izrazi_sest_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_pet.at(k).at(0), izrazi_pet.at(k).at(1), izrazi_pet.at(k).at(2), izrazi_pet.at(k).at(3),izrazi_pet.at(k).at(4), j, izrazi_pet.at(k).at(5), izrazi_pet.at(k).at(6), izrazi_pet.at(k).at(7),izrazi_pet.at(k).at(8), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_sest.push_back(upis);
                                    izrazi_sest_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {
                                std::cout << expression << std::endl;
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());

                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                        else {
                            std::string expression = izrazi_pet_str.at(k) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            Izraz izraz = Izraz();
                            std::string za_racun = int_to_str(izrazi_pet.at(k).at(9)) + " " + int_to_str(numbers.at(i)) + " " + operations.at(j);
                            izraz.set_posfix(za_racun);
                            izraz.set_izraz(izraz.convert_to_infix());
                            std::string isp = izraz.convert_to_infix();
                            izraz.izracunaj_rezultat();
                            if (izraz.get_rezultat() > 0) {
                                if (operations.at(j) == "/" && (izrazi_pet.at(k).at(9) % numbers.at(i)) == 0) {
                                    std::vector<int> upis = { i, izrazi_pet.at(k).at(0), izrazi_pet.at(k).at(1), izrazi_pet.at(k).at(2), izrazi_pet.at(k).at(3),izrazi_pet.at(k).at(4), j, izrazi_pet.at(k).at(5), izrazi_pet.at(k).at(6), izrazi_pet.at(k).at(7),izrazi_pet.at(k).at(8), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_sest.push_back(upis);
                                    izrazi_sest_str.push_back(expression);
                                }
                                if (operations.at(j) != "/") {
                                    std::vector<int> upis = { i, izrazi_pet.at(k).at(0), izrazi_pet.at(k).at(1), izrazi_pet.at(k).at(2), izrazi_pet.at(k).at(3),izrazi_pet.at(k).at(4), j, izrazi_pet.at(k).at(5), izrazi_pet.at(k).at(6), izrazi_pet.at(k).at(7),izrazi_pet.at(k).at(8), izraz.get_rezultat() };//pamtimo dva iskoriscena broja, operaciju, i vrednost izraza
                                    izrazi_sest.push_back(upis);
                                    izrazi_sest_str.push_back(expression);
                                }
                            }

                            if (abs(target_number - izraz.get_rezultat()) < min_razlika) {

                                std::cout << expression << std::endl;
                                izraz.set_posfix(expression);
                                this->izraz.set_izraz(izraz.convert_to_infix());
                                this->izraz.set_rezultat();
                                min_razlika = abs(target_number - izraz.get_rezultat());
                                if (min_razlika == 0) {
                                    return;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

}

void Racunar::ispis_na_konzolu()
{
    this->racunaj_izraze();
    std::cout << std::endl;
    std::cout << "NASE RESENJE(racunar): " << std::endl;
    if (abs(this->izraz.get_rezultat() - this->trazeni_rezultat) != 0) {
        std::cout << "Ne postoji izraz koji odgovara trazenom resenju! Najpriblizniji izraz je: "
            << this->izraz.get_izraz() << "=" << this->izraz.get_rezultat() << std::endl;
    }
    else {
        std::cout << "Izraz: " << this->izraz.get_izraz() << "=" << this->izraz.get_rezultat() << std::endl;
    }
}

std::string Racunar::int_to_str(int broj)
{
    std::stringstream stream;
    stream << broj;
    std::string res_str = stream.str();

    return res_str;
}



//geteri i seteri
Izraz Racunar::get_izraz()
{
    return this->izraz;
}

int Racunar::get_trazeni_rezultat()
{
    return this->trazeni_rezultat;
}

std::list<int> Racunar::get_brojevi()
{
    return this->brojevi;
}

int Racunar::get_broj_x()
{
    return this->broj_x;
}

int Racunar::get_broj_y()
{
    return this->broj_y;
}

void Racunar::set_izraz(Izraz izraz)
{
    this->izraz = izraz;
}

void Racunar::set_trazeni_rezultat(int trazeni_rezultat)
{
    this->trazeni_rezultat = trazeni_rezultat;
}

void Racunar::set_brojevi(std::list<int> brojevi)
{
    this->brojevi = brojevi;
}

void Racunar::set_broj_x(int broj_x)
{
    this->broj_x = broj_x;
}

void Racunar::set_broj_y(int broj_y)
{
    this->broj_y = broj_y;
}
