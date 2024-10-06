#include "service.h"
#include <algorithm>
#include <fstream>
#include <assert.h>

void Service::add_oferta(string denumire, string destinatie, string tip, double pret) //inainte nu aveam &
{
    Oferta oferta{denumire,destinatie,tip,pret};
    repository.adauga_oferta(oferta);
    undo_actions.push_back(std::make_unique<UndoAdauga>(repository,oferta));
}

void Service::delete_oferta(std::string denumire, std::string destinatie, std::string tip, double pret) {
    Oferta oferta{denumire,destinatie,tip,pret};
    repository.sterge_oferta(oferta);
    undo_actions.push_back(std::make_unique<UndoSterge>(repository,oferta));
}

bool Service::find_oferta_nou(std::string denumire, std::string destinatie, std::string tip, double pret) {
    Oferta oferta{denumire,destinatie,tip,pret};
    return repository.cautare_oferta(oferta);
}

void Service::modify_oferta(string den1, string dest1, string tip1, double p1, string den2, string dest2, string tip2, double p2){
    Oferta oferta_initiala{den1,dest1,tip1,p1};
    Oferta oferta_noua{den2,dest2,tip2,p2};
    repository.modifica_oferta(oferta_initiala,oferta_noua);
    undo_actions.push_back(std::make_unique<UndoModifica>(repository,oferta_initiala,oferta_noua));
}

vector<Oferta> Service::filtrare_dupa_destinatie(string destinatie){
    vector<Oferta> oferte_filtrate;
    vector<Oferta> oferte=repository.get_all_oferte();
    copy_if(oferte.begin(),oferte.end(),std::back_inserter(oferte_filtrate), [&](const Oferta &o){
        return o.get_destinatie()==destinatie;
    });
    return oferte_filtrate;
}

vector<Oferta> Service::filtrare_dupa_denumire(std::string denumire) {
    vector <Oferta> oferte_filtrate;
    vector <Oferta> oferte=get_all();
    copy_if(oferte.begin(),oferte.end(),std::back_inserter(oferte_filtrate),[&](const Oferta &o){
        return o.get_denumire()==denumire;
    });
    return oferte_filtrate;
}

vector<Oferta> Service::filtrare_dupa_tip(std::string tip) {
    vector <Oferta> oferte_filtrate;
    vector<Oferta> oferte= get_all();
    copy_if(oferte.begin(),oferte.end(),std::back_inserter(oferte_filtrate),[&](const Oferta &o){
        return o.get_tip()==tip;
    });
    return oferte_filtrate;
}

vector<Oferta> Service::filtrare_dupa_pret(double pret){
    vector<Oferta> oferte_filtrate;
    vector<Oferta> oferte=get_all();
    copy_if(oferte.begin(),oferte.end(),std::back_inserter(oferte_filtrate),[&](const Oferta &o){
       return o.get_pret()<pret;
    });
    return oferte_filtrate;
}


vector<Oferta> Service::ordonare_dupa_pret() {
    vector<Oferta> oferte=repository.get_all_oferte();
    sort(oferte.begin(),oferte.end(), [&](const Oferta &oferta1, const Oferta &oferta2){
        return oferta1.get_pret()<oferta2.get_pret();
    });
    return oferte;
}

vector<Oferta> Service::ordonare_dupa_denumire(){
    vector <Oferta> oferte=get_all();
    sort(oferte.begin(),oferte.end(),[&](const Oferta &o1, const Oferta &o2){
        return o1.get_denumire()<o2.get_denumire();
    });
    return oferte;
}

vector<Oferta> Service::ordonare_dupa_destinatie(){
    vector <Oferta> oferte=get_all();
    sort(oferte.begin(),oferte.end(),[&](const Oferta &o1, const Oferta &o2){
        return o1.get_destinatie()<o2.get_destinatie();
    });
    return oferte;

}

vector<Oferta> Service::ordonare_dupa_tip(){
    vector <Oferta> oferte=get_all();
    sort(oferte.begin(),oferte.end(),[&](const Oferta &o1, const Oferta &o2){
        return o1.get_tip()<o2.get_tip();
    });
    return oferte;

}

vector<Oferta> Service::get_all() {
    return repository.get_all_oferte();
}

