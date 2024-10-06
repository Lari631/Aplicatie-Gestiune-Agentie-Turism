#pragma once
#include "oferta.h"
#include <vector>
using std::vector;

class RepoAbstract{
private:
    vector <Oferta> oferte;

public:
    RepoAbstract (const RepoAbstract& r)=delete; // repo nu se poate copia -> copy constructorul este distrus automat
    RepoAbstract()=default;

    virtual void adauga_oferta(const Oferta &oferta);
    virtual void sterge_oferta(const Oferta &oferta);
    virtual bool cautare_noua(const Oferta &oferta);
    virtual void modifica_oferta(Oferta &oferta_initiala, Oferta &oferta_noua);
    virtual int get_pozitie(const Oferta &oferta);
    virtual Oferta cauta_denumire(string denumire);
    virtual const vector <Oferta>& get_all_oferte();

};