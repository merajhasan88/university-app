#ifndef CLASS_CATCHCLICKED_VIEW_FACULTY_H
#define CLASS_CATCHCLICKED_VIEW_FACULTY_H
#include <QMainWindow>
#include <QDebug>

class Class_catchclicked_view_faculty : public QMainWindow
{

    Q_OBJECT
public:
    //QModelIndex& clicked_row;

    Class_catchclicked_view_faculty();
    void return_clicked(){
        //QModelIndex clicked_row = pick_clicked();
//        QModelIndex& new_clicked = clicked_row;
//        new_clicked++;
//        if(new_clicked > 2){
//            new_clicked = 0;
//        }
//        //qDebug() << "Clicked_row in new class function is: "<< new_clicked;
//        return new_clicked;
    }
    QModelIndex& pick_clicked(QModelIndex& clicked_index){
        //QModelIndex& new_clicked = clicked_index;
        return clicked_index;
    }
public slots:
    void receivedFromViewFac(QModelIndex& indexFromViewFac){

        //send index via internal signal slot
        //clicked_row == indexFromViewFac;
        //QString clickedRow = indexFromViewFac.toString();

        //have another pick funbction instead
        //        clicked_row++;
//        if(clicked_row > 2){
//            clicked_row = 0;
//        }
        //label->setText(QString::number((clicked_row)));
        //qDebug() << "Address of clicked_row in slot is:" <<&clicked_row;
        //clicked_rows.insert(0,clicked_row);
       qDebug() << "Clicked row received is" <<indexFromViewFac;
        //flags(indexFromViewFac);

    }
};

#endif // CLASS_CATCHCLICKED_VIEW_FACULTY_H
