#pragma once
#include "repo.h"

class ActiuneUndo{
public:
    virtual void doUndo()=0; // functie pur virtuala, TREBUIE sa fie overriden; nu are implementare separat de claseele derivate
    virtual ~ActiuneUndo()=default;
};

class UndoAdauga: public ActiuneUndo{
private:
    Oferta oferta_adaugata;
    FileRepo &repo;
public:
    UndoAdauga(FileRepo &repo, const Oferta&oferta_adaugata):repo{repo},oferta_adaugata{oferta_adaugata}{}

    void doUndo() override{
        repo.sterge_oferta(oferta_adaugata);
    }
};

class UndoSterge: public ActiuneUndo{
private:
    Oferta oferta_stearsa;
    FileRepo &repo;
public:
    UndoSterge(FileRepo &repo, const Oferta &oferta_stearsa):repo{repo},oferta_stearsa{oferta_stearsa}{}
    void doUndo() override{
        repo.adauga_oferta(oferta_stearsa);
    }
};

class UndoModifica: public ActiuneUndo{
private:
    Oferta oferta_veche,oferta_noua;
    FileRepo &repo;

public:
    UndoModifica(FileRepo &repo, const Oferta &oferta_veche, const Oferta &oferta_noua):repo{repo},oferta_veche{oferta_veche},oferta_noua{oferta_noua}{}
    void doUndo() override{
        repo.modifica_oferta(oferta_veche,oferta_noua);
    }
};