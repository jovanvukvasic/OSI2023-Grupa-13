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

        if (ID == br) {
            outputFile << novaLinija << '\n';  // Pronađena odgovarajuća linija, kopiramo je
        } else {
            tempFile << novaLinija << '\n';  // Kopiramo sve ostale linije u temp datoteku
        }
    }

    inputFile.close();
    outputFile.close();
    tempFile.close();
}


