#include "unimain.h"
#include "./ui_unimain.h"
#include <QProcess>
#include <QTextStream>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>


UniMain::UniMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UniMain)
{
    ui->setupUi(this);
    //nWin = new UniMain(this);
//    QTextStream out(stdout);
//    out << "backsignal in unimain.cpp is:" <<Qt::endl;
//    out << addCourse->backsignal <<Qt::endl;

    //QMainWindow::closeEvent(
//if(addCourse->backsignal){ //put this in a function that runs here and declared in addcourse class
//addCourse->hide();//need stacked widget here
//addCourse->showMain();
//this->show();

//}
    //connect(addCourse,SIGNAL(addCourse->on), this, SLOT( showMain() ) );//see this from bookmarks tomorrow
    //connect(addCourse,SIGNAL(on_backButton_clicked()),this,SLOT(showMain()));//this works
connect(addCourse,SIGNAL(on_closeButtonClicked()),this,SLOT(showMain()));//this works
connect(addFaculty,SIGNAL(on_facultycloseButtonClicked()),this,SLOT(showMain()));//this works
connect(viewFaculty,SIGNAL(on_viewfacultycloseButtonClicked()),this,SLOT(showMain()));//this works
connect(viewFaculty,SIGNAL(signal_clickedRow(QModelIndex&)),class_clicked,SLOT(receivedFromViewFac(QModelIndex&)));

}

UniMain::~UniMain()
{
    delete ui;
}


void UniMain::on_addCourse_clicked()
{
//class AddCourse : public UniMain{

//};
//addCourse = new AddCourse(this);

//nWin = new UniMain(this);
//nWin->hide();
//nWin->setDisabled(true);


addCourse->show();//need stacked widget here
this->hide();

//QWidget *mainwin = find(wID);
//mainwin->hide();
//UniMain win;
//win.hide();
//addCourseFlag = true;
//parentWidget()->hide();
    //    QProcess *process = new QProcess(this);
//    QString file = "/UniApp/UniApp.exe";
//    //process->start(&file);
//    process->start(file);
//return true;
}

void UniMain::destroy_main(){
    QTextStream out(stdout);

    out << "In destroy main" <<Qt::endl;
//nWin = new UniMain(this);
//    nWin->hide();
    //this->hide();
      //  UniMain win;
      out << wID <<Qt::endl;
//QWidget *mainwin = find(wID);
//mainwin->hide();
//UniMain win;
//out << "In destroy main new window ID is:" <<Qt::endl;
//out << win.winId() <<Qt::endl;
//QWidget *newwin = find(win.winId());
//newwin->show();
//    win.destroy(true,true);
//    //ui->~UniMain();
}
QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}
void UniMain::closeit(QCloseEvent *event){
    event->ignore();
    hide();
}

void UniMain::showMain(){
    this->show();
    addCourse->hide();
    addFaculty->hide();
}

void UniMain::on_addFaculty_clicked()
{
    addFaculty->show();//need stacked widget here
    this->hide();

}


void UniMain::on_viewFaculty_clicked()
{
    viewFaculty->show();
    this->hide();
}

