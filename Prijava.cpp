#include "Korisnik.h"

void Korisnik::prijaviSe(){
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
                    std::cout << "\nDostupne operacije vlasniku: [PRIKAZ], [SLANJE], [ODJAVA] ....\n";
                if (pr == "2")
                    std::cout << "\nDostupne operacije kupac: [PRIKAZ], [APLICIRANJE], [ODJAVA] ....\n";
                if (pr == "3")
                    std::cout << "\nDostupne operacije iznajmljivac: [PRIKAZ], [APLICIRANJE], [ODJAVA] ....\n";
                if (pr == "4")
                    std::cout << "\nDostupne operacije radnik agencije: [PRIKAZ], [REGISTROVANJE], [GENERISANJE], [ODJAVA]....\n";
                if (pr == "5")
                    std::cout << "\nDostupne operacije odrzavatelj: [PRIKAZ], [ZADACI], [AZURIRAJ], [ODJAVA]....\n";

                while (ind2 != "ODJAVA")
                {
                    // prikaz informacija o transakcijama-----------------------------------------------

                    std::cout << "\n> ";
                    std::cin >> ind2;
                    if (ind2 == "PRIKAZ"){
                        Korisnik k;
                        k.prikaziNekretnine();
                    }
                        
                    else if (ind2 == "PRIJAVA")
                        std::cout << "\nTrenutno ste vec prijavljeni.\n";

                    else if (ind2 == "SLANJE" && pr == "1")
                    {
                        int tmp;
                        tmp = slanje_ponude();
                        if (tmp)
                            k.automatski_unos();
                    }
                    else if (ind2 == "REGISTROVANJE" && pr == "4")
                        registrovanje_ponude();
                  
                    else if (pr == "5")
                    {
                        if (ind2 == "AZURIRAJ")
                            azurirajListu();
                    }
                    else if (ind2 =="GENERISANJE" && pr == "4")
                        generisiListu();
                    /*
                        U ZAVISNOSTI OD PROFILA I DOSTUPNOSTI ISTOG, PRIKAZUJU SE OPCIJE KORISNICIMA
                    */  else
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