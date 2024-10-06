#pragma once
#include "oferta.h"
#include "vector_dinamic.h"
#include <vector>
using std::vector;
using std::string;
using std::move;

class RepoException : public std::exception{
    std::string mesaj;
public:
    explicit RepoException(string msj): mesaj{std::move(msj)}{

    }
    string get_mesaj(){
        return mesaj;
    }
};

class Repo{
private:
    vector <Oferta> oferte;

public:
    Repo (const Repo& r)=delete; // repo nu se poate copia -> copy constructorul este distrus automat
    Repo()=default;

    virtual void adauga_oferta(const Oferta &oferta); //override la functie in file_repo care mosteneste de aici
    virtual void sterge_oferta(const Oferta &oferta);
    bool cautare_noua(const Oferta &oferta);
    virtual void modifica_oferta(Oferta &oferta_initiala, Oferta &oferta_noua);
    bool cautare_oferta(Oferta oferta);
    int get_pozitie(const Oferta &oferta);
    Oferta cauta_denumire(string denumire);
    const vector <Oferta>& get_all_oferte();

};

class FileRepo: public Repo{
private:
    string file_name;
    void load_from_file();
    void write_to_file();
public:

    //functia pune in vectorul din repo datele din fisier
    FileRepo(string file_name): Repo(),file_name{file_name}{
        load_from_file(); // incarcarea datelor in fisier se face imediat
    }
    void adauga_oferta(const Oferta& p) override {
        Repo::adauga_oferta(p);//apelam metoda din clasa de baza
        write_to_file();
    }
    void sterge_oferta(const Oferta& p) override{
        Repo::sterge_oferta(p);//apelam metoda din clasa de baza
        write_to_file();
    }

    void modifica_oferta(Oferta &oferta_initiala, Oferta &oferta_noua) override{
        Repo::modifica_oferta(oferta_initiala,oferta_noua);
        write_to_file();
    }

};