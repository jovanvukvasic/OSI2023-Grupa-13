#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Nekretnina.hpp"

std::vector<Nekretnina> prikazDostupnihNekretnina(const std::string& filterTip, double minCena, double maxCena, double minPovrsina, int minBrojSoba, const std::string& sortiranje, const std::string& kljucneReci) {
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
        
        // Parsiranje linije
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

        // Primena filtera i pretrage
        if ((filterTip.empty() || tip == filterTip) &&
            cena >= minCena && cena <= maxCena &&
            povrsina >= minPovrsina &&
            brojSoba >= minBrojSoba &&
            (kljucneReci.empty() || adresa.find(kljucneReci) != std::string::npos || opis.find(kljucneReci) != std::string::npos) &&
            dostupnost) {
            Nekretnina nekretnina(id, tip, adresa, povrsina, brojSoba, opis, cena, dostupnost);
            nekretnine.push_back(nekretnina);
        }
    }

    file.close();

    // Sortiranje nekretnina
    if (sortiranje == "cena") {
        std::sort(nekretnine.begin(), nekretnine.end(), [](const Nekretnina& a, const Nekretnina& b) {
            return a.getCena() < b.getCena();
        });
    } else if (sortiranje == "povrsina") {
        std::sort(nekretnine.begin(), nekretnine.end(), [](const Nekretnina& a, const Nekretnina& b) {
            return a.getPovrsina() > b.getPovrsina();
        });
    }

    return nekretnine;
}
