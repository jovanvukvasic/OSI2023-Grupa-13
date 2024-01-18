#include "Korisnik.h"
#include "Nekretnina.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "prikazDostupnihNekretnina.h"
#include <stdlib.h>
#include <vector>
#include <limits>
#include <chrono>
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
    if (svrha == "PRODAJA")
    {
        svrha = "prodaja";
    }
    //----------------------------------------------------------------------------------------------------------------------

    //----------NAJAM------------------------------------------------------------------------------------------------------------

    else if (svrha == "NAJAM")
    {
        svrha = "najam";
    }
    else
        std::cout << "Neispravno izabrana opcija.\n";
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

int Korisnik::pregled_trenutnih_ponuda()
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
        std::string tip, adresa, vlasnik, brojSobaStr, opis;
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

        std::cout << "[" << redniBroj << "]    " << tip << " " << adresa << " " << vlasnik << " " << povrsina << " " << brojSoba << " " << opis << " " << cijena << std::endl;
        redniBroj++;
    }
    if(redniBroj==1){
        std::cout<<"\n> Trenutno nema dostupnih ponuda.\n"<<std::endl;
        return 0;
    }
    inputFile.close();
    return 1;
}

void Korisnik::registrovanje_ponude()
{
    //---------------------------------------------Dio sa trazenje IDa---------------------------------------------

    std::vector<Nekretnina> nekretnine;
    std::ifstream file("nekretnine.txt");

    if (!file.is_open())
    {
        std::cerr << "Datoteka se ne moze otvoriti 'nekretnine.txt'." << std::endl;
    }

    std::string line;
    std::string ID;
    int brojac111=0;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        std::getline(iss, ID, ',');
    }

    ID = std::to_string(std::stoi(ID) + 1);

    file.close();
    //---------------------------------------------Kraj dijela sa trazenje IDa---------------------------------------------

    brojac111 = pregled_trenutnih_ponuda();
    if (brojac111==0)return;
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
        if (redniBroj == bp)
        {
            outputFile << ID << ",";

            outputFile << novaLinija1 << ",";
            outputFile << "1\n";

    std::cout << "Ponuda je uspesno registrovana i uklonjena iz poslatih ponuda." << std::endl;

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
            std::getline(iss, svrha, ',');
            std::getline(iss, dostupnostStr);

            if (dostupnostStr == "1")
            {
                dostupnostStr = "0";
                tempFile << id << "," << tip << "," << adresa << "," << vlasnik << "," << povrsina << "," << brojSoba << "," << opis << "," << cijena << "," << svrha << "," << dostupnostStr << std::endl;
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
            std::cout << "[" << redniBroj << "]" << std::endl;
            std::cout << "    "
                      << "Ime: " << tokens[3] << std::endl;
            std::cout << "    "
                      << "Prezime: " << tokens[4] << std::endl;
            std::cout << "    "
                      << "Tip profila: " << tokens[0] << std::endl;
            std::cout << "    "
                      << "Korisnicko ime: " << tokens[1] << std::endl;
            std::cout << "    "
                      << "Broj telefona: " << tokens[5] << std::endl;
            std::cout << "    "
                      << "E-mail adresa: " << tokens[6] << std::endl;
            redniBroj++;
        }
    }

    inputFile.close();
}

