#include "Korisnik.h"
#include <limits>
#include "prikazDostupnihNekretnina.h"

void Korisnik::prijaviSe()
{
    std::cout << "~ Prijava na sistem ~\n";
    std::cout << "Korisnicko ime: ";
    std::cin >> korisnickoIme;

    std::string Sifra;
    std::cout << "Lozinka: ";
    char karakter;

    while (true)
    {
        karakter = _getch();

        if (karakter == 13)
        {
            break;
        }

        if (karakter == 8 && !Sifra.empty())
        {
            std::cout << "\b \b";
            Sifra.pop_back();
        }
        else if (karakter != 8)
        {
            Sifra.push_back(karakter);
            std::cout << '*';
        }
    }

    std::ifstream file("nalozi.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string pr, ki, si, i, p, bt, ea;

        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
        {
            continue;
        }

        // uspjesna prijava---------------------------------------------------------------------------------------
        if (ki == korisnickoIme && si == Sifra)
        {
            file.close();

            std::string ind2;

            std::cout << "\n\nUspesno ste se prijavili!\n\n\n";

            Korisnik k(ki, si, pr, i, p, bt, ea);

            k.prikazProfila();

            if (pr == "1")
                std::cout << "\nDostupne operacije vlasniku: [PRIKAZ], [SLANJE], [ODJAVA], [AZURIRANJE] ....\n";
            if (pr == "2")
                std::cout << "\nDostupne operacije kupac: [PRIKAZ], [KUPOVINA], [NAJAM], [ODJAVA] ....\n";
            if (pr == "3")
                std::cout << "\nDostupne operacije iznajmljivac: [PRIKAZ], [APLICIRANJE], [ODJAVA] ....\n";
            if (pr == "4")
                std::cout << "\nDostupne operacije radnik agencije: [PRIKAZ], [REGISTROVANJE], [GENERISANJE], [ODJAVA], [ZAVOD], [BRISANJE] ,[PREGLED]....\n";
            if (pr == "5")
                std::cout << "\nDostupne operacije odrzavatelj: [PRIKAZ], [ZADACI], [AZURIRAJ], [ODJAVA]....\n";
            if (pr == "6")
                std::cout << "\nDostupne operacije adminu: [KORISNICI] ....\n";
            while (ind2 != "ODJAVA")
            {
                // prikaz informacija o transakcijama-----------------------------------------------

                std::cout << "\n> ";
                std::cin >> ind2;
                if (ind2 == "PRIKAZ")
                {
                    Korisnik k;
                    k.prikaziNekretnine();
                }

                else if (ind2 == "PRIJAVA")
                    std::cout << "\nTrenutno ste vec prijavljeni.\n";

                else if (pr == "1")
                {
                    if (ind2 == "SLANJE")
                        slanje_ponude();
                    else if (ind2 == "AZURIRANJE")
                        azuriranje_informacija_o_nekretnini();
                }
                else if (pr == "6")
                {
                    if (ind2 == "KORISNICI")
                        prikaz_informacija_o_agenciji();
                }

                //----------------------------------KUPOVINA---------------------------------
                else if (pr == "2")
                {
                    if (ind2 == "KUPOVINA")
                    {
                        nekretnineZaKupovinu();
                        kupovina();
                    }
                    if (ind2 == "NAJAM")
                    {
                        nekretnineZaNajam();
                        najam();
                    }
                }

                //----------------------------------------------------------------------------

                else if (pr == "4")
                {
                    if (ind2 == "REGISTROVANJE")
                        registrovanje_ponude();
                    else if (ind2 == "PREGLED")
                        pregled_trenutnih_ponuda();
                    else if (ind2 == "ZAVOD")
                    {
                        std::string ind3;
                        std::cout << "1. Odobri kupovinu" << std::endl;
                        std::cout << "2. Odobri najam" << std::endl;
                        std::cout << "UNESITE REDNI BROJ ZELJENE OPCIJE: ";
                        std::cin >> ind3;
                        if (ind3 == "1")
                            zavedi_kupovina();
                        else if (ind3 == "2")
                            zavedi_najam();
                    }
                    else if (ind2 == "BRISANJE")
                        upravljanje_ponudama();
                    else if (ind2 == "GENERISANJE")
                    {
                        std::string ind3;
                        std::cout << "1. Generisanje izvjestaja o transakcijama" << std::endl;
                        std::cout << "2. Generisanje izvjestaja o transakcijama" << std::endl;
                        std::cout << "3. Generisanje izvjestaja o prihodima i rashodima." << std::endl;
                        std::cout << "4. Generisanje izvjestaja o stanju racuna" << std::endl;
                        std::cout << "\nUNESITE REDNI BROJ ZELJENE OPCIJE:" << std::endl;
                        std::cin >> ind3;
                        // if (ind3 == "3")
                        //  genersanje_izvjestaja_o_prihodima_i_rashodima();
                    }
                    else if (ind2 == "LISTA")
                    {
                        
                            std::vector<std::string> odabraneAdrese;

                            std::string odabranaAdresa;
                            std::cout << "Dostupne nekretnine:" << std::endl;

                            std::vector<Nekretnina> dostupneNekretnine = prikazDostupnihNekretnina();

                            while (true)
                            {
                                std::cout << "Dostupne nekretnine:" << std::endl;

                                for (int i = 0; i < dostupneNekretnine.size(); ++i)
                                {
                                    std::cout << i + 1 << ". " << dostupneNekretnine[i].getAdresa() << std::endl;
                                }

                                std::cout << "Unesite redni broj nekretnine za koju želite generisati listu zadataka (0 za kraj): ";
                                int redniBroj;
                                std::cin >> redniBroj;

                                if (redniBroj == 0 || redniBroj > dostupneNekretnine.size())
                                {
                                    break;
                                }

                                odabranaAdresa = dostupneNekretnine[redniBroj - 1].getAdresa();
                                odabraneAdrese.push_back(odabranaAdresa);

                                std::cout << "\nUnesite zadatke za nekretninu i radnika: " << odabranaAdresa << std::endl;

                                std::string noviZadatak;

                                std::cin.ignore();

                                std::getline(std::cin, noviZadatak);

                                std::string nik;

                                std::getline(std::cin, nik);

                                std::ofstream file("generisane_liste.txt", std::ios::app);
                                file << odabranaAdresa << "," << noviZadatak << "," << nik << ",0\n";

                                file.close();

                                std::cout << "Generisana lista zadataka za nekretninu " << odabranaAdresa << " uspješno upisana u datoteku." << std::endl;
                            
                        }
                    }
                }

                else if (pr == "5")
                {
                    if (ind2 == "AZURIRAJ")
                        azurirajListu(korisnickoIme);
                }

                else
                {
                    if (ind2 != "ODJAVA")
                        std::cout << "\nTa opcija nije dostupna.\n";
                }
            }
            return;
        }

        else if (ki == korisnickoIme)
        {
            file.close();
            std::cout << "\nPogresna lozinka. Pokusajte ponovo.\n";
            return;
        }
    }

    file.close();
    std::cout << "\nKorisnicko ime nije pronadjeno. Molimo vas da se registrujete.\n";
}