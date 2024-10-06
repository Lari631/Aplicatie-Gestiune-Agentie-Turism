#include "repo.h"
#include "vector_dinamic.h"
#include <bits/stdc++.h>
#include <fstream>

bool sunt_egale(const Oferta &oferta1, const Oferta &oferta2){
    if(oferta1.get_destinatie()==oferta2.get_destinatie() && oferta1.get_tip()==oferta2.get_tip() && oferta1.get_denumire()==oferta2.get_denumire() &&oferta1.get_pret()==oferta2.get_pret())
        return true;
    return false;
}

void Repo::adauga_oferta(const Oferta &oferta){
    auto it=std::find_if(oferte.begin(),oferte.end(),[&](const Oferta &o){
        return sunt_egale(oferta,o);
    });
    if (it != oferte.end()) {
        throw RepoException("Oferta deja existenta!\n");
    }
    oferte.push_back(oferta);
}

void Repo::sterge_oferta(const Oferta &oferta) {
    if(!(cautare_noua(oferta)))
        throw RepoException("oferta inexistenta!\n");
    auto new_end=std::remove_if(oferte.begin(), oferte.end(),[&](const Oferta &o){
        return sunt_egale(oferta,o);
    }); // muta elementele de sters la final
    oferte.erase(new_end, oferte.end()); // sterge elementele de la primul care trebe sters pana la final
}

int Repo::get_pozitie(const Oferta &oferta){
    auto it=std::find_if(oferte.begin(), oferte.end(),[&](const Oferta &o){
        return sunt_egale(oferta,o);
    });
    if (it != oferte.end()) {
        // Calculate the index of the matching oferta
        return std::distance(oferte.begin(), it);
    }
    else throw RepoException("oferta inexistenta!\n");
}

void Repo::modifica_oferta(Oferta &oferta_initiala, Oferta &oferta_noua) {
    if(!cautare_oferta(oferta_initiala)){
        throw RepoException("oferta inexistenta!\n");
    }
    else{
        int poz= get_pozitie(oferta_initiala);
        oferte[poz]=oferta_noua;
    }
}

//verific daca oferta exista in vectorul de oferte
bool Repo::cautare_oferta(Oferta oferta){
    for(auto &o:oferte){
        if(o.get_denumire()==oferta.get_denumire()&&o.get_destinatie()==oferta.get_destinatie()&&o.get_tip()==oferta.get_tip()&&o.get_pret()==oferta.get_pret())
            return true;
    }
    return false;
}

///!grijaaaa ca NU MERGE
bool Repo::cautare_noua(const Oferta &oferta){
    auto foundIt = std::find_if(oferte.begin(), oferte.end(), [&](const Oferta& o) {
        return sunt_egale(o, oferta);
    }); // e nevoie de & ca functia lambda sa aiba acces si la variabile din afara ei ( oferta )
    // variabila oferta nu ar fi captured de lambda fara &
    // [] = capture list
    return foundIt != oferte.end(); // foundit == oferte.end inseamna ca nu am gasit elementul
}

Oferta Repo::cauta_denumire(string denumire){
    auto gasit=std::find_if(oferte.begin(),oferte.end(),[&](const Oferta &o){
        return o.get_denumire()==denumire;
    });
    if(gasit==oferte.end()) // nu exista elementul
        throw RepoException("oferta inexistenta!\n");
    else return *gasit;
}

const vector<Oferta>& Repo::get_all_oferte() {
    return oferte;
}

void FileRepo::load_from_file() {
    std::ifstream in(file_name);
    if(!in.is_open()){
        throw RepoException("nu se poate deschide fisierul :(\n");
    }
    while(!in.eof()){
        //citesc atributele
        string denumire,destinatie,tip;
        double pret;
        in>>denumire;
        in>>destinatie;
        in>>tip;
        in>>pret;
        //alcatuiesc oferta
        if(!denumire.empty())
        {
            Oferta oferta{denumire,destinatie,tip,pret};
            //adaug oferta folosind functia din repo
            Repo::adauga_oferta(oferta);
        }
    }
    //inchidere fisier
    in.close();
}

void FileRepo::write_to_file() {
    std::ofstream out(file_name);
    if (!out.is_open()) { //verify if the stream is opened
        throw RepoException("Unable to open file:");
    }
    for (auto& p:get_all_oferte()) {
        out << p.get_denumire();
        out << std::endl;
        out << p.get_destinatie();
        out << std::endl;
        out << p.get_tip();
        out << std::endl;
        out<<p.get_pret();
        out<<std::endl;
    }
    out.close();
}




