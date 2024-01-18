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

    std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina();

    int indikatorPraznog = 0;
    std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(5) << std::setw(6) << "  ID broj"
              << "  | " << std::setw(18) << "Tip nekretnine"
              << " | " << std::setw(29) << "Adresa nekretnine"
              << " | " << std::setw(10) << "Svrha"
              << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
              << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
              << "   | " << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

    for (Nekretnina nekretnina : nekretnine)
    {
        nekretnina.prikaziInformacije();
        indikatorPraznog++;
    }
    std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

    if (indikatorPraznog)
    {
        std::cout << "\n\nOpcioni prikaz:\n     [SELEKT],\n     [FILTER-CIJENA],\n     [FILTER-ADRESA],\n     [FILTER-TIP],\n     [SORT-RASTUCE-KVADRATURA],\n     [SORT-RASTUCE-CIJENA],\n     [SORT-OPADAJUCE-KVADRATURA],\n     [SORT-OPADAJUCE-CIJENA],\n     [PRETRAGA-PRODAJA],\n     [PRETRAGA-NAJAM],\n     [IZLAZ]\n";
        std::cout << "\nprikaz"
                  << "> ";
        std::cin >> ind3;
    }
    int selekt = 0;
    if (ind3 == "SELEKT")
    {
        selekt = 1;
        int brojaaac = 0;

        std::cout << "\n  Za detaljne informacije selektujte nekretninu / [0]: \n";

        std::string detalj;
        std::cin >> detalj;
        if (detalj == "0")
            return;

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

    else if (ind3 == "IZLAZ")
        return;

    else if (ind3 == "FILTER-CIJENA")
    {
        indikatorPraznog = 0;

        double cijen1, cijen2;
        std::cout << "Unesite opseg cijene" << std::endl;
        std::cout << "Min: ";
        std::cin >> cijen1;
        std::cout << "Max: ";
        std::cin >> cijen2;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine)
        {
            double cijeena;
            cijeena = nekretnina.getCijena();
            if (cijeena >= cijen1 && cijeena <= cijen2)
            {
                nekretnina.prikaziInformacije();
                indikatorPraznog++;
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "FILTER-ADRESA")
    {
        indikatorPraznog = 0;

        std::string adresa1;
        std::cout << "\nUnesite zeljenu ulicu: ";
        std::cin.ignore();
        std::getline(std::cin, adresa1);
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        
        for (Nekretnina nekretnina : nekretnine)
        {
int pom=0;

            for (int i = 0; i < adresa1.size()/2; i++)
            {
                if (nekretnina.getAdresa()[i] == adresa1[i])
                {
pom++;
                }
                if (pom>=adresa1.size()/3)
                {
                    nekretnina.prikaziInformacije();
                    indikatorPraznog++;
                }
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "FILTER-TIP")
    {
        indikatorPraznog = 0;

        std::string tt;
        std::cout << "\nUnesite tip nekretnine: ";
        std::cin >> tt;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getTip() == tt)
            {
                nekretnina.prikaziInformacije();
                indikatorPraznog++;
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "SORT-RASTUCE-KVADRATURA")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiRASTUCE);
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
            indikatorPraznog++;
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "SORT-OPADAJUCE-KVADRATURA")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoKvadraturiOPADAJUCE);
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
            indikatorPraznog++;
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "SORT-RASTUCE-CIJENA")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniRASTUCE);
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
            indikatorPraznog++;
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "SORT-OPADAJUCE-CIJENA")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::sort(nekretnine1.begin(), nekretnine1.end(), uporediPoCijeniOPADAJUCE);
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine1)
        {
            nekretnina.prikaziInformacije();
            indikatorPraznog++;
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    else if (ind3 == "PRETRAGA-NAJAM")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::cout << "\nDostupne nekretnine za najam:\n"
                  << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getPretraga() == "najam")
            {
                indikatorPraznog++;
                nekretnina.prikaziInformacije();
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }
    else if (ind3 == "PRETRAGA-PRODAJA")
    {
        indikatorPraznog = 0;

        std::vector<Nekretnina> nekretnine1 = nekretnine;
        std::cout << "\nDostupne nekretnine za prodaju:\n"
                  << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << std::setw(5) << std::setw(6) << "  ID broj"
                  << "  | " << std::setw(18) << "Tip nekretnine"
                  << " | " << std::setw(29) << "Adresa nekretnine"
                  << " | " << std::setw(10) << "Svrha"
                  << " | " << std::setw(8) << std::setw(10) << "Kvadratura"
                  << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
                  << "   | " << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;

        for (Nekretnina nekretnina : nekretnine)
        {

            if (nekretnina.getPretraga() == "prodaja")
            {
                nekretnina.prikaziInformacije();
                indikatorPraznog++;
            }
        }
        std::cout << "-----------------------------------------------------------------------------------------------------------" << std::endl;
    }

    if (indikatorPraznog && !selekt)
    {
        std::cout << "\n  Za detaljne informacije selektujte nekretninu / [0]: \n";

        std::string detalj;
        std::cin >> detalj;

        if (detalj == "0")
            return;
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
        if (!selekt)
            std::cout << "\n  Na zalost, ne postoje takve nekretnine.\n";
    }
}