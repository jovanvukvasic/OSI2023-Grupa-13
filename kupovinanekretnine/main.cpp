#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Struktura za pohranu podataka o nekretninama
struct Nekretnina {
    int id;
    string naziv;
    double cijena;
};

// Struktura za pohranu podataka o korisnicima
struct Korisnik {
    int id;
    string imePrezime;
    string korisnickoIme;
    string lozinka;
    string uloga;
};

// Funkcija za učitavanje podataka iz datoteke
vector<string> ucitajPodatkeIzDatoteke(const string& datoteka) {
    ifstream file(datoteka);
    vector<string> linije;
    string linija;
    while (getline(file, linija)) {
        linije.push_back(linija);
    }
    file.close();
    return linije;
}

// Funkcija za prikaz opcija kupovine nekretnine
void prikaziOpcijeKupovine() {
    cout << "Odaberite nekretninu za kupovinu:" << endl;
    vector<string> nekretnine = ucitajPodatkeIzDatoteke("nekretnine.txt");
    for (const auto& nekretnina : nekretnine) {
        cout << nekretnina << endl;
    }
}

void generisiUgovorIRacun(const Nekretnina& nekretnina, const Korisnik& kupac) {
    // Simulirani ugovor
    string ugovor = "Ugovor o kupovini nekretnine\n\n";
    ugovor += "Nekretnina: " + nekretnina.naziv + "\n";
    ugovor += "Kupac: " + kupac.imePrezime + "\n";
    ugovor += "Cijena: " + to_string(nekretnina.cijena) + " KM\n";
    cout << "Postovani, ovo je Vas ugovor o kupovini nekretnine. Hvala Vam na povjerenju!\nu ";
    // Dodajte ostale informacije o ugovoru prema potrebi

    // Simulirani račun
    string racun = "Racun za kupljenu nekretninu\n\n";
    racun += "Nekretnina: " + nekretnina.naziv + "\n";
    racun += "Cijena: " + to_string(nekretnina.cijena) + " KM\n";
    // Dodajte ostale informacije o računu prema potrebi

    // Spremanje u datoteke
    ofstream ugovorFile("kupljenaNekretnina.ugovor.txt");
    ugovorFile << ugovor;
    ugovorFile.close();

    ofstream racunFile("kupljenaNekretnina.racun.txt");
    racunFile << racun;
    racunFile.close();
}

void ispisiUgovorIRacun() {
    // Čitanje sadržaja ugovora
    ifstream ugovorFile("kupljenaNekretnina.ugovor.txt");
    stringstream ugovorStream;
    ugovorStream << ugovorFile.rdbuf();
    string ugovor = ugovorStream.str();
    ugovorFile.close();

    // Čitanje sadržaja računa
    ifstream racunFile("kupljenaNekretnina.racun.txt");
    stringstream racunStream;
    racunStream << racunFile.rdbuf();
    string racun = racunStream.str();
    racunFile.close();

    // Ispis na ekran
    cout << "===== Ugovor =====\n" << ugovor << endl;
    cout << "===== Račun =====\n" << racun << endl;
}

int main() {
    // Učitavanje podataka o korisnicima
    vector<string> korisniciLinije = ucitajPodatkeIzDatoteke("korisnici.txt");
    vector<Korisnik> korisnici;
    for (const auto& linija : korisniciLinije) {
        stringstream ss(linija);
        Korisnik korisnik;
        ss >> korisnik.id >> korisnik.imePrezime >> korisnik.korisnickoIme >> korisnik.lozinka >> korisnik.uloga;
        korisnici.push_back(korisnik);
    }

     // Prijavljivanje korisnika
    string korisnickoIme, lozinka;
    cout << "Unesite korisnicko ime: ";
    cin >> korisnickoIme;
    cout << "Unesite lozinku: ";
    cin >> lozinka;

    // Provjera prijave korisnika
    bool prijavaUspjesna = false;
     Korisnik kupac;

    for (const auto& korisnik : korisnici) {
        if (korisnik.korisnickoIme == korisnickoIme && korisnik.lozinka == lozinka && korisnik.uloga == "buyer") {
            prijavaUspjesna = true;
            kupac = korisnik;
            break;
        }
    }

    if (!prijavaUspjesna) {
        cout << "Pogresno korisnicko ime ili lozinka ili nemate prava za kupovinu." << endl;
        return 1;
    }

    vector<string> nekretnineLinije = ucitajPodatkeIzDatoteke("nekretnine.txt");

     int odabranaNekretninaId;
    cout << "Unesite ID nekretnine koju zelite kupiti: ";
    cin >> odabranaNekretninaId;

    Nekretnina odabranaNekretnina;
    for (const auto& nekretnina : nekretnineLinije) {
        stringstream ss(nekretnina);
        ss >> odabranaNekretnina.id >> odabranaNekretnina.naziv >> odabranaNekretnina.cijena;
        if (odabranaNekretnina.id == odabranaNekretninaId) {
            cout << "Kupovina uspjesna! Cijena: " << odabranaNekretnina.cijena << " KM." << endl;

            // Generiranje ugovora i računa te ispis korisniku
            generisiUgovorIRacun(odabranaNekretnina, kupac);

            // Ispisivanje ugovora i računa korisniku
            ispisiUgovorIRacun();


            break;
        }
    }

    return 0;
}


