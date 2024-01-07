#include "Korisnik.h"

void Korisnik::prikazProfila(){
    std::cout<<"~ Prikaz profila ~\n";
    std::cout<<"\n   Podaci o korisniku: \n";

    std::string tip="";

    if(tipProfila=="1")tip="Vlasnik nekretnine";
    if(tipProfila=="2")tip="Kupac nekretnine";
    if(tipProfila=="3")tip="Iznajmljivac nekretnine";
    if(tipProfila=="4")tip="Radnik agencije";
    if(tipProfila=="5")tip="Odrzavatelj";

    std::cout << "      Korisnicko ime: " << korisnickoIme << "\n";
    std::cout << "      Tip profila: " << tip << "\n";
    std::cout << "      Ime: " << ime << "\n";
    std::cout << "      Prezime: " << prezime << "\n";
    std::cout << "      Broj telefona: " << brojTelefona << "\n";
    std::cout << "      E-mail adresa: " << emailAdresa << "\n";

    //prikaz informacija o transakacijama
}
