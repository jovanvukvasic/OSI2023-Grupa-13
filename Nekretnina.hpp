#pragma once
#include "Korisnik.h"
#include <vector>
#include <algorithm> 
#include <iomanip>

class Nekretnina {
private:
    std::string id;          
    std::string tip;         // Tip nekretnine (npr. "Stan", "Kuća", "Poslovni prostor")
    std::string adresa;
    std::string vlasnik;      
    double povrsina;         
    int brojSoba;            
    std::string opis;        
    double cena;        
    std::string svrha;         

    std::string dostupnost;         

public:
    // Konstruktor
    Nekretnina(const std::string& id, const std::string& tip, const std::string& adr,const std::string& vl, double pov, int brSoba, const std::string& opis, double cena, std::string& svrh, std::string& dostupna)
        : id(id), tip(tip), adresa(adr), vlasnik(vl), povrsina(pov), brojSoba(brSoba), opis(opis), cena(cena), svrha(svrh), dostupnost(dostupna) {}

    // Metoda za prikaz informacija o nekretnini
    void prikaziInformacije() const {
        if(id.size()==1)std::cout << std::setw(5) << std::setw(6) << "[ "<< id <<" ]"<< "  | " << std::setw(18)  << tip <<" | " << std::setw(29)<< adresa << " | " << std::setw(10) << svrha << " | " << std::setw(8) << std::setw(10) << povrsina <<" | "<< std::setw(8) << std::setw(10) << cena << std::setw(3) << "KM" << " | " << std::endl;    
        else std::cout << std::setw(5) << std::setw(6) << "[ "<< id <<" ]"<< " | " << std::setw(18)  << tip << " | " << std::setw(29)<< adresa << " | " << std::setw(10) << svrha << " | " << std::setw(8) << std::setw(10) << povrsina << " | "<<std::setw(8) << std::setw(10) << cena << std::setw(3) << "KM" << " | " << std::endl;    


}

    void prikaziInformacijeKonkretno() const {
    std::cout << "------------------------------------------------------"<< std::endl;    

        std::cout << "\n[" << id << "]"
                  << "\n\n    Tip: " << tip
                  << "\n    Adresa: " << adresa
                  << "\n    Površina: " << povrsina << " m2"
                  << "\n    Broj soba: " << brojSoba
                  << "\n    Opis: " << opis
                  << "\n    Cena: " << cena <<" KM"
                  << "\n    Vlasnik: " << vlasnik
                  << "\n    Svrha: " << svrha
                  << "\n    Dostupnost: " << "Dostupno"
                  << std::endl;
    std::cout << "\n------------------------------------------------------"<< std::endl;    

    }


    double getCijena()const{
        return cena;
    }
     double getPovrsina()const{
        return povrsina;
    }
    std::string getAdresa()const{
        return adresa;
    }
    std::string getId()const{
        return id;
    }
    std::string getTip()const{
        return tip;
    }
    std::string getPretraga() const
    {
        return svrha;
    }

    //ova metoda proverava da li je nekretnina za odrzavanje
    bool jePotrebnoOdrzavanje() const {
        return opis.find("održavanje") != std::string::npos;
    }

    
};