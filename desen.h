#pragma once
#include "service.h"
#include <qpainter.h>
#include <QWidget>

class Desen: public QWidget, public Observer{
private:
    Service &service;
public:
    Desen(Service &service):service{service}{
        service.add_observer(this);
    };
    void update() override{
        repaint();
    }
    void paintEvent(QPaintEvent *pe) override{
        QPainter p{this};
        int x=0,y=0;
        for(const auto &o: service.get_elemente_wishlist())
        {
            p.drawRect(x,y,30,30);
            x=x+50;
            y=y+50;
        }
    }

};