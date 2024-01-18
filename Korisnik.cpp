#include "Korisnik.h"
#include "Nekretnina.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "prikazDostupnihNekretnina.h"
#include <stdlib.h>
#include <vector>
#include <limits>
#include <iomanip>

void Korisnik::slanje_ponude()
{
    std::string tipN; // Tip nekretnine (npr. "Stan", "Kuća", "Poslovni prostor")
    std::string adresa;
    double povrsina;
    int brojSoba;
    std::string opis;
    double cena;

    std::cout << "Unesite tip nekretnine: ";
    std::cin >> tipN;
    if (tipN.empty())
    {
        std::cout << "Tip nekretnine ne sme biti prazan. Molimo vas ponovite unos." << std::endl;
    }

    std::cout << "Unesite adresu nekretnine: ";
    std::cin.ignore(); 
    std::getline(std::cin, adresa);
    if (adresa.empty())
    {
        std::cout << "Adresa ne sme biti prazna. Molimo vas ponovite unos." << std::endl;
    }

    std::cout << "Unesite povrsinu nekretnine (m^2): ";
    std::cin >> povrsina;
    if (povrsina <= 0)
    {
        std::cout << "Povrsina mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
    }

    std::cout << "Unesite broj soba nekretnine: ";
    std::cin >> brojSoba;
    if (brojSoba <= 0)
    {
        std::cout << "Broj soba mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
    }
    
    std::cout << "Unesite kratak opis: ";
    std::cin.ignore();
    std::getline(std::cin, opis);


    std::cout << "Prodajna cijena nekretnine ce biti vece za 5% u odnosu na unesenu cijenu - Unesite cijenu nekretnine: ";
    std::cin >> cena;
    if (cena <= 0)
    {
        std::cout << "Cena mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
    }
    else
        cena = cena + (cena / 100 * 5);

    std::cout << "Automatski unos informacija o vlasniku." << std::endl;
    // Ovdje biste mogli implementirati kod za automatski unos informacija o vlasniku


    //------------PRODAJA----------------------------------------------------------------------------------------------------------
    std::string svrha;
    std::cout << "Unesite namjenu (moguce opcije [NAJAM], [PRODAJA]): ";
    std::cin >> svrha;
    if (svrha.empty())
    {
        std::cout << "Tip nekretnine ne sme biti prazan. Molimo vas ponovite unos." << std::endl;
    }
    if(svrha=="PRODAJA"){
        svrha="prodaja";
        
    }
    //----------------------------------------------------------------------------------------------------------------------



    //----------NAJAM------------------------------------------------------------------------------------------------------------

    else if(svrha=="NAJAM"){
        svrha="najam";
    }
    else std::cout<<"Neispravno izabrana opcija.\n";
    //----------------------------------------------------------------------------------------------------------------------

    std::cout << "Zelite li sacuvati informacije o nekretnini? (Da/Ne): ";
    std::string odgovor;
    std::cin >> odgovor;
    if (odgovor == "Da" || odgovor == "da")
    {
        std::ofstream datoteka("poslate_ponude.txt", std::ios::app); // Otvori datoteku za pisanje, dodajte informacije na kraju

        if (datoteka.is_open())
        {
            datoteka << tipN << ",";
            datoteka << adresa << ",";
            datoteka << korisnickoIme << ",";
            datoteka << povrsina << ",";
            datoteka << brojSoba << ",";
            datoteka << opis << ",";
            datoteka << cena << ",";
            datoteka << svrha << std::endl;

            std::cout << "Ponuda je uspjesno poslana." << std::endl;

            datoteka.close(); // Zatvori datoteku nakon upisa
        }
        else
        {
            std::cerr << "Nemoguće otvoriti datoteku poslate_nekretnine.txt." << std::endl;
        }
    }
    else
    {
        std::cout << "Informacije nisu sačuvane." << std::endl;
    }
}

void Korisnik::pregled_trenutnih_ponuda()
{
    std::ifstream inputFile("poslate_ponude.txt"); 

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;
    int redniBroj = 1;

    while (std::getline(inputFile, line1))
    {
        std::istringstream iss(line1);
        std::string  tip, adresa, vlasnik, brojSobaStr, opis;
        double povrsina, cijena;
        int brojSoba;
        
        std::getline(iss, tip, ',');
        std::getline(iss, adresa, ',');
        std::getline(iss, vlasnik, ',');
        iss >> povrsina;
        iss.ignore(); 
        iss >> brojSoba;
        iss.ignore();
        std::getline(iss, opis, ',');
        iss >> cijena;

        std::cout <<"["<< redniBroj <<"]    " << tip <<" " <<adresa<<" " <<vlasnik<<" " <<povrsina<<" " <<brojSoba<<" " <<opis<<" " <<cijena<< std::endl;
        redniBroj++;
    }
    inputFile.close();
}

