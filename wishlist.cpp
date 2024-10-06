#include "wishlist.h"
#include <algorithm>
#include <random>

void Wishlist::adauga_wishlist(const Oferta &oferta) {
    list.push_back(oferta);
}

void Wishlist::goleste_wishlist() {
    list.clear();
}

void Wishlist::genereaza_wishlist(int capacitate, vector<Oferta> oferte) {
    std::shuffle(oferte.begin(),oferte.end(),std::default_random_engine(std::random_device{}()));
    // s-a schimbat ordinea elementelor din "oferte" (shuffle)
    // acum se adauga elementele din oferte in lista;
    while(list.size()<capacitate && oferte.size()>0){
        list.push_back(oferte.back()); // adaug element in lista
        oferte.pop_back(); // il sterg din oferte
    }
}

vector<Oferta> Wishlist::get_wishlist(){
    return list;
}