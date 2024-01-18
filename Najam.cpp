#include "Korisnik.h"
#include "Nekretnina.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "prikazDostupnihNekretnina.h"
#include <stdlib.h>
#include <vector>
#include <limits>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>

void Korisnik::nekretnineZaNajam()
{

    std::ifstream inputFile("nekretnine.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(5) << std::setw(6) << "  ID broj"
              << "  | " << std::setw(18) << "Tip nekretnine"
              << " | " << std::setw(29) << "Adresa nekretnine"
              << " | " << std::setw(10) << "Svrha"
              << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
              << "   | " << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;

    while (std::getline(inputFile, line1))
    {

        std::istringstream iss(line1);
        std::string id, tip, adresa, vlasnik, brojSobaStr, opis, svrha, dostupnost;
        double povrsina, cijena;
        int brojSoba;

        std::getline(iss, id, ',');
        std::getline(iss, tip, ',');
        std::getline(iss, adresa, ',');
        std::getline(iss, vlasnik, ',');
        iss >> povrsina;
        iss.ignore();
        iss >> brojSoba;
        iss.ignore();
        std::getline(iss, opis, ',');
        iss >> cijena;
        iss.ignore();
        std::getline(iss, svrha, ',');
        std::getline(iss, dostupnost);

        if (dostupnost == "1" && svrha == "najam")
        {
            if (id.size() == 1)
                std::cout << std::setw(5) << std::setw(6) << "[ " << id << " ]"
                          << "  | " << std::setw(18) << tip << " | " << std::setw(29) << adresa << " | " << std::setw(10) << svrha << " | " << std::setw(8) << std::setw(10) << cijena << std::setw(3) << "KM"
                          << " | " << std::endl;
            else
                std::cout << std::setw(5) << std::setw(6) << "[ " << id << " ]"
                          << " | " << std::setw(18) << tip << " | " << std::setw(29) << adresa << " | " << std::setw(10) << svrha << " | " << std::setw(8) << std::setw(10) << cijena << std::setw(3) << "KM"
                          << " | " << std::endl;
        }
    }
    inputFile.close();
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
}

void Korisnik::najam()
{
    std::string br;
    std::cout << "Unesite broj nekretnine koju zelite iznajmiti: ";
    std::cin >> br;

    std::string imee, prezimee;
    std::cout << "Unesite ime: ";
    std::cin >> imee;
    std::cout << "Unesite prezime: ";
    std::cin >> prezimee;

    std::ifstream inputFile("nekretnine.txt");
    std::ofstream outputFile("iznajmljivanje_nekretnina.txt", std::ios::app);
    std::ofstream tempFile("tempnekretnine.txt");

    if (!inputFile.is_open() || !outputFile.is_open() || !tempFile.is_open())
    {
        std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
        return;
    }

    std::string novaLinija;
    std::string ID;

    // Pretražujemo linije i kopiramo ih u odgovarajuće datoteke
    while (std::getline(inputFile, novaLinija))
    {
        std::istringstream iss(novaLinija);
        std::getline(iss, ID, ',');
        ID.erase(std::remove_if(ID.begin(), ID.end(), ::isspace), ID.end());

        if (ID == br)
        {
            outputFile << imee << "," << prezimee << "," << korisnickoIme << "," << novaLinija << '\n'; // Pronađena odgovarajuća linija, kopir
            std::cout << "\nVas zahtjev za najam je u obradi.\n"
                      << std::endl; // Pronađena odgovarajuća linija, kopiramo je
        }
        else
        {
            tempFile << novaLinija << '\n'; // Kopiramo sve ostale linije u temp datoteku
        }
    }

    inputFile.close();
    outputFile.close();
    tempFile.close();
}
void Korisnik::zavedi_najam()
{
    std::ifstream in2("iznajmljivanje_nekretnina.txt");

    int redniBroj = 1;

    std::string linija;
    std::cout << "\n----------------------------------------------------------------------------\n\n";

    while (std::getline(in2, linija))
    {
        std::string immm, prezzz, kor, id, tip, adresa, vlasnik, opis, svrha, dostupnostStr;
        double povrsina, cijena;
        int brojSoba;
        std::istringstream iss(linija);

        std::getline(iss, immm, ',');
        std::getline(iss, prezzz, ',');
        std::getline(iss, kor, ',');
        std::getline(iss, id, ',');
        std::getline(iss, tip, ',');
        std::getline(iss, adresa, ',');
        std::getline(iss, vlasnik, ',');
        iss >> povrsina;
        iss.ignore();
        iss >> brojSoba;
        iss.ignore();
        std::getline(iss, opis, ',');
        iss >> cijena;
        iss.ignore();
        std::getline(iss, svrha, ',');
        std::getline(iss, dostupnostStr);

        std::cout << "[ " << id << " ]"
                  << " - " << tip << "                      <-> " << vlasnik << "-" << kor << std::endl;

        redniBroj++;
    }
    std::cout << "\n----------------------------------------------------------------------------\n\n";

    std::string Id;
    std::cout << "Unesite id nekretnine za koju odobravate ili ne odobravate najam: ";
    std::cin >> Id;
    in2.close();
    std::cout << "\n----------------------------------------------------------------------------\n";

    std::cout << "Unesite 1 ako zelite da odobrite najam ili 0 ako ne zelite: ";
    int odobravanje;
    std::cin >> odobravanje;
    std::cout << "\n----------------------------------------------------------------------------\n\n";

    if (odobravanje == 1)
    {
        std::ifstream inputFile("nekretnine.txt");
        if (!inputFile.is_open())
        {
            std::cerr << "Nije moguce prikazati listu ponuda1." << std::endl;
            return;
        }

        std::ofstream file("prihodi_rashodi.txt", std::ios::app);
        if (!file.is_open())
        {
            std::cerr << "Greska prilikom otvaranja datoteka2." << std::endl;
            return;
        }

        std::ofstream file2("transakcije.txt", std::ios::app);
        if (!file2.is_open())
        {
            std::cerr << "Greska prilikom otvaranja datoteka4." << std::endl;
            return;
        }
        std::ifstream file3("stanje_racuna.txt");
        if (!file3.is_open())
        {
            std::cerr << "Greska prilikom otvaranja datoteka5." << std::endl;
            std::ofstream createFile5("stanje_racuna.txt");
            if (!createFile5.is_open())
            {
                std::cerr << "Nije moguće kreirati datoteku 'stanje_racuna.txt'." << std::endl;
            }
        }
        std::string ukupna;
        file3 >> ukupna;
        double ukupna1;
        if (ukupna.empty())
        {
            ukupna1 = 0;
        }
        else
            ukupna1 = std::stod(ukupna);
        file3.close();
        std::ofstream file4("stanje_racuna.txt");
        if (!file4.is_open())
        {
            std::cerr << "Greska prilikom otvaranja datoteka6." << std::endl;
            return;
        }

        std::ofstream tempFile("temp.txt");
        if (!tempFile.is_open())
        {
            std::cerr << "Greska pri otvaranju privremene datoteke." << std::endl;
            return;
        }

        std::string line1;
        while (std::getline(inputFile, line1))
        {
            std::istringstream iss(line1);
            std::string id1;
            std::getline(iss, id1, ',');

            if (Id == id1)
            {
                std::string tip1, adresa1, vlasnik1, brojSobaStr1, opis1, dostupnostStr1, svrha1;
                double povrsina1, cijena1;
                int brojSoba1;

                std::getline(iss, tip1, ',');
                std::getline(iss, adresa1, ',');
                std::getline(iss, vlasnik1, ',');
                iss >> povrsina1;
                iss.ignore();
                iss >> brojSoba1;
                iss.ignore();
                std::getline(iss, opis1, ',');
                iss >> cijena1;
                iss.ignore();
                std::getline(iss, svrha1, ',');
                std::getline(iss, dostupnostStr1);

                if (dostupnostStr1 == "1")
                {
                    dostupnostStr1 = "2";
                    tempFile << id1 << "," << tip1 << "," << adresa1 << "," << vlasnik1 << "," << povrsina1 << "," << brojSoba1 << "," << opis1 << "," << cijena1 << "," << svrha1 << "," << dostupnostStr1 << std::endl;
                    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    std::tm *tmNow = std::localtime(&time);
                    char buffer[20]; // dovoljno velik bafer za formatiranje
                    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y. %H:%M", tmNow);

                    file << "-----------------------------------------------------------------------------------------" << std::endl;
                    file2 << "-----------------------------------------------------------------------------------------" << std::endl;
                    file << buffer << std::endl;
                    file2 << buffer << std::endl;
                    cijena1 = cijena1 / 105 * 5;
                    ukupna1 = ukupna1 + cijena1;
                    file4 << ukupna1;
                    file4.close();
                    file2 << "+" << cijena1 << " KM" << std::endl;
                    file << "Stanje na racunu: " << ukupna1 << " KM" << std::endl;
                    file << "Prihod: " << cijena1 << " KM" << std::endl;
                    file << "Rashod: 0 KM" << std::endl;
                }
                else
                {
                    tempFile << line1 << std::endl;
                }
            }
            else
            {
                tempFile << line1 << std::endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (std::remove("nekretnine.txt") == 0)
        {
            if (std::rename("temp.txt", "nekretnine.txt") != 0)
            {
                std::cerr << "Greska pri preimenovanju datoteka." << std::endl;
                std::cout << "\n----------------------------------------------------------------------------\n\n";
            }
        }
        else
        {
            std::cerr << "Greska pri brisanju originalne datoteke." << std::endl;
            std::cout << "\n----------------------------------------------------------------------------\n\n";
        }
        std::ifstream in21("iznajmljivanje_nekretnina.txt");
        std::ofstream tempFile1("temp1.txt");

        std::string linija1;

        while (std::getline(in21, linija1))
        {
            std::string immm, prezzz, kor, id, tip, adresa, vlasnik;
            std::istringstream iss(linija1);

            std::getline(iss, immm, ',');
            std::getline(iss, prezzz, ',');
            std::getline(iss, kor, ',');
            std::getline(iss, id, ',');

            if (Id == id)
            {
                std::getline(iss, tip, ',');
                std::getline(iss, adresa, ',');
                std::getline(iss, vlasnik, ',');
                //-----------------------------------------------GENERISANJE UGOVORA---------------------------------------
                std::string naziv;
                naziv = "nekretnina" + id + ".txt";
                std::ofstream nekretninaFile("ugovori/" + naziv);

                if (nekretninaFile.is_open())
                {
                    nekretninaFile << "                         ~ Ugovor o najmu ~\n"
                                   << std::endl;
                    nekretninaFile << "  Iznajmljivac: " << immm << " " << prezzz << std::endl;
                    nekretninaFile << "  Korisnicko ime iznajmljivaca: " << kor << std::endl;
                    nekretninaFile << "  Korisnicko ime vlasnika: " << vlasnik << std::endl;
                    nekretninaFile.close();
                }

                std::ofstream ugovoriFile("ugovori.txt", std::ios::app);
                if (ugovoriFile.is_open())
                {
                    ugovoriFile << id << "," << kor << std::endl;
                    ugovoriFile.close();
                }

                std::cout << "Ugovor generisan!\n   > Stranke mogu pristupiti potpisivanju." << std::endl;
                std::cout << "\n----------------------------------------------------------------------------\n\n";

                //---------------------------------------------------------------------------------------------------------
            }
            else
            {
                tempFile1 << linija1 << std::endl;
            }
        }
        in21.close();
        tempFile1.close();
        file.close();
        std::filesystem::remove("iznajmljivanje_nekretnina.txt");
        std::filesystem::rename("temp1.txt", "iznajmljivanje_nekretnina.txt");
    }
    else if (odobravanje == 0)
    {
        std::ifstream inputFile("nekretnine.txt");
        if (!inputFile.is_open())
        {
            std::cerr << "Nije moguce prikazati listu ponuda." << std::endl;
            return;
        }

        std::ofstream tempFile("temp.txt");
        if (!tempFile.is_open())
        {
            std::cerr << "Greska pri otvaranju privremene datoteke." << std::endl;
            return;
        }

        std::string line1;
        while (std::getline(inputFile, line1))
        {
            std::istringstream iss(line1);
            std::string id1;
            std::getline(iss, id1, ',');

            if (Id == id1)
            {
                std::string tip1, adresa1, vlasnik1, brojSobaStr1, opis1, dostupnostStr1, svrha1;
                double povrsina1, cijena1;
                int brojSoba1;

                std::getline(iss, tip1, ',');
                std::getline(iss, adresa1, ',');
                std::getline(iss, vlasnik1, ',');
                iss >> povrsina1;
                iss.ignore();
                iss >> brojSoba1;
                iss.ignore();
                std::getline(iss, opis1, ',');
                iss >> cijena1;
                iss.ignore();
                std::getline(iss, svrha1, ',');
                std::getline(iss, dostupnostStr1);

                if (dostupnostStr1 == "1")
                {
                    dostupnostStr1 = "1";
                    tempFile << id1 << "," << tip1 << "," << adresa1 << "," << vlasnik1 << "," << povrsina1 << "," << brojSoba1 << "," << opis1 << "," << cijena1 << "," << svrha1 << "," << dostupnostStr1 << std::endl;
                }
                else
                {
                    tempFile << line1 << std::endl;
                }
            }
            else
            {
                tempFile << line1 << std::endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (std::remove("nekretnine.txt") == 0)
        {
            if (std::rename("temp.txt", "nekretnine.txt") != 0)
            {
                std::cerr << "Greska pri preimenovanju datoteka." << std::endl;
                std::cout << "\n----------------------------------------------------------------------------\n\n";
            }
        }
        else
        {
            std::cerr << "Greska pri brisanju originalne datoteke." << std::endl;
            std::cout << "\n----------------------------------------------------------------------------\n\n";
        }
        std::ifstream in21("iznajmljivanje_nekretnina.txt");
        std::ofstream tempFile1("temp1.txt");

        std::string linija1;

        while (std::getline(in21, linija1))
        {
            std::string immm, prezzz, kor, id, tip, adresa, vlasnik;
            std::istringstream iss(linija1);

            std::getline(iss, immm, ',');
            std::getline(iss, prezzz, ',');
            std::getline(iss, kor, ',');
            std::getline(iss, id, ',');

            if (Id != id)
            {
                tempFile1 << linija1 << std::endl;

                //---------------------------------------------------------------------------------------------------------
            }
        }
        in21.close();
        tempFile1.close();
        // file.close();
        std::filesystem::remove("iznajmljivanje_nekretnina.txt");
        std::filesystem::rename("temp1.txt","iznajmljivanje_nekretnina.txt");
    }
}