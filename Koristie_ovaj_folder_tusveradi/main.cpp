#include "Korisnik.h"
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

int main() {
    std::string ind;
   

    std::cout << "\n~ Aplikacija za rad sa nekretninama ~\n";
    std::cout << "\nDostupne opcije: [REGISTRACIJA], [PRIJAVA], [KRAJ]\n\n";
 Korisnik korisnik;
    while (ind!="KRAJ") {
        std::cout << "\n>";
        std::cin>>ind;

        if (ind == "REGISTRACIJA") {
            korisnik.registrujSe();
        } else if (ind == "PRIJAVA") {
            if (korisnik.prijaviSe()) {
                std::cout << "Uspesna prijava!\n";
                korisnik.prikazProfila();
                
                // Dodajte kod za prikaz nekretnina nakon prijave
                std::string filterTip;
                double minCena = 0;
                double maxCena = std::numeric_limits<double>::max();
                double minPovrsina = 0;
                int minBrojSoba = 0;
                std::string sortiranje;
                std::string kljucneReci;

                while (true) {
                    std::cout << "Unesite tip nekretnine za pretragu (prazno za sve): ";
                    std::getline(std::cin, filterTip);
                    std::cout << "Unesite minimalnu cijenu (0 za nema minimuma): ";
                    std::cin >> minCena;
                    std::cout << "Unesite maksimalnu cijenu (ostavite prazno za nema maksimuma): ";
                    std::cin >> maxCena;
                    std::cin.ignore();
                    std::cout << "Unesite minimalnu povrsinu (0 za nema minimuma): ";
                    std::cin >> minPovrsina;
                    std::cout << "Unesite minimalan broj soba (0 za nema minimuma): ";
                    std::cin >> minBrojSoba;
                    std::cin.ignore();
                    std::cout << "Unesite kriterijum za sortiranje (cena/povrsina): ";
                    std::getline(std::cin, sortiranje);
                    std::cout << "Unesite kljucne rijei za pretragu: ";
                    std::getline(std::cin, kljucneReci);

                    std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina(filterTip, minCena, maxCena, minPovrsina, minBrojSoba, sortiranje, kljucneReci);

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
                            break;
                        } else if (izbor > 0 && izbor <= static_cast<int>(nekretnine.size())) {
                            const Nekretnina& odabranaNekretnina = nekretnine[izbor - 1];
                            odabranaNekretnina.prikaziInformacije();
                        } else {
                            std::cout << "Nevazeci unos. Molimo pokusajte ponovo." << std::endl;
                        }
                    }

                    std::cout << "Zelite li izvrsiti novu pretragu? (DA/NE): ";
                    std::string izlaz;
                    std::cin >> izlaz;
                    std::cin.ignore();

                    if (izlaz != "DA") {
                        std::cout << "Izlaz iz aplikacije." << std::endl;
                        break;
                    }
                }

                break; // Izlaz iz glavne petlje nakon prijave i prikaza nekretnina
            } else {
                std::cout << "Pogresno korisnicko ime ili lozinka. Pokusajte ponovo.\n";
            }
        } else if (ind == "IZLAZ") {
            std::cout << "Izlaz iz aplikacije." << std::endl;
            break;
        } else {
            std::cout << "Nepoznata opcija. Molimo unesite [REGISTRACIJA], [PRIJAVA], ili [IZLAZ].\n";
        }
    }

    return 0;
}
