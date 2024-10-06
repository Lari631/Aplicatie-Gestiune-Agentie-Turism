#pragma once
#include <vector>
#include "oferta.h"
#include "observer.h"

using std::vector;

class Wishlist{
    vector<Oferta> list;

public:
    Wishlist() =default;
    void adauga_wishlist(const Oferta &oferta);
    void goleste_wishlist();
    void genereaza_wishlist(int capacitate,vector<Oferta> oferte);

    vector <Oferta> get_wishlist();
};

