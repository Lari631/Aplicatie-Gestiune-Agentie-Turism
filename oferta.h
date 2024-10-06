#pragma once

#include <string>
#include <iostream>
#include <utility>

using std::string;
using std::cout;

class Oferta {
private:
    string denumire;
    string destinatie;
    string tip;
    double pret{};
public:
    [[nodiscard]] double get_pret() const;

    [[nodiscard]] string get_destinatie() const;

    [[nodiscard]] string get_tip() const;

    [[nodiscard]] string get_denumire() const;

    void set_pret(int pret_nou){
        pret=pret_nou;
    };
    void set_denumire(string denumire_noua){
        denumire=denumire_noua;
    };
    void set_tip(string tip_nou){
        tip=tip_nou;
    };
    void set_destinatie(string destinatie_noua){
        destinatie=destinatie_noua;
    };

    Oferta()=default;
    //explicit Oferta(const string& denumire="",const string& destinatie="",const string& tip="",int pret=0){}
    Oferta(string denum, string dest, string tip, double pr) : denumire{std::move(denum)}, destinatie{std::move(dest)},
                                                               tip{std::move(tip)}, pret{pr} {}

    Oferta(const Oferta &other) {
        denumire = other.denumire;
        destinatie = other.destinatie;
        tip = other.tip;
        pret = other.pret;
        //cout << "copy constructing object\n";
    }

    ~Oferta() = default;

};