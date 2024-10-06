#pragma once
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include "MyTableModel.h"

class GUI: public QWidget{
public:
    Service &service;
    GUI(Service &service): service{service}{
        init_gui();
        load_data(service.get_all());
        adauga_butoane(service.get_all());
        init_connect();
    }

private:
    //QListWidget *lista= new QListWidget;
    //QListView *list_view = new QListView;
    QTableView *table_view= new QTableView;
    MyTableModel *table_model;

    QPushButton *exit= new QPushButton{"Exit"};
    QPushButton *adauga= new QPushButton{"Adauga"};
    QPushButton *sterge= new QPushButton{"Sterge"};
    QPushButton *modifica=new QPushButton{"Modifica"};
    QPushButton *ord_dest=new QPushButton{"Ordonare_destinatie"};
    QPushButton *ord_nume=new QPushButton{"Ordonare_nume"};
    QPushButton *ord_tip=new QPushButton{"Ordonare_tip"};
    QPushButton *ord_pret=new QPushButton{"Ordonare_pret"};
    QPushButton *filt_nume= new QPushButton{"Filtrare_nume"};
    QPushButton *filt_pret=new QPushButton{"Filtrare_pret"};
    QPushButton *filt_dest=new QPushButton{"Filtrare_destinatie"};
    QPushButton *filt_tip=new QPushButton{"Filtrare_tip"};
    QPushButton *nou_wishlist = new QPushButton{"Nou_wishlist"};
    //QPushButton *add_wishlist=new QPushButton{"Adauga_in_wishlist"};
    //QPushButton *empty_wishlist=new QPushButton{"Goleste_wishlist"};
    //QPushButton *gen_wishlist = new QPushButton{"Generate wishlist"};
    QPushButton *desen=new QPushButton{"Desen"};

    QLineEdit *denumire= new QLineEdit;
    QLineEdit *destinatie= new QLineEdit;
    QLineEdit *tip= new QLineEdit;
    QLineEdit *pret= new QLineEdit;

    QWidget *butoane_dinamice= new QWidget;
    QVBoxLayout *layout_din=new QVBoxLayout{};
    QHBoxLayout *main_layout=new QHBoxLayout{};

    vector<QPushButton*> vector_butoane;

    void reload_table();
    void init_gui();
    void load_data(const vector<Oferta>& oferte);
    void init_connect();
    void adauga_butoane(const vector<Oferta> &oferte);
    void sterge_buton(string type); // functia sterge butonul cu un tip, daca am sters toate elementele care au acel tip
};