Oferta Service::cauta_dupa_denumire(string denumire){
    return repository.cauta_denumire(denumire);
}

void Service::undo(){
    if(undo_actions.empty())
    {
        throw RepoException{"nu se mai poate face undo:("};
    }
    undo_actions.back()->doUndo(); //.back ia ultimul element (cel mai recent adaugat) si face apel polimorfic la doUndo
    //se apeleaza metoda corespunzatoare pt doundo
    undo_actions.pop_back(); //elimin ultima operatie din lista de undo, ca am facut-o
}

Oferta Service::cauta_dupa_denumire_si_destinatie(std::string denumire,string destinatie) {
    vector<Oferta> oferte=get_all();
    for(const auto &o:oferte){
        if(o.get_destinatie()==destinatie && o.get_denumire()==denumire)
            return o;
    }
    throw RepoException("nu exista oferta");
}

void Service::add_to_wishlist(string denumire,string destinatie){
    //cauta oferta cu denumire
    try{
        Oferta oferta = cauta_dupa_denumire_si_destinatie(denumire,destinatie);
        wishlist.adauga_wishlist(oferta);
        notify();
    }
   catch(RepoException &re){
        throw ServiceException("oferta inexistenta");
   }

}

void Service::adauga_wishlist(Oferta &o) {
    wishlist.adauga_wishlist(o);
    notify();
}

void Service::empty_wishlist(){
    wishlist.goleste_wishlist();
    notify();
}

void Service::generare_wishlist(int capacitate){
    vector <Oferta> oferte=get_all();
    wishlist.genereaza_wishlist(capacitate,oferte);
    notify();
}

vector<Oferta> Service::get_elemente_wishlist(){
    return wishlist.get_wishlist();
}

int Service::nr_linii()
{
    int count=0;
    vector<Oferta> oferte=get_elemente_wishlist();
    for(const auto &o:oferte)
        count++;
    return count;
}

void export_to_csv_1(const string& file_name, const vector<Oferta> &oferte){
    std::ofstream out(file_name, std::ios::trunc); // daca fisierul nu exista, este creat; daca exista, se sterge continutul
    if (!out.is_open()) {
        throw RepoException("Unable to open file:" + file_name);
    }
    for(const auto &o: oferte){
        out<<o.get_denumire()<<",";
        out<<o.get_destinatie()<<",";
        out<<o.get_tip()<<",";
        out<<o.get_pret()<<"\n";
    }
    out.close();
}

void Service::salvare_in_fisier(string &nume_fisier){
    vector<Oferta> oferte=get_all();
    export_to_csv_1(nume_fisier, oferte);
}

void Service::export_fisier(string &nume_fisier){
    vector<Oferta> oferte= get_elemente_wishlist();
    export_to_csv_1(nume_fisier,oferte);
}

map <string,int> Service::frecventa_tipuri() {
    map <string,int> dictionar;
    vector<Oferta> oferte=get_all();
    //initializare valori din dictionar cu 0
    for(const Oferta &o:oferte){
        string tip=o.get_tip();
        dictionar[tip]=0;
    }
    //actualizare valori din dictionar dupa frecventa aparitiei tipurilor
    for(const Oferta &o:oferte){
        string tip=o.get_tip();
        dictionar[tip]++;
    }
    return dictionar;
}

string Service::build_one_string(Oferta oferta){
    string new_string;
    new_string=oferta.get_denumire()+","+oferta.get_destinatie()+","+oferta.get_tip();
    return new_string;
}

string Service::build_string_list(vector<Oferta> oferte) {
    string text;
    for(const Oferta &o:oferte){
        text+= build_one_string(o)+"\n";
    }
    return text;
}

void Service::test_build_string(){
    Oferta oferta{"vacanta","denumire","tip",100};
    assert(build_one_string(oferta)=="vacanta,denumire,tip,100");
}

//functia returneaza true daca lista curenta are un element cu tipul precizat
bool Service::mai_exista_tipul(string type){
    vector<Oferta> oferte= get_all();
    for(const auto &o:oferte){
        if(o.get_tip()==type)
            return true;
    }
    return false;
}

Oferta Service::get_item(int index)
{
    return get_all()[index];
}