#include "teste.h"
#include "repo.h"
#include "service.h"
#include <assert.h>
#include <stdlib.h>
#include "vector_dinamic.h"
#include <vector>



void test_add_del_repo()
{
    //sigur nu ma gasesti aici
    Repo repository;
    Oferta oferta1{"Vacanta","Londra","City-Break",1000};
    Oferta oferta2{"a","b","c",1};
    Oferta oferta3{"s","a","a",9};
    repository.adauga_oferta(oferta1);
    repository.adauga_oferta(oferta2);
    assert(repository.get_all_oferte().size()==2);
    try{
        repository.adauga_oferta(oferta1);
        assert(false);
    }
    catch(RepoException &ex)
    {
        assert(true);
        assert(ex.get_mesaj()=="Oferta deja existenta!\n");
    }
    repository.sterge_oferta(oferta1);
    assert(repository.get_all_oferte().size()==1);
    try {
        repository.sterge_oferta(oferta3);
    }
    catch(RepoException &ex)
    {
        assert(true);
        assert(ex.get_mesaj()=="oferta inexistenta!\n");
    }
    try{
        repository.adauga_oferta(oferta2);
        //assert(false);
    }
    catch(RepoException &ex)
    {
        assert(true);
        assert(ex.get_mesaj()=="Oferta deja existenta!\n");
    }
}

void test_add_del_srv()
{
    //Repo repository;
    FileRepo filerepo("oferte.txt");
    Service srv(filerepo);
    //srv.add_oferta("Vacanta","Londra","City-Break",1000);
    //assert(srv.get_all().size()==4);
    srv.add_oferta("a","b","c",10);
    assert(srv.get_all().size()==4);
    srv.delete_oferta("a","b","c",10);
    assert(srv.get_all().size()==3);

}

void test_nou_find_modifica()
{
    //Repo repository;
    FileRepo filerepo("oferte.txt");
    Service srv(filerepo);
    //srv.add_oferta("Vacanta","Londra","City-Break",1000);
    assert(srv.find_oferta_nou("Vacanta","Londra","City-Break",2000)==true);
    assert(srv.find_oferta_nou("Va","Londra","City-Break",1000)==false);
    srv.modify_oferta("Vacanta","Londra","City-Break",2000,"Excursie","Lapusel","camping",500);
    //assert(srv.get_all().size()==1);
    assert(srv.get_all()[0].get_pret()==500);
    assert(srv.get_all()[0].get_destinatie()=="Lapusel");
    Oferta oferta1=srv.cauta_dupa_denumire("Excursie");
    assert(oferta1.get_denumire()=="Excursie");
    assert(oferta1.get_destinatie()=="Lapusel");
    try{
        srv.cauta_dupa_denumire("blablabla");
        assert(false);
    }
    catch (RepoException &re){
        assert(re.get_mesaj()=="oferta inexistenta!\n");
    }
    //srv.modify_oferta("Excursie","Lapusel","camping",500,"Vacanta","Londra","City-Break",2000);
}

void test_wishlist()
{
    //Repo repository;
    FileRepo filerepo("oferte.txt");
    Service srv(filerepo);
    srv.add_oferta("Vacanta","Londra","City-Break",1000);
    srv.add_oferta("Excursie","B","d",300);
    //srv.add_to_wishlist("Vacanta");
    vector <Oferta>wishlist= srv.get_elemente_wishlist();
    assert(wishlist[0].get_denumire()=="Vacanta");
    assert(wishlist[0].get_destinatie()=="Londra");
    assert(wishlist[0].get_pret()==1000);
    assert(wishlist[0].get_tip()=="City-Break");
    srv.empty_wishlist();
    assert(srv.get_elemente_wishlist().size() == 0);
}

void run_teste()
{
    test_add_del_repo(); //3 copii
    //test_add_del_srv(); //7 copii
    //test_nou_find_modifica();
    //test_wishlist();
}

