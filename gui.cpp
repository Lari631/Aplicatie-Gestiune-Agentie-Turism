//
// Created by A on 15/05/2024.
//

#include    "gui.h"
#include "wishlist_gui.h"
#include <sstream>
#include <string>
#include "desen.h"
#include <iostream>

using std::stringstream;
using std::getline;

void GUI::init_gui() {
    qDebug()<<"am ajuns aici\n";
    //QWidget stanga{};

    //QHBoxLayout *main_layout=new QHBoxLayout{};
    setLayout(main_layout);

    QHBoxLayout *ordonari=new QHBoxLayout{};
    QHBoxLayout *wishlist=new QHBoxLayout{};
    QHBoxLayout *buttons=new QHBoxLayout{};
    QHBoxLayout *filtrari=new QHBoxLayout{};

    //auto Lista = new MyTableModel(service.get_all());
    //table_view->setModel(Lista);
    //tv->show();
    table_view=new QTableView;
    table_model=new MyTableModel(service.get_all()); //modelul contine datele
    table_view->setModel(table_model); // view-ul ia datele din model

    QVBoxLayout *stanga=new QVBoxLayout{};
    //stanga->addWidget(lista);
    stanga->addWidget(table_view);
    ordonari->addWidget(ord_nume);
    ordonari->addWidget(ord_dest);
    ordonari->addWidget(ord_tip);
    ordonari->addWidget(ord_pret);
    stanga->addLayout(ordonari);
    //wishlist->addWidget(add_wishlist);
    //wishlist->addWidget(empty_wishlist);
    //wishlist->addWidget(gen_wishlist);
    wishlist->addWidget(nou_wishlist);
    wishlist->addWidget(desen);
    stanga->addLayout(wishlist);

    //lineedit
    QFormLayout *campuri= new QFormLayout{};
    campuri->addRow("Denumire",denumire);
    campuri->addRow("Destinatie", destinatie);
    campuri->addRow("Tip",tip);
    campuri->addRow("Pret", pret);

    //campuri+butoane -> vertical

    QVBoxLayout *dreapta = new QVBoxLayout{};
    dreapta->addLayout(campuri);
    dreapta->addLayout(buttons);

    //butoane
    buttons->addWidget(adauga);
    buttons->addWidget(sterge);
    buttons->addWidget(modifica);
    buttons->addWidget(exit);

    filtrari->addWidget(filt_nume);
    filtrari->addWidget(filt_dest);
    filtrari->addWidget(filt_tip);
    filtrari->addWidget(filt_pret);

    dreapta->addLayout(filtrari);

    main_layout->addLayout(stanga);
    main_layout->addLayout(dreapta);
    //this->show();
    //+butoane dinamice
    //layout_din->addWidget(butoane_dinamice);
    //main_layout->addLayout(layout_din);
   // main_layout->show();

};

void GUI::load_data(const vector<Oferta> &oferte){
    //lista->clear();
    /*
    for(const auto &oferta: oferte){
            auto denumire=QString::fromStdString(oferta.get_denumire());
            auto destinatie=QString::fromStdString(oferta.get_destinatie());
            auto tip=QString::fromStdString(oferta.get_tip());
            auto pret=oferta.get_pret();
            auto new_string=denumire+","+destinatie+","+tip;
            QListWidgetItem *item = new QListWidgetItem(new_string);
            item->setData(Qt::UserRole,pret);
            //item->setData(Qt::UserRole+1,destinatie);
            //item->setData(Qt::UserRole+2,tip);
            //item->setData(Qt::UserRole+3,pret);
            //lista->addItem(item);
        }*/
    table_model->set_oferte(oferte);
    //reload_table();
}

