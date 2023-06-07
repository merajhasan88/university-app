#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QGraphicsScene>

namespace Ui {
class AddCourse;
}

class AddCourse : public QMainWindow
{
    Q_OBJECT

public:
    int col = 0;
       int row = 0;
       int sizex = 5;
       int sizey = 0;
       QGraphicsScene *scene = new QGraphicsScene(this);
    explicit AddCourse(QWidget *parent = nullptr);
    ~AddCourse();
signals:
       void on_closeButtonClicked();
public slots:
       void closeEvent(QCloseEvent *event);
private slots:
    void on_submitButton_clicked();
    void addColToTableView(QString,int);
        //void addRowToTableView(QString);
void showEvent(QShowEvent *event);
        void setTitle();
            void clear_addnewRow();

    void on_submitButtonID_clicked();

    void on_submitButtonName_clicked();

    void on_submitButtonDetails_clicked();

    void on_doneButton_clicked();

private:
    Ui::AddCourse *ui;
    QStandardItemModel *model;
    QList<QStandardItem*> items;
};

#endif // ADDCOURSE_H
