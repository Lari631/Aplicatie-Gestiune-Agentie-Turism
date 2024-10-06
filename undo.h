#pragma once
#include "oferta.h"
#include "repo.h"

class ActiuneUndo{
public:
    virtual void doUndo()=0;
    virtual ~ActiuneUndo()=default;
};

class UndoAdauga: public ActiuneUndo{
    Oferta oferta_adaugata;
    FileRepo& filerepo;
public:
    UndoAdauga(FileRepo& filerepo,const  Oferta& oferta_adaugata) :filerepo{ filerepo }, oferta_adaugata{ oferta_adaugata } {}

    void doUndo() override {
        filerepo.sterge_oferta(oferta_adaugata);
    }
};

class UndoSterge : public ActiuneUndo {
    Oferta oferta_stearsa;
    FileRepo& filerepo;
public:
    UndoSterge(FileRepo& filerepo, const  Oferta& oferta_stearsa) :filerepo{ filerepo }, oferta_stearsa{ oferta_stearsa } {}
    void doUndo() override {
        filerepo.adauga_oferta(oferta_stearsa);
    }
};

class UndoModifica: public ActiuneUndo{
    Oferta oferta_initiala,oferta_modificata;
    FileRepo &filerepo;
public:
    UndoModifica(FileRepo &filerepo,const Oferta&oferta_initiala, const Oferta &oferta_modificata):filerepo{filerepo},oferta_initiala{oferta_initiala},oferta_modificata{oferta_modificata}{}
    void doUndo() override{
        filerepo.sterge_oferta(oferta_initiala);
        filerepo.adauga_oferta(oferta_modificata);
    }
};