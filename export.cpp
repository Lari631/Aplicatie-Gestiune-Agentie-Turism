#include "export.h"
#include "oferta.h"
#include <fstream>
#include <string>
#include <vector>
#include "repo.h"
using std::vector;


void export_to_csv(const string& file_name, const vector<Oferta> &oferte){
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