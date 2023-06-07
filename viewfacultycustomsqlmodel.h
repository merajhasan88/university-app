#ifndef VIEWFACULTYCUSTOMSQLMODEL_H
#define VIEWFACULTYCUSTOMSQLMODEL_H

#include <QSqlTableModel>
//#include <viewfaculty.h>
#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include "class_catchclicked_view_faculty.h"

class Clicked_class : QMainWindow
{
public:
    Clicked_class(int received_int){
        clicked_class_int = received_int;
    }
    int clicked_class_int;
};

class ViewFacultyCustomSqlModel : public QSqlTableModel
{
   Q_OBJECT

public:
//    ViewFacultyCustomSqlModel():QSqlTableModel(),
//        clicked_row(new int){
//      connect(viewfac,SIGNAL(signal_clickedRow(int)),this,SLOT(receivedFromViewFac(int)));
//    }
    //ViewFacultyCustomSqlModel();
   // ~ViewFacultyCustomSqlModel();
    //QModelIndex clicked_row;
    QList<int> clicked_rows;
    QLabel *label = new QLabel();
    const QString tempTest;

    int clicked_row;//put this in a slot that returns this value not with flags directly
    //then use that value in flags instead of using clicked_row directly
    ViewFacultyCustomSqlModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    int return_clicked(){
        int new_clicked = clicked_row;
        return new_clicked;
    }
    //virtual
    /*Qt::ItemFlags flags(const QModelIndex& index) const{
        Qt::ItemFlags flags;
        flags = QSqlTableModel::flags(index);
        //int current_row = receivedFromViewFac;
        qDebug() << "Clicked row in flags is" <<clicked_row;
        if(index.row()==clicked_row )
        {flags |= Qt::ItemIsEditable;
            return flags;
            }
        return (QSqlTableModel::flags(index) & ~Qt::ItemIsEditable);
    }*/
private:
   // ViewFaculty *viewfac = new ViewFaculty;
    //int *clicked_row;
public slots:
    //void empty_clickedRow();
    void receivedFromViewFac(int indexFromViewFac){
        clicked_row = indexFromViewFac;
        label->setText(QString::number((clicked_row)));
        //qDebug() << "Address of clicked_row in slot is:" <<&clicked_row;
        clicked_rows.insert(0,clicked_row);
       // qDebug() << "Clicked row received is" <<clicked_rows.at(0);
        //flags(indexFromViewFac);

    }

    Qt::ItemFlags flags(const QModelIndex& index) const;
//public slots:
//    Qt::ItemFlags flags(const QModelIndex& index) const{
//            Qt::ItemFlags flags;
//            flags = QSqlTableModel::flags(index);

//            if(index.row()== *clicked_row)
//            {flags |= Qt::ItemIsEditable;
//                return flags;
//                }
//            return (QSqlTableModel::flags(index) & ~Qt::ItemIsEditable);
//        }
//signals:
//    void click_match();
};

#endif // VIEWFACULTYCUSTOMSQLMODEL_H
