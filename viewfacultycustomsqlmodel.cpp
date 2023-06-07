#include "viewfacultycustomsqlmodel.h"
#include "QSqlTableModel"

ViewFacultyCustomSqlModel::ViewFacultyCustomSqlModel(QObject *parent, QSqlDatabase db): QSqlTableModel(parent,db){
//connect(viewfac,SIGNAL(signal_clickedRow(int)),this,SLOT(receivedFromViewFac(int)));
 //qDebug() << "Clicked row in main is" <<clicked_row;

}
Qt::ItemFlags ViewFacultyCustomSqlModel::flags(const QModelIndex& index) const{
        Qt::ItemFlags flags;
        flags = QSqlTableModel::flags(index);
        QString received_index = "QModelIndex(1,0,0x0,ViewFacultyCustomSqlModel(0x55f8f8c85dc0))";
        //qDebug()<< "Index is: "<<index;
        //int current_row = receivedFromViewFac;
//qDebug() << "Address of clicked_row in flags is:" <<&clicked_row;
//       qDebug() << "Clicked row in flags is" <<clicked_row;
        //Class_catchclicked_view_faculty *class_clicked2 = new Class_catchclicked_view_faculty;
        //QModelIndex current_row = class_clicked2->return_clicked();
        //qDebug() << "Clicked row in flags is" << current_row;
        //get this value from database
        if(index.row()==2)
        {flags |= Qt::ItemIsEditable;
          //emit click_match();
            return flags;
            }
        return (QSqlTableModel::flags(index) & ~Qt::ItemIsEditable);
    }
//void ViewFacultyCustomSqlModel::empty_clickedRow(){
//    emit click_match();
//}
