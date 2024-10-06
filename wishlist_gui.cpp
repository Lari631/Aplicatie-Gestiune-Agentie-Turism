//
// Created by A on 25/05/2024.
//
#include "observer.h"
#include "wishlist_gui.h"
#include <QListWidgetItem>
#include <QTimer>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>

void WishlistGui::init_wishlist(){
    //deschid fereastra noua, afisez ce am in cos(momentan nimic)
    setLayout(layout);

    //int nr=service.nr_linii();
    //QTableWidget *tabel= new QTableWidget{nr,4};
    //tabel->setRowCount(nr);
    //tabel->setColumnCount(4);

    QFormLayout *campuri= new QFormLayout;
    campuri->addRow("Denumire:",denumire);
    campuri->addRow("Destinatie:",destinatie);
    campuri->addRow("Cantitate",cantitate);

    QLabel *title=new QLabel{"Wishlist:"};
    layout->addWidget(title);

    layout->addLayout(campuri);
    layout->addLayout(butoane);
    //layout->addWidget(lista);

    layout->addWidget(tabel);

    butoane->addWidget(add);
    butoane->addWidget(empty);
    butoane->addWidget(generate);

}

void WishlistGui::load_data(vector<Oferta> oferte) {
    //lista->clear();
    tabel->clear();
    int nr=service.nr_linii();
    tabel->setRowCount(nr);
    tabel->setColumnCount(4);
    int linie=-1;
    for(const auto &o:oferte){
        linie++;
        //afisez ofertele din cos cu tot cu pret data asta
        string pret=std::to_string(o.get_pret());
        string text=o.get_denumire()+", "+o.get_destinatie()+", "+o.get_tip()+", "+pret;
        //QListWidgetItem *item=new QListWidgetItem(QString::fromStdString(text));
        //lista->addItem(item);
        QTableWidgetItem *den =  new QTableWidgetItem(QString::fromStdString(o.get_denumire()));
        tabel->setItem(linie,0,den);
        QTableWidgetItem *dest =  new QTableWidgetItem(QString::fromStdString(o.get_destinatie()));
        tabel->setItem(linie,1,dest);
        QTableWidgetItem *tip =  new QTableWidgetItem(QString::fromStdString(o.get_tip()));
        tabel->setItem(linie,2,tip);
        QString p=QString::number(o.get_pret());
        QTableWidgetItem *pr =  new QTableWidgetItem(p);
        tabel->setItem(linie,3,pr);

    }
}

void WishlistGui::init_connections()
{
    QObject::connect(add, &QPushButton::clicked, [&](){
        //iau textul din qlineedit
        string den=denumire->text().toStdString();
        string dest=destinatie->text().toStdString();
        //apelez functia service de adaugare dupa nume si destinatie, care va da si notify
        try{
            service.add_to_wishlist(den,dest);
        }
        catch(ServiceException &re){
            QMessageBox::warning(this,"Warning",QString::fromStdString(re.get_mesaj()));
        }
    });

    QObject::connect(empty,&QPushButton::clicked,[&](){
        service.empty_wishlist();
    });

    QObject::connect(generate,&QPushButton::clicked,[&](){
        int cant=cantitate->text().toInt();
        service.generare_wishlist(cant);
    });
}

/*
void WishlistGui::refresh(){
    QTimer* refreshTimer = new QTimer;
    QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
        load_data(wishlist.get_wishlist());
    });
    refreshTimer->start(1000);

}*/

//metoda apelata de fiecare data cand se schimba ceva in wishlist
void WishlistGui::update()
{
    load_data(wishlist.get_wishlist());
}

