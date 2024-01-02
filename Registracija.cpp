#include "korisnik.h"

void Korisnik::registrujSe()
{
    std::cout << " \n [1] Vlasnik nekretnine,\n [2] Kupac nekretnine,\n [3] Prodavac nekretnine,\n [4] Radnik agencije,\n [5] Odrzavatelj,\n";
    std::cout<<"\n> Odaberite tip profila: ";
    std::getline(std::cin, tipProfila);
    int br=0;

    if (tipProfila == "1" || tipProfila == "[1] Vlasnik profila" || tipProfila == "[1]" || tipProfila == "Vlasnik nekretnine" || tipProfila == "vlasnik nekretnine" || tipProfila == "Vlasnik" || tipProfila == "vlasnik")
    {
        tipProfila = "1";
    }

    else if (tipProfila == "2" || tipProfila == "[2] Kupac nekretnine" || tipProfila == "[2]" || tipProfila == "Kupac nekretnine" || tipProfila == "kupac nekretnine" || tipProfila == "Kupac" || tipProfila == "kupac")
    {
        tipProfila = "2";
    }

    else if (tipProfila == "3" || tipProfila == "[3] Prodavac nekretnine" || tipProfila == "[3]" || tipProfila == "Prodavac nekretnine" || tipProfila == "prodavac nekretnine" || tipProfila == "Prodavac" || tipProfila == "prodavac")
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
bool Korisnik::proveriPostojanjeKorisnickogImena() const
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