void Korisnik::registrovanje_ponude()
{
    //---------------------------------------------Dio sa trazenje IDa---------------------------------------------

    std::vector<Nekretnina> nekretnine;
    std::ifstream file("nekretnine.txt");

    if (!file.is_open()) {
        std::cerr << "Datoteka se ne moze otvoriti 'nekretnine.txt'." << std::endl;
    }

    std::string line;
    std::string ID;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        

        std::getline(iss, ID, ',');
    }

    ID = std::to_string(std::stoi(ID) + 1);

    file.close();
    //---------------------------------------------Kraj dijela sa trazenje IDa---------------------------------------------




    pregled_trenutnih_ponuda();
    int bp;
    std::cout << "Unesite broj ponude koju zelite registrovati: " << std::endl;
    std::cin >> bp;

    std::ifstream inputFile2("poslate_ponude.txt");
    std::ofstream outputFile("nekretnine.txt", std::ios::app);
    std::ofstream tempFile("temp_poslate_ponude.txt"); // Dodajemo otvaranje privremene datoteke

    if (!inputFile2.is_open() || !outputFile.is_open() || !tempFile.is_open())
    {
        std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
        return;
    }

    int redniBroj = 1;
    std::string novaLinija1;

    while (std::getline(inputFile2, novaLinija1))
    {
        if (redniBroj == bp){
            outputFile<<ID<<",";
            
            outputFile << novaLinija1 <<",";
            outputFile << "1\n";
        }
            
        else
            tempFile << novaLinija1 << '\n';

        redniBroj++;
    }

    inputFile2.close();
    outputFile.close();
    tempFile.close(); 

    // Opciono: Obrisati staru datoteku i preimenovati novu
    std::remove("poslate_ponude.txt");
    std::rename("temp_poslate_ponude.txt", "poslate_ponude.txt");

    std::cout << "Ponuda je uspesno registrovana i uklonjena iz poslatih ponuda." << std::endl;
}


 

#include <fstream>
#include <iostream>
#include <sstream>

void Korisnik::upravljanje_ponudama()
{
    std::vector<Nekretnina> nekretnine = prikazDostupnihNekretnina();

    for (Nekretnina nekretnina : nekretnine)
    {
       nekretnina.prikaziInformacije();
    }

    std::string Id;
    std::cout << "Unesite id nekretnine koju zelite da obrisete: ";
    std::cin >> Id;
    
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
        std::string id;
        std::getline(iss, id, ',');

        if (Id == id)
        {
            std::string tip, adresa, vlasnik, brojSobaStr, opis, dostupnostStr, svrha;
            double povrsina, cijena;
            int brojSoba;

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
            std::getline(iss, svrha,',');
            std::getline(iss, dostupnostStr);

            if (dostupnostStr == "1")
            {
                dostupnostStr = "0";
                tempFile << id << "," << tip << "," << adresa << "," << vlasnik << "," << povrsina << "," << brojSoba << ","<<opis<<"," << cijena << "," << svrha << "," << dostupnostStr << std::endl;
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
        }
    }
    else
    {
        std::cerr << "Greska pri brisanju originalne datoteke." << std::endl;
    }
}

void Korisnik::prikaz_informacija_o_agenciji()
{
    std::ifstream inputFile("nalozi.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati registrovane korisnike." << std::endl;
        return;
    }
    std::cout << "Registrovani korisnici:" << std::endl;

    std::string line;
    int redniBroj = 1;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::vector<std::string> tokens;

        std::string token;
        while (std::getline(iss, token, ' '))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 7)
        {
            std::cout << "[" << redniBroj <<"]"<<std::endl;
            std::cout << "    " <<"Ime: "<<tokens[3] << std::endl;
            std::cout << "    " <<"Prezime: "<<tokens[4] << std::endl;
            std::cout << "    " << "Tip profila: " << tokens[0] << std::endl;
            std::cout << "    " << "Korisnicko ime: " << tokens[1] << std::endl;
            std::cout << "    " << "Broj telefona: " << tokens[5] << std::endl;
            std::cout << "    " << "E-mail adresa: " << tokens[6] << std::endl;
            redniBroj++;
        }
    }

    inputFile.close();
}

void Korisnik::azuriranje_informacija_o_nekretnini() 
{
    std::ifstream inputFile("nekretnine.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Nije moguće otvoriti datoteku za čitanje." << std::endl;
        return;
    }

    std::cout << "Nekretnine za korisnika " << korisnickoIme << ":" << std::endl;

    std::string line;
    std::vector<std::string> tokens;

    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        tokens.clear();

        std::string token;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 7 && tokens[3] == korisnickoIme) {
            std::cout << tokens[0] << ", " << tokens[1] << ", " << tokens[2] << ", " << tokens[4] << ", " << tokens[6] << ", " << tokens[7] << ", " << tokens[8] << std::endl;
        }
    }

    inputFile.close();

    int izbor;
    std::cout << "Unesite broj nekretnine koju zelite azurirati: ";
    std::cin >> izbor;

    // Otvaranje datoteke za pisanje (temp.txt)
    std::ofstream tempFile("temp.txt");

    if (!tempFile.is_open()) {
        std::cerr << "Nije moguće otvoriti datoteku za čitanje ili pisanje." << std::endl;
        return;
    }

    inputFile.open("nekretnine.txt");

    // Preskakanje odabrane nekretnine
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        tokens.clear();

        std::string token;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 7 && tokens[3] == korisnickoIme && std::stoi(tokens[0]) == izbor) {
            // Preskoci ovu nekretninu
            continue;
        }

        tempFile << line << std::endl;
    }

    inputFile.close();
    tempFile.close();

    remove("nekretnine.txt");
    rename("temp.txt", "nekretnine.txt");
    std::cout<<"Unesite nove informacije o nekretnini:"<<std::endl;
    slanje_ponude();

    std::cout << "Nove informacije su uspjesno unesene. Azuriranje ceka odobrenje agencije."<< std::endl;
}

