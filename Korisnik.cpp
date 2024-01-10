#include "Korisnik.h"
#include "Nekretnina.hpp"

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
    std::cin.ignore(); // Da se izbegne problem sa preostalim newline karakterom u baferu
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
    std::cin.ignore(); // Da se izbegne problem sa preostalim newline karakterom u baferu

    std::cout << "Unesite opis nekretnine: ";
    std::cin.ignore(); // Da se izbegne problem sa preostalim newline karakterom u baferu
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
            datoteka << cena << std::endl;

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

void Korisnik::pregle_trenutnih_ponuda()
{
    std::ifstream inputFile("poslate_ponude.txt"); // Zamenite "nekretnine.txt" sa imenom vaše datoteke

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;
    int redniBroj = 1;

    while (std::getline(inputFile, line1))
    {

        std::cout << redniBroj << ' ' << line1 << std::endl;
        redniBroj++;
    }
    inputFile.close();
}
void Korisnik::registrovanje_ponude()
{
    pregle_trenutnih_ponuda();
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
            outputFile << novaLinija1 << '\n';
        else
            tempFile << novaLinija1 << '\n';

        redniBroj++;
    }

    inputFile2.close();
    outputFile.close();
    tempFile.close(); // Zatvaranje privremene datoteke

    // Opciono: Obrisati staru datoteku i preimenovati novu
    std::remove("poslate_ponude.txt");
    std::rename("temp_poslate_ponude.txt", "poslate_ponude.txt");

    std::cout << "Ponuda je uspesno registrovana i uklonjena iz poslatih ponuda." << std::endl;
}

void Korisnik::azurirajListu()
{
    std::cout << "Izaberite zadatak koji želite ažurirati:" << std::endl;
    int i = 0;
    while (i < listaZadataka.size())
    {
        std::cout << i + 1 << ". " << listaZadataka[i].getnaslov() << std::endl;
        i++;
    }
    int izbor;
    std::cout << "> ";
    std::cin >> izbor;
    if (izbor < 1 || izbor > i)
    {
        std::cout << "Nevazeci unos." << std::endl;
        return;
    }
    int izabran = izbor - 1;
    std::cout << "Prikaz zadatka: " << listaZadataka[izabran].getnaslov() << std::endl;

    char zavrsen;
    std::cout << "Da li je zadatak završen? (D/N): ";
    std::cin >> zavrsen;
    if (zavrsen == 'D' || zavrsen == 'd')
        listaZadataka[izabran].setzavrsen(true);
    else
        listaZadataka[izabran].setzavrsen(false);

    char zeliKomentar;
    std::cout << "Želite li unijeti komentar? (D/N): ";
    std::cin >> zeliKomentar;
    std::string komentar;
    if (zeliKomentar == 'D' || zeliKomentar == 'd')
    {
        std::cout << "Unesite komentar: ";
        std::cin.ignore();
        std::getline(std::cin, komentar);
        listaZadataka[izabran].setkomentar(komentar);
    }
    std::ofstream file("azurirane_liste.txt");
    for (const auto &zadatak : listaZadataka)
    {
        file << zadatak.getnaslov() << " " << zadatak.getKomentar() << " " << (zadatak.getzavrsen() ? "1" : "0") << "\n";
    }
    file.close();
}

std::vector<Nekretnina> listaNekretnina;

void Korisnik::ucitajNekretnine()
{
    std::ifstream file("nekretnine.txt");

    if (!file.is_open())
    {
        std::cerr << "Greska pri otvaranju fajla nekretnine.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string id, tip, adresa, vlasnik, opis;
        double povrsina, cena;
        int brojSoba;
        bool dostupnost;

        if (std::getline(iss, id, ',') >> tip >> adresa >> vlasnik >> povrsina >> brojSoba >> opis >> cena >> dostupnost)
        {
            Nekretnina nekretnina(id, tip, adresa, vlasnik, povrsina, brojSoba, opis, cena, dostupnost);
            listaNekretnina.push_back(nekretnina);
        }
    }
    if (listaNekretnina.empty())
    {
        std::cout << "Nema dostupnih nekretnina." << std::endl;
        return;
    }

    file.close();
}

void Korisnik::generisiListu()
{
    ucitajNekretnine();
    std::cout << "Dostupne nekretnine:" << std::endl;
    for (const auto &nekretnina : listaNekretnina)
    {
        std::cout << nekretnina.getAdresa() << std::endl;
    }
    std::vector<std::string> odabraneAdrese;
    std::string odabranaAdresa;
    while (listaNekretnina.size())
    {
        std::cout << "Unesite adresu nekretnine za koju želite generisati listu zadataka: ";
        std::cin.ignore();
        std::getline(std::cin, odabranaAdresa);
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (odabranaAdresa == "0" || odabranaAdresa.empty())
        {
            break;
        }
        bool adresaValidna = false;
        for (const auto &nekretnina : listaNekretnina)
        {
            if (nekretnina.getAdresa() == odabranaAdresa)
            {
                adresaValidna = true;
                break;
            }
        }
        if (adresaValidna)
        {
            odabraneAdrese.push_back(odabranaAdresa);
        }
        else
        {
            std::cout << "Nekretnina sa tom adresom nije pronađena. Molimo Vas da ponovite unos." << std::endl;
        }
    }
    std::vector<Zadatak> listaZadataka;
    std::cout << "Unesite zadatke za nekretninu: " << odabranaAdresa << std::endl;

    std::string noviZadatak;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, noviZadatak);

        if (noviZadatak == "0")
        {
            break;
        }

        Zadatak noviZad(odabranaAdresa, noviZadatak);
        listaZadataka.push_back(noviZad);
    }

    std::ofstream file("generisane_liste.txt", std::ios::app);
    for (const auto &zadatak : listaZadataka)
    {
        file << odabranaAdresa << " " << zadatak.getnaslov() << " " << zadatak.getKomentar() << " " << (zadatak.getzavrsen() ? "1" : "0") << "\n";
    }
    file.close();

    std::cout << "Generisana lista zadataka za nekretninu " << odabranaAdresa << " uspješno upisana u datoteku." << std::endl;
}
 

//TODO

/*void Korisnik::upravljanje_ponudama()
{
    prikaziNekretnine();
    std::string id;
    std::cout << "Unesite id nekretnine koju zelite da obrisete: ";
    std::cin >> id;
    std::ifstream inputFile("nekretnine.txt"); // Zamenite "nekretnine.txt" sa imenom vaše datoteke

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;
    std::string tmp;
    while (std::getline(inputFile, line1))
    {
        std::cout << line1 << std::endl;
        
    }
    inputFile.close();
}*/