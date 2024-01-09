#include "Korisnik.h"
#include <stdlib.h>
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.h"
#include <iostream>
#include <string>

bool uporediPoKvadraturiRASTUCE(const Nekretnina &a, const Nekretnina &b)
{
    return a.getPovrsina() < b.getPovrsina();
}

bool uporediPoKvadraturiOPADAJUCE(const Nekretnina &a, const Nekretnina &b)
{
    return a.getPovrsina() > b.getPovrsina();
}

bool uporediPoCijeniRASTUCE(const Nekretnina &a, const Nekretnina &b)
{
    return a.getCijena() < b.getCijena();
}

bool uporediPoCijeniOPADAJUCE(const Nekretnina &a, const Nekretnina &b)
{
    return a.getCijena() > b.getCijena();
}

int main()
{
    std::string ind;
    std::cout << "\n~ Aplikacija za rad sa nekretninama ~\n";
    std::cout << "\nDostupne opcije: [REGISTRACIJA], [PRIJAVA], [PRIKAZ]\n\n";

    /*TODO
        Dostupne nekretnine
    */

    Korisnik korisnik1;
    while (ind != "KRAJ")
    {
        std::cout << "\n> ";
        std::cin >> ind;
        if (ind == "PRIJAVA")
            korisnik1.prijaviSe();
        else if (ind == "REGISTRACIJA")
            korisnik1.registrujSe();
        else if (ind == "PRIKAZ")
        {

            std::string ind3;

            std::cout << "\n\nMogucnost filtera, [ALL] [F-c], [F-a], [F-t], [S-r-k], [S-r-c], [S-o-k], [S-o-c] \n";
            std::cin >> ind3;

            std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina();

            if (ind3 == "ALL")
            {

                for (Nekretnina nekretnina : nekretnine)
                {
                    nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "F-c")
            {
                double cijen1, cijen2;
                std::cout << "Unesite pocetnu i krajnju cijenu" << std::endl;
                std::cout << "Min: ";
                std::cin >> cijen1;
                std::cout << "Max: ";
                std::cin >> cijen2;
                for (Nekretnina nekretnina : nekretnine)
                {
                    double cijeena;
                    cijeena = nekretnina.getCijena();
                    if (cijeena >= cijen1 && cijeena <= cijen2)
                        nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "F-a")
            {
                std::string adresa1;
                std::cout << "\nUnesite zeljenu adresu: ";
                std::getline(std::cin, adresa1);

                for (Nekretnina nekretnina : nekretnine)
                {

                    if (nekretnina.getAdresa() == adresa1)
                        nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "F-t")
            {
                std::string tt;
                std::cout << "\nUnesite tip stana: ";
                std::cin >> tt;
                for (Nekretnina nekretnina : nekretnine)
                {

                    if (nekretnina.getTip() == tt)
                        nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "S-r-k")
            {
                std::vector<Nekretnina> nekretnine1 = nekretnine;
                std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiRASTUCE);

                for (Nekretnina nekretnina : nekretnine1)
                {
                    nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "S-o-k")
            {
                std::vector<Nekretnina> nekretnine1 = nekretnine;
                std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiOPADAJUCE);

                for (Nekretnina nekretnina : nekretnine1)
                {
                    nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "S-r-c")
            {
                std::vector<Nekretnina> nekretnine1 = nekretnine;
                std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniRASTUCE);

                for (Nekretnina nekretnina : nekretnine1)
                {
                    nekretnina.prikaziInformacije();
                }
            }

            else if (ind3 == "S-o-c")
            {
                std::vector<Nekretnina> nekretnine1 = nekretnine;
                std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniOPADAJUCE);

                for (Nekretnina nekretnina : nekretnine1)
                {
                    nekretnina.prikaziInformacije();
                }
            }

            std::cout << "\n  Za detaljne informacije selektujte nekretninu: \n";

            std::string detalj;
            std::cin >> detalj;

            int brojaaac = 0;

            for (Nekretnina nekretnina : nekretnine)
            {
                if (detalj == nekretnina.getId())
                {
                    nekretnina.prikaziInformacijeKonkretno();
                    brojaaac++;
                }
            }
            if (brojaaac == 0)
                std::cout << "Nema nekretnine sa tim identifikacionim brojem.\n";
        }

        else
        {
            if (ind != "KRAJ")
                std::cout << "\nTa opcija nije dostupna. Za vise opcija morate se prijaviti.\n";
        }
    }

    return 0;
}
