#include "Korisnik.h"
#include "Nekretnina.hpp"
#include "prikazDostupnihNekretnina.h"
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

void Korisnik::prikaziNekretnine()
{
    std::string ind3;

    std::cout << "\n\nMogucnost filtera:\n  [FILTER-CIJENA],\n  [FILTER-ADRESA],\n  [FILTER-TIP],\n  [SORT-RASTUCE-KVADRATURA],\n  [SORT-RASTUCE-CIJENA],\n  [SORT-OPADAJUCE-KVADRATURA],\n  [SORT-OPADAJUCE-CIJENA],\n  [PRETRAGA-PRODAJA],\n  [PRETRAGA-NAJAM] \n";
    std::cin >> ind3;

    std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina();

   

    for (Nekretnina nekretnina : nekretnine)
    {
        nekretnina.prikaziInformacije();
    }


    else if (ind3 == "FILTER-CIJENA")
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

    else if (ind3 == "FILTER-ADRESA")
    {
        std::string adresa1;
        std::cout << "\nUnesite zeljenu adresu: ";
        std::cin.ignore();
        std::getline(std::cin, adresa1);

        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getAdresa() == adresa1)
                nekretnina.prikaziInformacije();
        }
    }

    else if (ind3 == "FILTER-TIP")
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

    else if (ind3 == "SORT-RASTUCE-KVADRATURA")
    {
        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiRASTUCE);

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
        }
    }

    else if (ind3 == "SORT-OPADAJUCE-KVADRATURA")
    {
        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiOPADAJUCE);

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
        }
    }

    else if (ind3 == "SORT-RASTUCE-CIJENA")
    {
        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniRASTUCE);

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
        }
    }

    else if (ind3 == "SORT-OPADAJUCE-CIJENA")
    {
        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniOPADAJUCE);

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
        }
    }
    else if (ind3 == "PRETRAGA-NAJAM")
    {
        std::cout<<"\nDostupne nekretnine za najam:\n"<<std::endl;
        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getPretraga() == ind3)
                nekretnina.prikaziInformacije();
        }
    }
     else if (ind3 == "PRETRAGA-PRODAJA")
    {
        std::cout<<"\nDostupne nekretnine za prodaju:\n"<<std::endl;

        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getPretraga() == ind3)
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