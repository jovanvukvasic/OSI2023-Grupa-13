#include "Korisnik.h"
#include <limits>
#include "prikazDostupnihNekretnina.h"

void Korisnik::prijaviSe()
{
    int ind = 0;
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
            std::cout << "\n----------------------------------------------------------------------------------------------------------";

            std::string ind2;

            std::cout << "\n\nUspjesno ste se prijavili!\n\n";
            std::cout << "----------------------------------------------------------------------------------------------------------\n";

            Korisnik k(ki, si, pr, i, p, bt, ea);

            k.prikazProfila();
            std::cout << "----------------------------------------------------------------------------------------------------------\n";

            if (pr == "1")
                std::cout << "\nDostupne operacije vlasniku: [PRIKAZ], [SLANJE], [ODJAVA], [AZURIRANJE] ....\n";
            if (pr == "2")
                std::cout << "\nDostupne operacije kupac: [PRIKAZ], [KUPOVINA], [ODJAVA] ....\n";
            if (pr == "3")
                std::cout << "\nDostupne operacije iznajmljivac: [PRIKAZ], [NAJAM], [ODJAVA] ....\n";
            if (pr == "4")
                std::cout << "\nDostupne operacije radnik agencije: \n[PRIKAZ], [REGISTROVANJE], [GENERISANJE], [ODJAVA], [UPRAVLJANJE], [BRISANJE], [PREGLED], [LISTAZADATAKA]\n";
            if (pr == "5")
                std::cout << "\nDostupne operacije odrzavatelj: [PRIKAZ], [ZADACI], [AZURIRAJ], [ODJAVA]....\n";
            if (pr == "6")
                std::cout << "\n";
            std::cout << "\n----------------------------------------------------------------------------------------------------------\n";

            while (ind2 != "ODJAVA")
            {
                if (pr == "2" && ind == 0)
                {
                    ind = 1;
                    std::ifstream inputF2("ugovori.txt");
                    std::string novaL1, nekretnina, kupac;

                    while (std::getline(inputF2, novaL1))
                    {
                        std::istringstream iss(novaL1);
                        std::getline(iss, nekretnina, ',');
                        std::getline(iss, kupac);
                        if (korisnickoIme == kupac)
                        {
                            std::cout << " \nVasa kupovina je odobrena, ugovor je generisan i spreman za potpisivanje." << std::endl;
                            std::cout << "   > ID nekretnine: " << nekretnina << ", a ugovor se cuva pod nazivom: "
                                      << "nekretnina" + nekretnina << std::endl;
                        }
                    }

                    inputF2.close();
                }
                if (pr == "3" && ind == 0)
                {
                    ind = 1;
                    std::ifstream inputF2("ugovori.txt");
                    std::string novaL1, nekretnina, kupac;

                    while (std::getline(inputF2, novaL1))
                    {
                        std::istringstream iss(novaL1);
                        std::getline(iss, nekretnina, ',');
                        std::getline(iss, kupac);
                        if (korisnickoIme == kupac)
                        {
                            std::cout << " \nVas najam je odobren, ugovor je generisan i spreman za potpisivanje." << std::endl;
                            std::cout << "   > ID nekretnine: " << nekretnina << ", a ugovor se cuva pod nazivom: "
                                      << "nekretnina" + nekretnina << std::endl;
                        }
                    }

                    inputF2.close();
                }
                if (pr == "6")
                {
                    //prikaz_informacija_o_agenciji();

                    std::string naziv;

                    std::ifstream file("nalozi.txt");
                    std::string line;
                    std::string pr, ki, si, i, p, bt, ea;
                    int rb = 1;
                    std::cout << "Radnici agencije: " << std::endl;

                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    std::cout << "RB |" << std::setw(9) << "Kor. ime"
                              << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << "Ime"
                              << " | " << std::setw(8) << std::setw(10) << "Prezime"
                              << " | " << std::setw(33) << "E-adresa"
                              << " | " << std::endl;
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    while (std::getline(file, line))
                    {

                        std::istringstream iss(line);
                        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
                        {
                            continue;
                        }
                        else
                        {
                            if (pr == "4")
                            {

                                std::cout << rb << ". |" << std::setw(9) << ki << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << i << " | " << std::setw(8) << std::setw(10) << p << " | " << std::setw(33) << ea << " | " << std::endl;
                                rb++;
                            }
                        }
                    }
                    file.close();
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;


                    std::ifstream file1("nalozi.txt");
                    
                    rb = 1;
                    std::cout << "\nOdrzavaci: " << std::endl;

                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    std::cout << "RB |" << std::setw(9) << "Kor. ime"
                              << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << "Ime"
                              << " | " << std::setw(8) << std::setw(10) << "Prezime"
                              << " | " << std::setw(33) << "E-adresa"
                              << " | " << std::endl;
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    while (std::getline(file1, line))
                    {

                        std::istringstream iss(line);
                        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
                        {
                            continue;
                        }
                        else
                        {
                            if (pr == "5")
                            {

                                std::cout << rb << ". |" << std::setw(9) << ki << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << i << " | " << std::setw(8) << std::setw(10) << p << " | " << std::setw(33) << ea << " | " << std::endl;
                                rb++;
                            }
                        }
                    }
                    file1.close();
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;
            
            
                    std::ifstream file2("nalozi.txt");
                    
                    rb = 1;
                    std::cout << "\nVlasnici nekretnina: " << std::endl;

                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    std::cout << "RB |" << std::setw(9) << "Kor. ime"
                              << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << "Ime"
                              << " | " << std::setw(8) << std::setw(10) << "Prezime"
                              << " | " << std::setw(33) << "E-adresa"
                              << " | " << std::endl;
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    while (std::getline(file2, line))
                    {

                        std::istringstream iss(line);
                        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
                        {
                            continue;
                        }
                        else
                        {
                            if (pr == "1")
                            {

                                std::cout << rb << ". |" << std::setw(9) << ki << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << i << " | " << std::setw(8) << std::setw(10) << p << " | " << std::setw(33) << ea << " | " << std::endl;
                                rb++;
                            }
                        }
                    }
                    file2.close();
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;
 
                    std::ifstream file3("nalozi.txt");
                    
                    rb = 1;
                    std::cout << "\nKupci: " << std::endl;

                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    std::cout << "RB |" << std::setw(9) << "Kor. ime"
                              << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << "Ime"
                              << " | " << std::setw(8) << std::setw(10) << "Prezime"
                              << " | " << std::setw(33) << "E-adresa"
                              << " | " << std::endl;
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    while (std::getline(file3, line))
                    {

                        std::istringstream iss(line);
                        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
                        {
                            continue;
                        }
                        else
                        {
                            if (pr == "2")
                            {

                                std::cout << rb << ". |" << std::setw(9) << ki << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << i << " | " << std::setw(8) << std::setw(10) << p << " | " << std::setw(33) << ea << " | " << std::endl;
                                rb++;
                            }
                        }
                    }
                    file3.close();
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;
 
                    std::ifstream file4("nalozi.txt");
                    
                    rb = 1;
                    std::cout << "\nIznajmljivaci: " << std::endl;

                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    std::cout << "RB |" << std::setw(9) << "Kor. ime"
                              << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << "Ime"
                              << " | " << std::setw(8) << std::setw(10) << "Prezime"
                              << " | " << std::setw(33) << "E-adresa"
                              << " | " << std::endl;
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;

                    while (std::getline(file4, line))
                    {

                        std::istringstream iss(line);
                        if (!(iss >> pr >> ki >> si >> i >> p >> bt >> ea))
                        {
                            continue;
                        }
                        else
                        {
                            if (pr == "3")
                            {

                                std::cout << rb << ". |" << std::setw(9) << ki << " | " << std::setw(10) << " | " << std::setw(8) << std::setw(10) << i << " | " << std::setw(8) << std::setw(10) << p << " | " << std::setw(33) << ea << " | " << std::endl;
                                rb++;
                            }
                        }
                    }
                    file4.close();
                    std::cout << "--------------------------------------------------------------------------------------- " << std::endl;
                    
                    generisanje_izjestaja_o_transakcijama();
                
                }
                // prikaz informacija o transakcijama-----------------------------------------------
                std::cout << "\n"
                          << korisnickoIme << "> ";
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

                //----------------------------------KUPOVINA---------------------------------
                else if (pr == "2")
                {

                    if (ind2 == "KUPOVINA")
                    {
                        nekretnineZaKupovinu();
                        kupovina();
                    }
                }
                else if (pr == "3")
                {
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
                    else if (ind2 == "PREGLED"){
                        int p;
                        p=pregled_trenutnih_ponuda();
                    }
                    else if (ind2 == "UPRAVLJANJE")
                    {
                        std::string ind3;
                        std::cout << "1. Odobri kupovinu" << std::endl;
                        std::cout << "2. Odobri najam" << std::endl;
                        std::cout << "UNESITE REDNI BROJ ZELJENE OPCIJE: ";
                        std::cin >> ind3;
                        if (ind3 == "1")
                            upravljanje_statusom_transakcija_kupovine();
                        else if (ind3 == "2")
                        upravljanje_statusom_transakcija_najma();
                    }
                    else if (ind2 == "BRISANJE")
                        upravljanje_ponudama();
                    else if (ind2 == "GENERISANJE")
                    {
                        std::string ind3;
                        std::cout << "1. Generisanje izvjestaja o transakcijama" << std::endl;
                        std::cout << "2. Generisanje izvjestaja o prihodima i rashodima." << std::endl;
                        std::cout << "3. Generisanje izvjestaja o stanju racuna" << std::endl;
                        std::cout << "\nUNESITE REDNI BROJ ZELJENE OPCIJE:" << std::endl;
                        std::cin >> ind3;
                        if (ind3 == "2")
                            genersanje_izvjestaja_o_prihodima_i_rashodima();
                        else if (ind3 == "3")
                            generisanje_izvjestaja_o_stanju_racuna();
                        else if (ind3 == "1")
                            generisanje_izjestaja_o_transakcijama();
                    }
                    else if (ind2 == "LISTAZADATAKA")
                    {

                        std::vector<std::string> odabraneAdrese;

                        std::string odabranaAdresa;

                        std::vector<Nekretnina> dostupneNekretnine = prikazDostupnihNekretnina();

                        while (true)
                        {
                            std::cout << "Dostupne nekretnine:" << std::endl;

                            for (int i = 0; i < dostupneNekretnine.size(); ++i)
                            {
                                std::cout << i + 1 << ". " << dostupneNekretnine[i].getAdresa() << std::endl;
                            }

                            std::cout << "Unesite redni broj nekretnine za koju zelite generisati listu zadataka (0 za kraj): ";
                            int redniBroj;
                           // std::cin >> redniBroj;
                           // int redniBroj;
                            if (!(std::cin >> redniBroj) || redniBroj < 0 || redniBroj > dostupneNekretnine.size())
                            {
                                std::cout << "\nUnos je nevazeci. Molimo unesite ispravan redni broj.\n\n" << std::endl;
                                std::cin.clear();                                                   // Očisti zastavice greške
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Odbaci nevalidan unos
                                continue;                                                           // Preskoči ostatak iteracije petlje
                            }

                            if (redniBroj == 0)
                            {
                                break; // Izlaz iz petlje ako je uneseno 0
                            }

                            if (redniBroj == 0 || redniBroj > dostupneNekretnine.size())
                            {
                                return;
                            }

                            odabranaAdresa = dostupneNekretnine[redniBroj - 1].getAdresa();
                            odabraneAdrese.push_back(odabranaAdresa);

                            std::cout << "\nUnesite zadatak za nekretninu: " << odabranaAdresa << std::endl;

                            std::string noviZadatak;

                            std::cin.ignore();

                            std::getline(std::cin, noviZadatak);
                            std::cout << "\nUnesite korisnicko ime radnika : ";

                            std::string nik;

                            std::getline(std::cin, nik);

                            std::ofstream file("generisane_liste.txt", std::ios::app);
                            file << odabranaAdresa << "," << noviZadatak << "," << nik << ",0"
                                 << ","
                                 << "\n";

                            file.close();

                            std::cout << "Generisana lista zadataka za nekretninu " << odabranaAdresa << " uspjesno upisana u datoteku." << std::endl;
                        }
                    }
                }

                else if (pr == "5")
                {
                    if (ind2 == "AZURIRAJ")
                        azurirajListu(korisnickoIme);
                    else if (ind2 == "ZADACI")
                        prikaziListu(korisnickoIme);
                }

                else
                {
                    if (ind2 != "ODJAVA")
                        std::cout << "\nTa opcija nije dostupna.\n";
                }
            }
            if (ind2 == "ODJAVA")
                std::cout << "> Upravo ste se odjavili sa sistema...\n";
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