#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Nekretnina.hpp"

std::vector<Nekretnina> prikazDostupnihNekretnina() {
    std::vector<Nekretnina> nekretnine;
    std::ifstream file("nekretnine.txt");

    if (!file.is_open()) {
        std::cerr << "Datoteka se ne moze otvoriti 'nekretnine.txt'." << std::endl;
        return nekretnine;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, tip, adresa, brojSobaStr, opis, dostupnostStr;
        double povrsina, cena;
        int brojSoba;
        bool dostupnost;
        
        // Pretpostavka je da su vrijednosti u datoteci razdvojene zarezima
        std::getline(iss, id, ',');
        std::getline(iss, tip, ',');
        std::getline(iss, adresa, ',');
        iss >> povrsina;
        iss.ignore(); 
        iss >> brojSoba;
        iss.ignore();
        std::getline(iss, opis, ',');
        iss >> cena;
        iss.ignore();
        std::getline(iss, dostupnostStr, ',');
        dostupnost = dostupnostStr == "1";

        if (dostupnost) { 
            Nekretnina nekretnina(id, tip, adresa, povrsina, brojSoba, opis, cena, dostupnost);
            nekretnine.push_back(nekretnina);
        }
    }

    file.close();
    return nekretnine;
}
