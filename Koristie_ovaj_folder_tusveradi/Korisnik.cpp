#include "Korisnik.h"
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <conio.h>
#include <limits>

bool Korisnik::prijaviSe() {
    std::cout << "~ Prijava na sistem ~\n";
    std::cout << "Korisnicko ime: ";
    std::cin >> korisnickoIme;

    std::string Sifra;
    std::cout << "Lozinka: ";
    char karakter;

    while (true) {
        karakter = getch();

        if (karakter == 13) { // Enter key
            break;
        }

        if (karakter == 8 && !Sifra.empty()) { // Backspace key
            std::cout << "\b \b";
            Sifra.pop_back();
        } else if (karakter != 8) {
            Sifra.push_back(karakter);
            std::cout << '*';
        }
    }

    std::ifstream file("nalozi.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string pr, ki, si, i, p, bt, ea;

        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea)) {
            continue;
        }

        if (ki == korisnickoIme && si == Sifra) {
            file.close();

            std::cout << "\n\nUspesno ste se prijavili!\n\n\n";
            prikazProfila();

            if(pr == "1") {
                std::cout << "\nDostupne operacije vlasniku: [PRIKAZ], [SLANJE], ....\n";
            } else if(pr == "2") {
                std::cout << "\nDostupne operacije kupcu: [PRIKAZ], [APLICIRANJE], ....\n";
            } else if(pr == "3") {
                std::cout << "\nDostupne operacije iznajmljivacu: [PRIKAZ], [APLICIRANJE], ....\n";
            } else if(pr == "4") {
                std::cout << "\nDostupne operacije radniku agencije: [PRIKAZ], [REGISTROVANJE], [GENERISANJE], ....\n";
            } else if(pr == "5") {
                std::cout << "\nDostupne operacije odrzavatelju: [PRIKAZ], [ZADACI], [AZADATAK], ....\n";
            }

            std::string ind2;
            while(ind2 != "ODJAVA") {
                std::cout << "\n> ";
                std::cin >> ind2;

                if(ind2 == "PRIKAZ") {
                    std::cout << "\nTrenutno dostupne nekretnine.\n";
                    // Ovde implementirati logiku za prikaz nekretnina
        std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina("", 0, std::numeric_limits<double>::max(), 0, 0, "", "");
        
        if (nekretnine.empty()) {
            std::cout << "Nema nekretnina koje odgovaraju zadatim kriterijumima." << std::endl;
        } else {
            for (size_t i = 0; i < nekretnine.size(); ++i) {
                std::cout << i + 1 << ". " << nekretnine[i].getOpis() << " - " << nekretnine[i].getAdresa() << std::endl;
            }

            std::cout << "Unesite broj nekretnine za više detalja ili 0 za izlaz: ";
            int izbor;
            std::cin >> izbor;

            if (izbor == 0) {
                std::cout << "Izlaz iz aplikacije." << std::endl;
            } else if (izbor > 0 && izbor <= static_cast<int>(nekretnine.size())) {
                const Nekretnina& odabranaNekretnina = nekretnine[izbor - 1];
                odabranaNekretnina.prikaziInformacije();
            } else {
                std::cout << "Nevazeci unos. Molimo pokusajte ponovo." << std::endl;
            }
        }
                    
                } else if(ind2 == "PRIJAVA") {
                    std::cout << "\nTrenutno ste vec prijavljeni.\n";
                } else if(ind2 != "ODJAVA") {
                    std::cout << "\nTa opcija nije dostupna.\n";
                }
            }

            return true;
        } else if (ki == korisnickoIme) {
            file.close();
            std::cout << "\nPogresna lozinka. Pokusajte ponovo.\n";
            return false;
        }
    }

    file.close();
    std::cout << "\nKorisnicko ime nije pronadjeno. Molimo vas da se registrujete.\n";
    return false;
}
