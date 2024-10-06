#pragma once

#include <vector>
#include "oferta.h"

template <typename Element>
class Iterator;

template <typename Element>
class VectorDinamic{
private:
    int capacitate,lungime;
    Element *elems;
public:

    VectorDinamic();
    //Rule of 3
    //constructor copiere
    VectorDinamic(const VectorDinamic &other);
    //operator assignment
    VectorDinamic& operator=(const VectorDinamic &other);
    //destructor
    ~VectorDinamic();

    //move constructor
    //apelat daca se construieste vector nou, de ex expresie la returnare
    VectorDinamic(VectorDinamic&& other);

    //move assignment
    //folosit la assignment
    VectorDinamic& operator=(VectorDinamic&& other);

    void add(const Element &oferta);

    void del(const Element& oferta);

    void search(const Element &oferta);

    int get_poz(const Element &oferta);

    void update(const Element &oferta, int poz);

    Element& get_oferta(int poz) const;

    void set_oferta(int poz, const Element &oferta);

    int get_size() const;

    friend class Iterator<Element>;
    //functii care creaza iteratori
    Iterator<Element> begin();
    Iterator<Element> end();

};

template <typename Element>
class Iterator{
private:
    const VectorDinamic<Element>& v;
    int poz=0;
public:
    Iterator<Element>(const VectorDinamic<Element>& v) noexcept;
    Iterator<Element>(const VectorDinamic<Element>& v, int poz)noexcept;
    bool valid()const noexcept;
    Element& element() const noexcept;
    void next() noexcept;
    Element& operator*();
    Iterator<Element>& operator++();
    bool operator==(const Iterator& ot)noexcept;
    bool operator!=(const Iterator& ot)noexcept;

};

template <typename Element>
VectorDinamic<Element>::~VectorDinamic(){
    delete[] elems;
}

//constructor default
template <typename Element>
VectorDinamic<Element>::VectorDinamic():capacitate{10},lungime{0},elems{new Oferta[capacitate]}{

}
//constructor copiere
template <typename Element>
VectorDinamic<Element>::VectorDinamic(const VectorDinamic &other){
    elems = new Oferta[other.capacitate];
    //copiez elementele
    for (int i = 0; i < other.lungime; i++) {
        elems[i] = other.elems[i];
    }
    lungime = other.lungime;
    capacitate = other.capacitate;
}

//operator assignment
template <typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(const VectorDinamic &other){
    if (this == &other) {
        return *this;//s-a facut l=l;
    }
    delete []elems;
    elems=new Oferta[other.capacitate];
    for(int i=0;i<other.lungime;i++)
    {
        elems[i]=other.elems[i];
    }
    lungime=other.lungime;
    capacitate=other.capacitate;
    return *this;
}

//destructor


//adaugare element in vector
template <typename Element>
void VectorDinamic<Element>::add(const Element &oferta){
    if(capacitate==lungime){
        Oferta* aux=new Oferta[capacitate*2];
        for(int i=0;i<lungime;i++)
            aux[i]=elems[i];
        delete[] elems;
        elems = aux;
        capacitate=capacitate*2;
    }
    elems[lungime++]=oferta;

}

template <typename Element>
int VectorDinamic<Element>::get_poz(const Element &oferta) {
    for(int i=0; i<lungime; i++)
    {
        Element &o=elems[i];
        if(oferta.get_destinatie()==o.get_destinatie() && oferta.get_tip()==o.get_tip() && oferta.get_denumire()==o.get_denumire() &&oferta.get_pret()==o.get_pret())
            return i;
    }
    return -1;
}

template <typename Element>
void VectorDinamic<Element>::del(const Element& oferta){
    int poz = get_poz(oferta);
    for (int i = poz; i < this->lungime - 1; i++)
        this->elems[i] = this->elems[i + 1];
    this->lungime--;
}

//move constructor
//obiectul other nu se mai foloseste, astfel ca se poate refolosi interiorul lui
template <typename Element>
VectorDinamic<Element>::VectorDinamic(VectorDinamic&& other) {
    elems=other.elems;
    lungime = other.lungime;
    capacitate = other.capacitate;

    other.elems = nullptr;
    other.lungime=0;
    other.capacitate=0;
}

//move assignment
//elibereaza ce contine this si ia continutul lui other
//pregateste other pentru distrugere
template <typename Element>
VectorDinamic<Element>& VectorDinamic<Element>::operator=(VectorDinamic &&other){
    if(this==&other)
    {
        return *this;
    }
    delete[] elems;
    elems=other.elems;
    lungime = other.lungime;
    capacitate = other.capacitate;

    other.elems = nullptr;
    other.lungime=0;
    other.capacitate=0;
    return *this;
}

template <typename Element>
Element& VectorDinamic<Element>::get_oferta(int poz) const{
    return elems[poz];
}

template <typename Element>
void VectorDinamic<Element>::set_oferta(int poz, const Element& oferta){
    elems[poz]=oferta; // cealalta oferta nu cred ca s a sters
}

template <typename Element>
int VectorDinamic<Element>::get_size() const {
    return lungime;
}

template <typename Element>
Iterator<Element> VectorDinamic<Element>::begin(){
    return Iterator(*this);
}

template <typename Element>
Iterator<Element> VectorDinamic<Element>::end(){
    return Iterator(*this,lungime);
}

template <typename Element>
Iterator<Element>::Iterator(const VectorDinamic<Element> &v) noexcept:v{v} {}
template <typename Element>
Iterator<Element>::Iterator(const VectorDinamic<Element> &v, int poz) noexcept:v {v},poz{poz}{}

template <typename Element>
bool Iterator<Element>::valid() const noexcept{
    return poz<v.lungime;
}

template <typename Element>
Element& Iterator<Element>::element() const noexcept{
    return v.elems[poz];
}

template <typename Element>
void Iterator<Element>::next() noexcept{
    poz++;
}

template <typename Element>
Element& Iterator<Element>::operator*(){
    return element();
}

template <typename Element>
Iterator<Element>& Iterator<Element>::operator++(){
    next();
    return *this;
}

template <typename Element>
bool Iterator<Element>::operator==(const Iterator& other) noexcept{
    return poz==other.poz;
}

template <typename Element>
bool Iterator<Element>::operator!=(const Iterator& other) noexcept{

    return !(*this==other);
}