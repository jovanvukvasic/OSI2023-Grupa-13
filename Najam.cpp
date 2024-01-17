#include "Korisnik.h"
#include "Nekretnina.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "prikazDostupnihNekretnina.h"
#include <stdlib.h>
#include <vector>
#include <limits>

void Korisnik::nekretnineZaNajam(){


    std::ifstream inputFile("nekretnine.txt"); 

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;

    while (std::getline(inputFile, line1))
    {

        std::istringstream iss(line1);
        std::string  id,tip, adresa, vlasnik, brojSobaStr, opis,svrha,dostupnost;
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

        if(dostupnost=="1" && svrha=="najam") std::cout <<"["<< id <<"]    " << tip <<" " <<adresa<<" " <<vlasnik<<" " <<povrsina<<" " <<brojSoba<<" " <<opis<<" " <<cijena<< std::endl;
    }
    inputFile.close();
}

void Korisnik::najam() {
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

    if (!inputFile.is_open() || !outputFile.is_open() || !tempFile.is_open()) {
        std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
        return;
    }

    std::string novaLinija;
    std::string ID;

    // Pretražujemo linije i kopiramo ih u odgovarajuće datoteke
    while (std::getline(inputFile, novaLinija)) {
        std::istringstream iss(novaLinija);
        std::getline(iss, ID, ',');
        ID.erase(std::remove_if(ID.begin(), ID.end(), ::isspace), ID.end());

        if (ID == br) {
              outputFile << imee << "," << prezimee << "," << novaLinija << '\n'; // Pronađena odgovarajuća linija, kopir
            std::cout << "\nVas zahtjev za najam je u obradi.\n" << std::endl; // Pronađena odgovarajuća linija, kopiramo je
        } else {
            tempFile << novaLinija << '\n';  // Kopiramo sve ostale linije u temp datoteku
        }
    }

    inputFile.close();
    outputFile.close();
    tempFile.close();
     std::remove("nekretnine.txt");
    std::rename("tempnekretnine.txt", "nekretnine.txt");
}



void Korisnik::zavedi_najam()
{
    int bp;
    std::cout << "Unesite broj ponude ciji najam odobravate: ";
    std::cin >> bp;

    std::ifstream inputFile2("iznajmljivanje_nekretnina.txt");
    std::ofstream outputFile("nekretnine.txt", std::ios::app);
    std::ofstream tempFile("temp.txt");

    if (!inputFile2.is_open() || !outputFile.is_open() || !tempFile.is_open())
    {
        std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
        return;
    }

    int redniBroj = 1;
    std::string novaLinija1;

    while (std::getline(inputFile2, novaLinija1))
    {
        std::istringstream iss(novaLinija1);
        if (redniBroj == bp)
        {

            std::string immm, prezzz, id, tip, adresa, vlasnik, opis, svrha, dostupnostStr;
            double povrsina, cijena;
            int brojSoba;

            std::getline(iss, immm, ',');
            std::getline(iss, prezzz, ',');
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
            if (dostupnostStr == "1")

                dostupnostStr = "2";
            outputFile << id << "," << tip << "," << adresa << "," << vlasnik << "," << povrsina << "," << brojSoba << "," << opis << "," << cijena << "," << svrha << ',' << dostupnostStr << std::endl;
        }
        else
        {
            tempFile << novaLinija1 << '\n';
        }
        redniBroj++;
    }
    inputFile2.close();
    outputFile.close();
    tempFile.close();

    std::remove("iznajmljivanje_nekretnina.txt");
    std::rename("temp.txt", "iznajmljivanje_nekretnina.txt");

    std::cout << "Zahtjev za najam je uspjesno poslat." << std::endl;
}