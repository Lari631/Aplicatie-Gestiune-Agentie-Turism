#pragma once
#include "vector_dinamic.h"
#include <assert.h>

void test_add_del_repo();

void test_add_del_srv();

void test_find_modifica();

void run_teste();

template <typename Element>
void testAll();

/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/

template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
    double totalPrice = 0;
    for (auto el : v) {
        totalPrice += el.get_pret();
    }
    Oferta p{ "total","tt","j",totalPrice };
    v.add(p);
    return v;
}

template <typename MyVector>
void addPets(MyVector& v, int cate) {
    for (int i = 0; i<cate; i++) {
        Oferta p{ std::to_string(i) + "_denumire",std::to_string(i) + "_destinatie",std::to_string(i) + "_tip",i + 10.0 };
        v.add(p);
    }
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
    MyVector v;//default constructor
    addPets(v, 100);
    assert(v.get_size() == 100);
    assert(v.get_oferta(50).get_tip() == "50_tip");

    MyVector v2{ v };//constructor de copiere
    assert(v2.get_size() == 100);
    assert(v2.get_oferta(50).get_tip() == "50_tip");

    MyVector v3;//default constructor
    v3 = v;//operator=   assignment
    assert(v3.get_size() == 100);
    assert(v3.get_oferta(50).get_tip() == "50_tip");

    auto v4 = testCopyIterate(v3);
    assert(v4.get_size() == 101);
    assert(v4.get_oferta(50).get_tip() == "50_tip");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
    std::vector<MyVector> v;
    //adaugam un vector care este o variabila temporara
    //se v-a apela move constructor
    v.push_back(MyVector{});

    //inseram, la fel se apeleaza move costructor de la vectorul nostru
    v.insert(v.begin(),MyVector{});

    assert(v.size() == 2);

    MyVector v2;
    addPets(v2, 50);

    v2 = MyVector{};//move assignment

    assert(v2.get_size() == 0);

}

template <typename MyVector>
void testAll() {
    testCreateCopyAssign<MyVector>();
    testMoveConstrAssgnment<MyVector>();
}

