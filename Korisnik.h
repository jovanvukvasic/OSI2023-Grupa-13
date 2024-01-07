#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


class Korisnik {
private:
    std::string korisnickoIme;
    std::string sifra;
    std::string tipProfila;
    std::string ime;
    std::string prezime;
    std::string brojTelefona;
    std::string emailAdresa;

public:
    Korisnik()
        : korisnickoIme(""), sifra(""), tipProfila(""), ime(""), prezime(""), brojTelefona(""), emailAdresa("") {
    }

    Korisnik(std::string korIme, std::string sif, std::string tipProf, std::string im, std::string prez, std::string telefon, std::string email)
        : korisnickoIme(korIme), sifra(sif), tipProfila(tipProf), ime(im), prezime(prez), brojTelefona(telefon), emailAdresa(email) {
    }

    void registrujSe()
{
    std::cout << " \n [1] Vlasnik nekretnine,\n [2] Kupac nekretnine,\n [3] Iznajmljivac nekretnine,\n [4] Radnik agencije,\n [5] Odrzavatelj,\n";
    std::cout<<"\n> Odaberite tip profila: ";
    std::cin>>tipProfila;
    int br=0;

    if (tipProfila == "1" || tipProfila == "[1] Vlasnik nekretnine" || tipProfila == "[1]" || tipProfila == "Vlasnik nekretnine" || tipProfila == "vlasnik nekretnine" || tipProfila == "Vlasnik" || tipProfila == "vlasnik")
    {
        tipProfila = "1";
    }

    else if (tipProfila == "2" || tipProfila == "[2] Kupac nekretnine" || tipProfila == "[2]" || tipProfila == "Kupac nekretnine" || tipProfila == "kupac nekretnine" || tipProfila == "Kupac" || tipProfila == "kupac")
    {
        tipProfila = "2";
    }

    else if (tipProfila == "3" || tipProfila == "[3] Iznajmljivac nekretnine" || tipProfila == "[3]" || tipProfila == "Iznajmljivac nekretnine" || tipProfila == "Iznajmljivac nekretnine" || tipProfila == "Iznajmljivac" || tipProfila == "iznajmljivac")
    {
        tipProfila = "3";
    }

    else if (tipProfila == "4" || tipProfila == "[4] Radnik agencije" || tipProfila == "[4]" || tipProfila == "Radnik agencije" || tipProfila == "radnik agencije" || tipProfila == "Radnik" || tipProfila == "radnik")
    {
        tipProfila = "4";
    }

    else if (tipProfila == "5" || tipProfila == "[5] Odrzavatelj" || tipProfila == "[5]" || tipProfila == "Odrzavatelj" || tipProfila == "odrzavatelj")
    {
        tipProfila = "5";
    }

    else {
        std::cout<<"... Tip profila nije adekvatno odabran, pokusajte ponovo.\n";
        return;
    }

    std::cout << "> Unesite korisnicko ime: ";
    std::cin >> korisnickoIme;

    while (proveriPostojanjeKorisnickogImena())
    {
        std::cout << "... Korisnicko ime vec postoji. Molimo Vas da odaberete drugo korisnicko ime.\n";
        std::cin >> korisnickoIme;
    }

    std::string sifra;
    std::string ponovljenaSifra;
    char karakter;

    std::cout << "> Unesite lozinku (minimalno 8 karaktera): ";

    while (true)
    {
        karakter = _getch();

        if (karakter == 13)
        {
            break;
        }

        if (karakter == 8 && !sifra.empty())
        {
            std::cout << "\b \b";
            sifra.pop_back();
        }
        else if (karakter != 8)
        {
            sifra.push_back(karakter);
            std::cout << '*';
        }
    }

    while (sifra.length() < 8)
    {
        std::cout << "\n... Lozinka mora imati barem 8 karaktera. Unesite ponovo lozinku: ";

        sifra.clear();

        while (true)
        {
            karakter = _getch();

            if (karakter == 13)
            {
                break;
            }

            if (karakter == 8 && !sifra.empty())
            {
                std::cout << "\b \b";
                sifra.pop_back();
            }
            else if (karakter != 8)
            {
                sifra.push_back(karakter);
                std::cout << '*';
            }
        }
    }

    std::cout << "\n> Ponovite lozinku: ";

    while (true)
    {
        karakter = _getch();

        if (karakter == 13)
        {
            if (sifra.length() >= 8 && ponovljenaSifra == sifra)
            {
                break;
            }
            else
            {
                std::cout << "\n... Lozinke se ne podudaraju ili nisu ispunjeni uslovi. Molimo Vas da ponovo unesete lozinku: ";
                ponovljenaSifra.clear();
                continue;
            }
        }

        if (karakter == 8 && !ponovljenaSifra.empty())
        {
            std::cout << "\b \b";
            ponovljenaSifra.pop_back();
        }
        else if (karakter != 8)
        {
            ponovljenaSifra.push_back(karakter);
            std::cout << '*';
        }
    }

    std::cout << "\n> Unesite ime: ";
    std::cin >> ime;

    std::cout << "> Unesite prezime: ";
    std::cin >> prezime;

    std::cout << "> Unesite broj telefona: ";
    std::cin >> brojTelefona;

    std::cout << "> Unesite e-mail adresu: ";
    std::cin >> emailAdresa;

    std::cout << "... Registracija uspjesna!\n";

    std::ofstream file("nalozi.txt", std::ios::app);
    file << tipProfila << " " << korisnickoIme << " " << sifra << " " << ime << " " << prezime << " " << brojTelefona << " " << emailAdresa << "\n";
    file.close();
}
bool proveriPostojanjeKorisnickogImena() const
{
    std::ifstream file("nalozi.txt");
    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string existingUsername;

        if (!(iss >> existingUsername))
        {

            continue;
        }

        if (existingUsername == korisnickoIme)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
    void prijaviSe() {
    std::cout << "~ Prijava na sistem ~\n";
    std::cout << "Korisnicko ime: ";
    std::cin >> korisnickoIme;

    std::string Sifra;
    std::cout << "Lozinka: ";
    char karakter;

    while (true) {
        karakter = _getch();

        if (karakter == 13) {
            break;
        }

        if (karakter == 8 && !Sifra.empty()) {
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

        // uspjesna prijava---------------------------------------------------------------------------------------
        if (ki == korisnickoIme && si == Sifra) {
            file.close();

            std::string ind2;

            std::cout << "\n\nUspesno ste se prijavili!\n\n\n";

            Korisnik k(ki, si, pr, i, p, bt, ea);

            k.prikazProfila();

            if(pr=="1")std::cout<<"\nDostupne operacije vlasniku: [PRIKAZ], [SLANJE], ....\n";
            if(pr=="2")std::cout<<"\nDostupne operacije kupac: [PRIKAZ], [APLICIRANJE], ....\n";
            if(pr=="3")std::cout<<"\nDostupne operacije iznajmljivac: [PRIKAZ], [APLICIRANJE], ....\n";
            if(pr=="4")std::cout<<"\nDostupne operacije radnik agencije: [PRIKAZ], [REGISTROVANJE], [GENERISANJE] ....\n";
            if(pr=="5")std::cout<<"\nDostupne operacije odrzavatelj: [PRIKAZ], [ZADACI], [AZADATAK] ....\n";


            while(ind2!="ODJAVA"){
                //prikaz informacija o transakcijama-----------------------------------------------

                std::cout<<"\n> ";
                std::cin>>ind2;
                if(ind2=="PRIKAZ") std::cout<<"\nTrenutno dostupne nekretnine.\n";
                else if(ind2=="PRIJAVA") std::cout<<"\nTrenutno ste vec prijavljeni.\n";
                else{
                    if(ind2!="ODJAVA")std::cout<<"\nTa opcija nije dostupna.\n";
                }
                /*
                    U ZAVISNOSTI OD PROFILA I DOSTUPNOSTI ISTOG, PRIKAZUJU SE OPCIJE KORISNICIMA
                */
            }
            return;
        }

        else if (ki == korisnickoIme) {
            file.close();
            std::cout << "\nPogresna lozinka. Pokusajte ponovo.\n";
            return;
        }
    }

    file.close();
    std::cout << "\nKorisnicko ime nije pronadjeno. Molimo vas da se registrujete.\n";
}
    void prikazProfila();
    void odjava();

};
