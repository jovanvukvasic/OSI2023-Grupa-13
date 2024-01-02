#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>
#include <fstream>

class Korisnik {
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
        : korisnickoIme(""), sifra(""), tipProfila(""), ime(""), prezime(""), brojTelefona(""), emailAdresa("") {
    }

    Korisnik(std::string korIme, std::string sif, std::string tipProf, std::string im, std::string prez, std::string telefon, std::string email)
        : korisnickoIme(korIme), sifra(sif), tipProfila(tipProf), ime(im), prezime(prez), brojTelefona(telefon), emailAdresa(email) {
    }

    void registrujSe();

private:
    bool proveriPostojanjeKorisnickogImena() const;
};
