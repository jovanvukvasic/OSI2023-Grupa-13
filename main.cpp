#include "Korisnik.h"
#include <stdlib.h>
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.h"
#include <iostream>
#include <string>



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
            korisnik1.prikaziNekretnine();
        else
        {
            if (ind != "KRAJ")
                std::cout << "\nTa opcija nije dostupna. Za vise opcija morate se prijaviti.\n";
        }
    }

    return 0;
}
