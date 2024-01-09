#include "Korisnik.h"

int Korisnik::slanje_ponude()
{
    std::string tipN; // Tip nekretnine (npr. "Stan", "Kuća", "Poslovni prostor")
    std::string adresa;
    double povrsina;
    int brojSoba;
    std::string opis;
    double cena;

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

    std::cout << "Unesite tip nekretnine: ";
    std::cin >> tipN;
    if (tipN.empty())
    {
        std::cout << "Tip nekretnine ne sme biti prazan. Molimo vas ponovite unos." << std::endl;
    }

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
    cena=cena+(cena/100*5);

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
            // Upisujemo informacije u datoteku
            datoteka << adresa << ' ';
            datoteka << povrsina << ' ';
            datoteka << brojSoba << ' ';
            datoteka << tipN << ' ';
            datoteka << opis << ' ';
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
    if(odgovor=="DA" || odgovor=="Da" || odgovor=="da")
    return 1;
    else return 0;
}

void Korisnik::registrovanje_ponude()
{
    std::ifstream inputFile("poslate_ponude.txt"); // Zamenite "nekretnine.txt" sa imenom vaše datoteke

    if (!inputFile.is_open())
    {
        std::cerr << "Nije moguće prikazati listu ponuda." << std::endl;
    }

    std::string line1;
    std::string line2;
    int redniBroj = 1;

   while (std::getline(inputFile, line1) && std::getline(inputFile, line2))
    {
        std::cout << redniBroj <<' '<<line1<<std::endl;
        std::cout<< line2  << std::endl;
        redniBroj++;
    }
    

    inputFile.close();
}


void Korisnik::automatski_unos()
{
    std::ofstream datoteka("poslate_ponude.txt", std::ios::app); // Otvori datoteku za pisanje, dodajte informacije na kraju

        if (datoteka.is_open())
        {
            datoteka<<ime<<' ';
            datoteka<<prezime<<' ';
            datoteka<<brojTelefona<<' ';
            datoteka<<emailAdresa<<std::endl;
            datoteka<<tipProfila<<std::endl;
        }
}