void GUI::init_connect(){
    QObject::connect(exit,&QPushButton::clicked,[&](){
        qDebug()<<"exit button apasat";
        QMessageBox::information(nullptr,"hopa","plecam");
        close();
    });
    QObject::connect(adauga,&QPushButton::clicked,[&](){
        qDebug()<<"se adauga...";
       auto den=denumire->text().toStdString();
       auto dest= destinatie->text().toStdString();
       auto t=tip->text().toStdString();
       auto p=pret->text().toDouble();
       try{
           service.add_oferta(den,dest,t,p);
       }
       catch(RepoException &re){
           QMessageBox::warning(this,"Warning",QString::fromStdString(re.get_mesaj()));
       }
       load_data(service.get_all());
      // reload_table();
       //qDebug()<<"am adaugat urmatorul element: nume: "<<den<<" dest: "<<dest<<" tip: "<<t<<" pret: "<<p;
    });
    QObject::connect(sterge,&QPushButton::clicked,[&](){
        auto den=denumire->text().toStdString();
        auto dest=destinatie->text().toStdString();
        auto t=tip->text().toStdString();
        auto p=pret->text().toDouble();
        service.delete_oferta(den,dest,t,p);
        //daca nu mai am elemente cu tipul dat, sterg butonul cu acel tip
        if(!service.mai_exista_tipul(t)){
            for(const auto &buton:vector_butoane){
                string nume_buton=buton->text().toStdString();
                if(nume_buton==t)
                    delete buton;
            }
        }
        load_data(service.get_all());
    });

    QObject::connect(modifica,&QPushButton::clicked,[&](){
        auto new_denumire=denumire->text().toStdString();
        auto new_destinatie=destinatie->text().toStdString();
        auto new_tip=tip->text().toStdString();
        auto new_pret=pret->text().toDouble();

            //auto selected_item=lista->selectedItems();
        QModelIndex index =table_view->selectionModel()->selectedIndexes()[0];
        //index va fi pozitia elementului in tabel; index.row() este efectiv al catelea e din vector
        //functie de get element dupa index
        Oferta oferta=service.get_item(index.row());
        service.modify_oferta(oferta.get_denumire(),oferta.get_destinatie(),oferta.get_tip(),oferta.get_pret(),new_denumire,new_destinatie,new_tip,new_pret);
        load_data(service.get_all());
        /*
            for(auto item :selected_item)
            {
                string item_text=item->text().toStdString();
                auto pret=item->data(Qt::UserRole).toDouble();
                qDebug()<<"cam atat te costa"<<pret;
                qDebug()<<"afisez item_text pt chestia selectata"<<item_text<<"\n";
                //item_text=denumire,destinatie,tip,pret (string)
                //gasesc ce oferta e, comparand stringul fiecarei oferte din service cu asta
                int i=0;
                for(auto &oferta: service.get_all())
                {
                    i++;
                    qDebug()<<"stringul nr "<<i<<": ";
                    qDebug()<<service.build_one_string(oferta)<<"\n";
                    if(item_text==service.build_one_string(oferta))
                    {
                        //am gasit oferta de modificat din lista mea
                        service.modify_oferta(oferta.get_denumire(),oferta.get_destinatie(),oferta.get_tip(),oferta.get_pret(),new_denumire,new_destinatie,new_tip,new_pret);
                        load_data(service.get_all());
                    }
                }
            }
        */

        });

    QObject::connect(ord_nume,&QPushButton::clicked,[&](){
        vector<Oferta> ofertele=service.ordonare_dupa_denumire();
        load_data(ofertele);
    });
    QObject::connect(ord_dest,&QPushButton::clicked,[&](){
        vector<Oferta> ofertele=service.ordonare_dupa_destinatie();
        load_data(ofertele);
    });
    QObject::connect(ord_tip,&QPushButton::clicked,[&](){
        vector<Oferta> ofertele=service.ordonare_dupa_tip();
        load_data(ofertele);
    });
    QObject::connect(ord_pret,&QPushButton::clicked,[&](){
        vector<Oferta> ofertele=service.ordonare_dupa_pret();
        load_data(ofertele);
    });

    //pentru filtrari: selectez tipul/numele/dest/pret din qlineedit-ul corespunzator
    //acela va fi criteriul dupa care filtrez
    //lista filtrata va fi afisata intr-un qmessagebox

    QObject::connect(filt_dest,&QPushButton::clicked,[&](){
        //iau denumirea din qlineedit
        string dest=destinatie->text().toStdString();
        //fac filtrarea dupa denumire
        vector<Oferta> oferte_filtrate=service.filtrare_dupa_destinatie(dest);

        // fac noua fereastra: qmessagebox
        //textul ar trebui sa fie format din stringurile ofertelor care indeplinesc criteriile + endl -uri
        string text=service.build_string_list(oferte_filtrate);
        QMessageBox::information(nullptr,"Oferte filtrate dupa destinatie",QString::fromStdString(text));
    });

    QObject::connect(filt_nume,&QPushButton::clicked,[&](){
        string den=denumire->text().toStdString();
        vector<Oferta> oferte_filtrate=service.filtrare_dupa_denumire(den);
        string text=service.build_string_list(oferte_filtrate);
        QMessageBox::information(nullptr,"Oferte filtrate dupa denumire",QString::fromStdString(text));
    });
    QObject::connect(filt_tip,&QPushButton::clicked,[&](){
        string type=tip->text().toStdString();
        vector<Oferta> oferte_filtrate=service.filtrare_dupa_tip(type);
        string text=service.build_string_list(oferte_filtrate);
        QMessageBox::information(nullptr,"Oferte filtrate dupa tip",QString::fromStdString(text));
    });
    QObject::connect(filt_pret,&QPushButton::clicked,[&](){
        double p=pret->text().toDouble();
        vector<Oferta> oferte_filtrate=service.filtrare_dupa_pret(p);
        string text=service.build_string_list(oferte_filtrate);
        QMessageBox::information(nullptr,"Oferte filtrate dupa pret",QString::fromStdString(text));
    });
    /*
    QObject::connect(add_wishlist,&QPushButton::clicked,[&](){
        // cand apas butonu se adauga la wishlist obiectul de pe campul selectat
        auto items=lista->selectedItems();
        for(const auto item: items){
            string text=item->text().toStdString();
            //text=denumire,destinatie,tip
            for(auto &o:service.get_all())
            {
                //verific fiecare oferta pana gasesc oferta egala, si pe aia o adaug la wishlist
                if(service.build_one_string(o)==text)
                    service.adauga_wishlist(o);
            }
        }
    });

    QObject::connect(empty_wishlist,&QPushButton::clicked,[&](){
        service.empty_wishlist();
    });

    QObject::connect(gen_wishlist,&QPushButton::clicked, [&](){
        service.generare_wishlist(5);
    });*/

    QObject::connect(nou_wishlist,&QPushButton::clicked,[&](){
        // genereaza fereastra noua de wishlist
        WishlistGui *wishlist = new WishlistGui{service.get_wishlist(),service};
        wishlist->show();
    });

    QObject::connect(desen,&QPushButton::clicked, [&](){
        Desen *d= new Desen{service};
        d->show();
    });

}