void Korisnik::prikaziListu(std::string korisnickoIme)
{
    std::ifstream inputFile2("generisane_liste.txt");
    int redniBroj = 1;
    std::string novaLinija1, naziv, zadatak, ime, ind;

    while (std::getline(inputFile2, novaLinija1))
    {
        std::istringstream iss(novaLinija1);
        std::getline(iss, naziv, ',');
        std::getline(iss, zadatak, ',');
        std::getline(iss, ime, ',');
        std::getline(iss, ind);
        if (korisnickoIme == ime && ind == "0")
        {
            std::cout << "[" << redniBroj << "]. " << naziv << ", " << zadatak << std::endl;
            
        }redniBroj++;
    }
    inputFile2.close();
}
#include <limits>
void Korisnik::azurirajListu(std::string korisnickoIme)
{
    int bp;
    while (true)
    {
        prikaziListu(korisnickoIme);

        std::cout << "Unesite broj zadatka koji zelite uraditi ili 0 za kraj: " << std::endl;
        std::cin >> bp;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (bp == 0)
        {
            std::cout << "Ažuriranje zadataka je završeno." << std::endl;
            return;
        }
        std::string komentar;
        std::cout << "Unesi komentar: ";
        std::getline(std::cin, komentar);

        
            std::ifstream inputFile5("generisane_liste.txt");
            std::ofstream tempFile("temp_poslate.txt");
            //std::ofstream completedFile("uradjeni_zadaci.txt", std::ios::app);
            if (!inputFile5.is_open() || !tempFile.is_open())
            {
                std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
                return;
            }

            int redniBroj1 = 1;
            std::string novaLinija;
            std::string naziv1, zadatak1, ime1, ind1;

            while (std::getline(inputFile5, novaLinija))
            {
                std::istringstream iss(novaLinija);
                std::getline(iss, naziv1, ',');
                std::getline(iss, zadatak1, ',');
                std::getline(iss, ime1, ',');
                std::getline(iss, ind1);

                if (korisnickoIme == ime1 && ind1 == "0")
                {
                    if (redniBroj1 == bp)
                    {
                        ind1 = komentar;
                        //completedFile << novaLinija << std::endl;
                    }
                }
                tempFile << naziv1 << "," << zadatak1 << "," << ime1 << "," << ind1 << std::endl;

                redniBroj1++;
            }

            inputFile5.close();
            tempFile.close();
            //completedFile.close();
            std::remove("generisane_liste.txt");
            std::rename("temp_poslate.txt", "generisane_liste.txt");
        
    }
}




void Korisnik::genersanje_izvjestaja_o_prihodima_i_rashodima()
{
    std::ifstream file("prihodi_rashodi.txt");

    if (!file.is_open())
    {
        std::cerr << "Greska prilikom otvaranja datoteke 'prihodi_rashodi.txt'." << std::endl;
        return;
    }

    std::string linija;
    while (std::getline(file, linija))
    {
        std::cout << linija << std::endl;
    }

    file.close();
}

void Korisnik::generisanje_izvjestaja_o_stanju_racuna() 
{
    std::ifstream file("prihodi_rashodi.txt");

    if(!file.is_open())
    {
        std::cerr << "Greska prilikom otvaranja datoteke 'prihodi_rashodi.txt'." << std::endl;
        return;
    }

    std::string linija;
    std::string prihod_linija;
    std::string rashod_linija;
    double prihod = 0;
    double rashod = 0;
    std::vector<std::string> linije;

    while(std::getline(file, linija)) 
    {
        linije.push_back(linija);
    }

    int pozicija = 2;

    while(pozicija < linije.size()) 
    {
        prihod_linija = linije[pozicija];
        pozicija += 1;
        rashod_linija = linije[pozicija];

        pozicija += 3;

        std::string prihod_broj;
        std::string rashod_broj;

        prihod_broj = prihod_linija.substr(8, prihod_linija.length() - 1);
        rashod_broj = rashod_linija.substr(8, rashod_linija.length() - 1);
        prihod += std::stod(prihod_broj);
        rashod += std::stod(rashod_broj);
    }

    prihod -= rashod;

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm *tmNow = std::localtime(&time);
    char buffer[20]; // dovoljno velik bafer za formatiranje
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y. %H:%M", tmNow);
    std::cout << "Trenutno vrijeme i datum: " << buffer << std::endl;
    std::cout << std::fixed <<  std::setprecision(2) << "Stanje ukupno: " << prihod << std::endl;
}
