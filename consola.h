#pragma once
#include "service.h"

class UI{
private:
    Service& service;
public:
    explicit UI(Service &srv): service{srv}{}
    void start_ui();
    void afisare_oferte();
    void afisare_wishlist();
    void afisare_nr_elem_cos();
};