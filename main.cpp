#include <QApplication>
#include <QPushButton>
#include "teste.h"
#include "consola.h"
#include "gui.h"
#include "wishlist_gui.h"
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include "desen.h"


int main(int argc, char *argv[]) {
    run_teste();
    QApplication a(argc, argv);
    try{
        FileRepo filerepo{"oferte.txt"};
        Service service{filerepo};
        qDebug()<<"am service\n";
        GUI gui{service};
        qDebug()<<"am gui\n";
        gui.show();
        //Wishlist wishlist;
        //WishlistGui wishlist_gui{service.get_wishlist()};
        //wishlist_gui.show();

        return QApplication::exec();
    }
    catch(RepoException &ex)
    {
        cout<<ex.get_mesaj();
    }

    return 0; // nu stiu daca e nevoie

}
