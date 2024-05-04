#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QGraphicsScene>
#include <qpushbutton.h>
namespace Ui {
class AddCourse;
}

class AddCourse : public QMainWindow
{
    Q_OBJECT

public:
//    QPushButton *push_buttonImage = new QPushButton(this);
    QString table_name="";
    QString id = "";
    QString name = "";
    QString semester = "";
    QString department = "";
    QString cgpa="";
    QByteArray image_bytes;
    int col = 0;
       int row = 0;
       int sizex = 6;
       int sizey = 0;
       QGraphicsScene *scene = new QGraphicsScene(this);
    explicit AddCourse(QWidget *parent = nullptr);
    ~AddCourse();
signals:
       void on_closeButtonClicked();
    void onImageCellClicked();
public slots:
       void closeEvent(QCloseEvent *event);
    void openImage(QString);
private slots:
    void on_submitButton_clicked();
    void addColToTableView(QString,int);
    void addImageColToTableView(int);
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
