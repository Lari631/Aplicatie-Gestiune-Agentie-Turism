#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include "wishlist.h"
#include "service.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>

class WishlistGui:public QWidget, public Observer{
    //friend class Service;
private:
    QVBoxLayout *layout=new QVBoxLayout;
    //QListWidget *lista=new QListWidget;

    QTableWidget *tabel=new QTableWidget;

    QPushButton *add= new QPushButton{"Add"};
    QPushButton *empty= new QPushButton{"Empty"};
    QPushButton *generate = new QPushButton{"Generate"};
    QHBoxLayout *butoane = new QHBoxLayout{};

    QLineEdit *denumire = new QLineEdit;
    QLineEdit *destinatie = new QLineEdit;
    QLineEdit *cantitate= new QLineEdit;

    Wishlist &wishlist;
    Service &service;
    void init_wishlist();
    void load_data(vector<Oferta> oferte);
    void init_connections();
    //void refresh();
    void update() override;


public:
    WishlistGui(Wishlist &wishlist,Service &service): wishlist{wishlist},service{service}{
            init_wishlist();
            service.add_observer(this);
            init_connections();
            //refresh();
            load_data(wishlist.get_wishlist());
        }
};