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
    void slanje_ponude();
    void registrovanje_ponude();
   void azurirajListu(std::string korsinickoime);
    void ucitajNekretnine();
    void prikaziListu(std::string korsinicko);
    void pregled_trenutnih_ponuda();
    void upravljanje_ponudama();
    void prikaz_informacija_o_agenciji();
    void nekretnineZaKupovinu();
    void kupovina();
    void azuriranje_informacija_o_nekretnini();
    void nekretnineZaNajam();
    void najam();
    void zavedi_kupovina();
    void zavedi_najam();
    void genersanje_izvjestaja_o_prihodima_i_rashodima();
    void generisanje_izvjestaja_o_stanju_racuna();
    void generisanje_izjestaja_o_transakcijama();
};