#ifndef VIEWFACULTY_H
#define VIEWFACULTY_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QPushButton>
//#include "viewfacultycustomsqlmodel.h"

namespace Ui {
class ViewFaculty;
}

class ViewFaculty : public QMainWindow
{
    Q_OBJECT

public:
    //static int clicked_row;

     //QPushButton *button_dynamic = new QPushButton;
    explicit ViewFaculty(QWidget *parent = nullptr);
    ~ViewFaculty();
signals:
    void on_viewfacultycloseButtonClicked();
    void signal_clickedRow(QModelIndex&);
public slots:
     void closeEvent(QCloseEvent *event);
     void changeTextEditButton(QPushButton *button_d);
private slots:
     void on_viewFacultybBckButton_clicked();

private:
    Ui::ViewFaculty *ui;

   // ViewFacultyCustomSqlModel *viewfaccustsqlmod = new ViewFacultyCustomSqlModel;
//    QSqlTableModel *model;
//    QSqlTableModel *modelLoop;
};

#endif // VIEWFACULTY_H
