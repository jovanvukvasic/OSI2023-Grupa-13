#include "Korisnik.h"
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.cpp"

int main() {
    std::string ind;
    std::cout << "\n~ Aplikacija za rad sa nekretninama ~\n";
    std::cout << "\nDostupne opcije: [REGISTRACIJA], [PRIJAVA], [PRIKAZ]\n\n";

    Korisnik korisnik1;
    while (ind != "KRAJ") {
        std::cout << "\n> ";
        std::cin >> ind;
        if (ind == "PRIJAVA") {
            korisnik1.prijaviSe();
        } else if (ind == "REGISTRACIJA") {
            korisnik1.registrujSe();
        } else if (ind == "PRIKAZ") {
            std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina();
            std::cout << "\nDostupne nekretnine:\n";
            for (const auto& nekretnina : nekretnine) {
                nekretnina.prikaziInformacije();
                std::cout << "\n----------------------\n";
            }
        } else {
            if (ind != "KRAJ") std::cout << "\nTa opcija nije dostupna. Za vise opcija morate se prijaviti.\n";
        }
    }

    return 0;
}