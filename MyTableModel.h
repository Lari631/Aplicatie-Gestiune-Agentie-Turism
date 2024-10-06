#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <qfont.h>
#include "Oferta.h"
#include <vector>
#include <qdebug.h>
#include <qtableview>
using std::vector;


class MyTableModel :public QAbstractTableModel {
    std::vector<Oferta> oferte;
public:
    MyTableModel(const std::vector<Oferta>& oferte) :oferte{ oferte } {
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return (int)oferte.size(); //merge?
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }
    //Returns the data stored under the given role for the item referred to by the index.
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {

            Oferta o = oferte[index.row()];
            if (index.column() == 0) {
                return QString::fromStdString(o.get_denumire());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(o.get_destinatie());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(o.get_tip());
            }
            else if (index.column() == 3) {
                return QString::number(o.get_pret());
            }
        }

        return QVariant{};
    }

    void set_oferte(const vector<Oferta> oferte) {
        this->oferte = oferte;
        auto topLeft = createIndex(0, 0);
        auto bottomR = createIndex(rowCount(), columnCount());
        emit dataChanged(topLeft, bottomR);
        emit layoutChanged();
    }

    Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                    case 0:
                        return tr("Denumire");
                    case 1:
                        return tr("Destinatie");
                    case 2:
                        return tr("Tip");
                    case 3:
                        return tr("Pret");
                    default:
                        return QString("");
                }
            }
        }
        return QVariant{};
    }
    void update(){
        set_oferte(oferte);
    }
};