bool am_deja(string tip, vector<string> tipuri){
    for(const string &t:tipuri){
        if(t==tip)
            return true;
    }
    return false;
}

void GUI::adauga_butoane(const vector<Oferta> &oferte) {
    //mai intai trebuie sa iau tipurile existente si sa le adaug intr-un vector de tipuri
    vector<string> tipuri;
    for(const auto &oferta:oferte){
        string t=oferta.get_tip();
        //verific daca nu o am deja in vector
        if(!am_deja(t,tipuri))
            tipuri.push_back(t);
    }
    // am construit vector de stringuri
    //pt fiecare string, creez buton cu stringul respectiv
    for(const string &t:tipuri){
        qDebug()<<t;
        QString nume_buton=QString::fromStdString(t);
        QPushButton *buton=new QPushButton{nume_buton};
        //adaug la vector de butoane (am nevoie de vector ca sa pot elimina dupa butonul)
        vector_butoane.push_back(buton);
        layout_din->addWidget(buton);
        QObject::connect(buton,&QPushButton::clicked,[&,t](){ // nu-mi recunostea tipul t daca nu l dadeam si aici
            // cand apas butonul, afisez cate oferte de acel tip am
            map<string,int> dictionar=service.frecventa_tipuri();
            for(auto const &element: dictionar){
                if(element.first==t){
                    //afisez intr-o fereastra element.second
                    QMessageBox::information(nullptr,"Nr de elemente cu tipul selectat",QString::number(element.second));
                }
            }
        });
    }
    main_layout->addLayout(layout_din);
}

/*
void GUI::reload_table()
{
    table_model->update();
}*/