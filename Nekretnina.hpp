#include "Korisnik.h"
#include <vector>

class Nekretnina {
private:
    std::string id;          
    std::string tip;         // Tip nekretnine (npr. "Stan", "Kuća", "Poslovni prostor")
    std::string adresa;      
    double povrsina;         
    int brojSoba;            
    std::string opis;        
    double cena;             
    bool dostupnost;         

public:
    // Konstruktor
    Nekretnina(const std::string& id, const std::string& tip, const std::string& adr, double pov, int brSoba, const std::string& opis, double cena, bool dostupna)
        : id(id), tip(tip), adresa(adr), povrsina(pov), brojSoba(brSoba), opis(opis), cena(cena), dostupnost(dostupna) {}

    // Metoda za prikaz informacija o nekretnini
    void prikaziInformacije() const {
        std::cout << "ID: " << id
                  << "\nTip: " << tip
                  << "\nAdresa: " << adresa
                  << "\nPovršina: " << povrsina << " m2"
                  << "\nBroj soba: " << brojSoba
                  << "\nOpis: " << opis
                  << "\nCena: " << cena
                  << "\nDostupnost: " << (dostupnost ? "Dostupno" : "Nije dostupno")
                  << std::endl;
    }
};