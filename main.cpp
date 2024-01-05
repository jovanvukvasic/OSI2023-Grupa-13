#include "Korisnik.h"
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.cpp"

void prikaziNekretnineZaOdrzavanje(const std::vector<Nekretnina>& nekretnine) {
    std::cout << "\nNekretnine koje zahtevaju održavanje:\n";
    for (const auto& nekretnina : nekretnine) {
        if (nekretnina.jePotrebnoOdrzavanje()) {
            nekretnina.prikaziInformacije();
            std::cout << "-----------------------------------\n";
        }
    }
}

int main() {

    std::string ind;
    std::cout << "\n~ Aplikacija za rad sa nekretninama ~\n";
    std::cout << "\nDostupne opcije: [REGISTRACIJA], [PRIJAVA], [PRIKAZ],[ODRZAVANJE]\n\n";

    std::vector<Nekretnina> sveNekretnine = prikazDostupnihNekretnina();
    Korisnik korisnik1;
    while (ind != "KRAJ") {
        std::cout << "\n> ";
        std::cin >> ind;

        if (ind == "PRIJAVA") {
            korisnik1.prijaviSe();
        } else if (ind == "REGISTRACIJA") {
            korisnik1.registrujSe();
        } else if (ind == "PRIKAZ") {
            std::cout << "\nDostupne nekretnine:\n";
            for (const auto& nekretnina : sveNekretnine) {
                nekretnina.prikaziInformacije();
                std::cout << "\n----------------------\n";
            }
        } else if (ind == "ODRZAVANJE") {
            prikaziNekretnineZaOdrzavanje(sveNekretnine);
        } else {
            if (ind != "KRAJ") std::cout << "\nTa opcija nije dostupna. Za vise opcija morate se prijaviti.\n";
        }
    }


    return 0;
}