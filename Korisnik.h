#pragma once
#include <iostream>
#include <cstring>
#include <sstream>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Zadatak
{
private:
    std::string naslov;
    std::string opis;
    bool zavrsen;

public:
    Zadatak(const std::string &naslov, const std::string &opis)
        : naslov(naslov), opis(opis), zavrsen(false) {}
    std::string getnaslov() const
    {
        return naslov;
    }
    bool getzavrsen() const
    {
        return zavrsen;
    }
    std::string getKomentar() const
    {
        return opis;
    }
    void setzavrsen(bool z)
    {
        this->zavrsen = z;
    }
    void setkomentar(const std::string &komentar)
    {
        this->opis = komentar;
    }
    void prikaziInformacije() const
    {
        // Prikazi informacije o zadatku
    }
};

class Korisnik
{
private:
    std::string korisnickoIme;
    std::string sifra;
    std::string tipProfila;
    std::string ime;
    std::string prezime;
    std::string brojTelefona;
    std::string emailAdresa;
    std::vector<Zadatak> listaZadataka;

public:
    Korisnik()
        : korisnickoIme(""), sifra(""), tipProfila(""), ime(""), prezime(""), brojTelefona(""), emailAdresa("")
    {
    }

    Korisnik(std::string korIme, std::string sif, std::string tipProf, std::string im, std::string prez, std::string telefon, std::string email)
        : korisnickoIme(korIme), sifra(sif), tipProfila(tipProf), ime(im), prezime(prez), brojTelefona(telefon), emailAdresa(email)
    {
    }

    void registrujSe();
    bool provjeriPostojanjeKorisnickogImena() const;
    void prijaviSe();
    void prikazProfila();
    void prikaziNekretnine();
    void odjava();
    int slanje_ponude();
    void registrovanje_ponude();
    void automatski_unos();
    void azurirajListu();
};
