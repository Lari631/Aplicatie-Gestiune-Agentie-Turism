#pragma once
#include <string>
#include "repo.h"
#include "wishlist.h"
#include <map>
#include <memory>
#include "ActiuneUndo.h"

using std::string;
using std::map;
using std::unique_ptr;

class ServiceException:public std::exception{
private:
    string mesaj;
public:
    ServiceException(string mesaj):mesaj{mesaj}{};
    string get_mesaj(){
        return mesaj;
    }
};

class Service: public Observable{
private:
    //Repo& repository;
    FileRepo &repository;
    Wishlist wishlist;
    std::vector<unique_ptr<ActiuneUndo>> undo_actions;

public:
    explicit Service(FileRepo& repository): repository{repository}{};

    Service (const Service& r)=delete; // repo nu se poate copia
    Service()=default;

    void add_oferta(string denumire, string destinatie, string tip, double pret);
    void delete_oferta(string denumire, string destinatie, string tip, double pret);
    //bool find_oferta(string denumire, string destinatie, string tip, double pret);
    bool find_oferta_nou(string denumire, string destinatie, string tip, double pret);
    void modify_oferta(string den1, string dest1, string tip1, double p1, string den2, string dest2, string tip2, double p2);

    void undo();

    Oferta get_item(int index);
    Oferta cauta_dupa_denumire(string denumire);
    Oferta cauta_dupa_denumire_si_destinatie(string denumire, string destinatie);
    void add_to_wishlist(string denumire,string destinatie);
    void adauga_wishlist(Oferta &o);
    void empty_wishlist();
    void generare_wishlist(int capacitate);
    void salvare_in_fisier(string & nume_fisier); // functia salveaza TOATE ofertele in alt fisier
    void export_fisier(string &nume_fisier);
    int nr_linii();
    //calculeaza cate oferte sunt de fiecare tip
    map <string,int> frecventa_tipuri();
    vector<Oferta> get_elemente_wishlist();
    Wishlist& get_wishlist(){
        return wishlist;
    }

    vector<Oferta> filtrare_dupa_destinatie(string destinatie);
    vector<Oferta> filtrare_dupa_denumire(string denumire);
    vector <Oferta> filtrare_dupa_pret(double pret); // returneaza ofertele cu un pret mai mic sau egal cu pretul dat
    vector<Oferta> filtrare_dupa_tip(string tip);
    vector<Oferta> ordonare_dupa_pret();
    vector<Oferta> ordonare_dupa_destinatie();
    vector<Oferta> ordonare_dupa_denumire();
    vector<Oferta> ordonare_dupa_tip();
    vector <Oferta> get_all();

    string build_one_string(Oferta oferta);
    string build_string_list(vector<Oferta> oferte);
    void test_build_string();
    bool mai_exista_tipul(string type);

};