void Korisnik::azuriranje_informacija_o_nekretnini()
{
    std::ifstream inputFile("nekretnine.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće otvoriti datoteku za čitanje." << std::endl;
        return;
    }

    std::cout << "> Nekretnine za korisnika :\n\n" << korisnickoIme << ":" << std::endl;

    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(5) << std::setw(6) << "  ID broj"
              << "  | " << std::setw(18) << "Tip nekretnine"
              << " | " << std::setw(29) << "Adresa nekretnine"
              << " | " << std::setw(10) << "Svrha"
              << " | " << std::setw(8) << std::setw(10) << "Cijena [KM]"
              << "   | " << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;


    std::string line;
    std::vector<std::string> tokens;
    int brojac1=0;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        tokens.clear();

        std::string token;
        while (std::getline(iss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 7 && tokens[3] == korisnickoIme && tokens[9]=="1"){
            if (tokens[0].size() == 1)
                std::cout << std::setw(5) << std::setw(6) << "[ " << tokens[0]  << " ]"
                          << "  | " << std::setw(18) << tokens[1]  << " | " << std::setw(29) << tokens[2] << " | " << std::setw(10) << tokens[8]  << " | " << std::setw(8) << std::setw(10) << tokens[7]  << std::setw(3) << "KM"
                          << " | " << std::endl;
            else
                std::cout << std::setw(5) << std::setw(6) << "[ " << tokens[0]<< " ]"
                          << " | " << std::setw(18) << tokens[1]  << " | " << std::setw(29) << tokens[2] << " | " << std::setw(10) << tokens[8]  << " | " << std::setw(8) << std::setw(10) << tokens[7]  << std::setw(3) << "KM"
                          << " | " << std::endl;
        }
        {
        brojac1++;
        
        }
    }
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;


    inputFile.close();

    int izbor;
    if(brojac1)std::cout << "Unesite ID nekretnine koju zelite azurirati/[0] - za izlaz: ";
    else{
         std::cout << "\nNema dostupnih nekretnina.\n";
         return;
    }
    std::cin >> izbor;

    if(izbor<=0 && izbor>99)return;
    

    // Otvaranje datoteke za pisanje (temp.txt)
    std::ofstream tempFile("temp.txt");

    if (!tempFile.is_open())
    {
        std::cerr << "Nije moguće otvoriti datoteku za čitanje ili pisanje." << std::endl;
        return;
    }

    inputFile.open("nekretnine.txt");
    std::cout << "Unesite nove informacije o nekretnini:" << std::endl;

    // Preskakanje odabrane nekretnine
    while (std::getline(inputFile, line))
{
    std::istringstream iss(line);
    tokens.clear();

    std::string token;
    while (std::getline(iss, token, ','))
    {
        tokens.push_back(token);
    }
        int indikator=0;


    if (tokens.size() >= 7 && tokens[3] == korisnickoIme && std::stoi(tokens[0]) == izbor && tokens[9]=="1")
    {
            std::string tipN; // Tip nekretnine (npr. "Stan", "Kuća", "Poslovni prostor")
            std::string adresa;
            double povrsina;
            int brojSoba;
            std::string opis;
            double cena;

            std::cout << "Unesite ponovo tip nekretnine: ";
            std::cin >> tipN;
            if (tipN.empty())
            {
                std::cout << "Tip nekretnine ne sme biti prazan. Molimo vas ponovite unos." << std::endl;
            }

            std::cout << "Unesite ponovo adresu nekretnine: ";
            std::cin.ignore();
            std::getline(std::cin, adresa);
            if (adresa.empty())
            {
                std::cout << "Adresa ne sme biti prazna. Molimo vas ponovite unos." << std::endl;
            }

            std::cout << "Unesite ponovo povrsinu nekretnine (m^2): ";
            std::cin >> povrsina;
            if (povrsina <= 0)
            {
                std::cout << "Povrsina mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
            }

            std::cout << "Unesite ponovo broj soba nekretnine: ";
            std::cin >> brojSoba;
            if (brojSoba <= 0)
            {
                std::cout << "Broj soba mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
            }

            std::cout << "Unesite ponovo kratak opis: ";
            std::cin.ignore();
            std::getline(std::cin, opis);

            std::cout << "Prodajna cijena nekretnine ce biti vece za 5% u odnosu na unesenu cijenu - Unesite ponovo cijenu nekretnine: ";
            std::cin >> cena;
            if (cena <= 0)
            {
                std::cout << "Cijena mora biti pozitivan broj. Molimo vas ponovite unos." << std::endl;
            }
            else
                cena = cena + (cena / 100 * 5);

            std::cout << "  > Automatski unos informacija o vlasniku." << std::endl;

            //------------PRODAJA----------------------------------------------------------------------------------------------------------
            std::string svrha;
            std::cout << "Unesite ponovo namjenu (moguce opcije [NAJAM], [PRODAJA]): ";
            std::cin >> svrha;
            if (svrha.empty())
            {
                std::cout << "Tip nekretnine ne sme biti prazan. Molimo vas ponovite unos." << std::endl;
            }
            if (svrha == "PRODAJA")
            {
                svrha = "prodaja";
            }
            //----------------------------------------------------------------------------------------------------------------------

            //----------NAJAM------------------------------------------------------------------------------------------------------------

            else if (svrha == "NAJAM")
            {
                svrha = "najam";
            }
            else
                std::cout << "Neispravno izabrana opcija.\n";
            //----------------------------------------------------------------------------------------------------------------------

             std::cout << "Zelite li sacuvati izmjene informacija o nekretnini? (Da/Ne): ";
        std::string odgovor;
        std::cin >> odgovor;
        if (odgovor == "Da" || odgovor == "da")
        {
                tempFile << tokens[0]<<","<<tipN<<","<<adresa<<","<<korisnickoIme<<","<<povrsina<<","<<brojSoba<<","<<opis<<","<<cena<<","<<svrha << ","<<tokens[9]<<std::endl;
                indikator=1;
    std::cout << "Nove informacije su uspjesno unesene. Azuriranje ceka odobrenje agencije." << std::endl;

            }
            else if (odgovor == "Ne" || odgovor == "ne")
        {
            tempFile << line << std::endl; // Ako je odgovor "Ne", upisujemo originalnu liniju
            indikator = 1;
            std::cout << "Nove informacije nisu sačuvane." << std::endl;
        }
            
        else
        {
            std::cout << "Informacije nisu sačuvane." << std::endl;
            continue; 
        }
        }
        if(!indikator)
        tempFile << line << std::endl;
        indikator=0;

    }

    inputFile.close();
    tempFile.close();

    remove("nekretnine.txt");
    rename("temp.txt", "nekretnine.txt");

}
bool Korisnik::prikaziListu(std::string korisnickoIme)
{
    std::ifstream inputFile2("generisane_liste.txt");
    int redniBroj = 1;
    std::string novaLinija1, naziv, zadatak, ime, ind, komentar;
    bool imaZadataka = false;
    while (std::getline(inputFile2, novaLinija1))
    {
        std::istringstream iss(novaLinija1);
        std::getline(iss, naziv, ',');
        std::getline(iss, zadatak, ',');
        std::getline(iss, ime, ',');
        std::getline(iss, ind, ',');
        std::getline(iss, komentar);
        if (korisnickoIme == ime && ind == "0")
        {
            std::cout << "[" << redniBroj << "]. " << naziv << ", " << zadatak << std::endl;
            imaZadataka = true;
        }
        redniBroj++;
    }
    inputFile2.close();
    if (!imaZadataka)
    {
        imaZadataka = false;
        std::cout << "\nNema zadataka za Vas.\n"
                  << std::endl;
    }
    return imaZadataka;
}
#include <limits>
void Korisnik::azurirajListu(std::string korisnickoIme)
{
    int bp;
    bool ima;

    while (true)
    {

        ima = prikaziListu(korisnickoIme);
        if (!ima)
            return;

        std::cout << "Unesite id zadatka koji zelite uraditi ili 0 za kraj: " << std::endl;
        //std::cin >> bp;

        if (!(std::cin >> bp) || bp < 0) {
            std::cout << "\nNevazeci unos. Molimo unesite ispravan id zadatka.\n\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (bp == 0)
        {
            std::cout << "Azuriranje zadataka je zavrseno." << std::endl;
            return;
        }

        std::cout << "\nDa li zelite oznaciti zadatak kao uradjen (1) ili neuradjen (0): " << std::endl;
        char status;
        std::cin >> status;

        std::string komentar;
        char zeliKomentar;
        if (status == '1')
        {
            std::cout << "\nDa li zelite unijeti komentar? (d/n): ";
            std::cin >> zeliKomentar;

            if (zeliKomentar == 'd')
            {

                std::cout << "Unesi komentar : ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, komentar);
            }

            std::ifstream inputFile5("generisane_liste.txt");
            std::ofstream tempFile("temp_poslate.txt");
            // std::ofstream completedFile("uradjeni_zadaci.txt", std::ios::app);
            if (!inputFile5.is_open() || !tempFile.is_open())
            {
                std::cerr << "Greska prilikom otvaranja datoteka." << std::endl;
                return;
            }

            int redniBroj1 = 1;
            std::string novaLinija;
            std::string naziv1, zadatak1, ime1, ind1, komentar1;

            while (std::getline(inputFile5, novaLinija))
            {
                std::istringstream iss(novaLinija);
                std::getline(iss, naziv1, ',');
                std::getline(iss, zadatak1, ',');
                std::getline(iss, ime1, ',');
                std::getline(iss, ind1, ',');
                std::getline(iss, komentar1);

                if (korisnickoIme == ime1 && ind1 == "0")
                {
                    if (redniBroj1 == bp)
                    {
                        ind1 = (status == '1') ? "1" : "0";
                        komentar1 = (komentar.empty()) ? "-" : komentar;
                    }
                }
                tempFile << naziv1 << "," << zadatak1 << "," << ime1 << "," << ind1 << "," << komentar1 << std::endl;

                redniBroj1++;
            }

            inputFile5.close();
            tempFile.close();

            std::remove("generisane_liste.txt");
            std::rename("temp_poslate.txt", "generisane_liste.txt");
        }
    }
}

void Korisnik::genersanje_izvjestaja_o_prihodima_i_rashodima()
{
    std::ifstream file("prihodi_rashodi.txt");

    if (!file.is_open())
    {
        std::cerr << "Trenutno nema izjestaja o prihodima i rashodima.txt'." << std::endl;
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
    std::ifstream file("stanje_racuna.txt");

    if (!file.is_open())
    {
        std::cerr << "Trenutno nema izjestaja o stanju racuna'." << std::endl;
        return;
    }

    std::string novac;
    file >> novac;
    file.close();

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm *tmNow = std::localtime(&time);
    char buffer[20]; // dovoljno velik bafer za formatiranje
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y. %H:%M", tmNow);
    std::cout << "Datum i vrijeme: " << buffer << std::endl;
    std::cout << "Stanje na racunu: " << novac << " KM" << std::endl;
}

void Korisnik::generisanje_izjestaja_o_transakcijama()
{
    std::ifstream file("transakcije.txt");

    if (!file.is_open())
    {
        std::cerr << "Trenutno nema transakcija.txt'." << std::endl;
        return;
    }

    std::string linija;
    while (std::getline(file, linija))
    {
        std::cout << linija << std::endl;
    }

    file.close();
}