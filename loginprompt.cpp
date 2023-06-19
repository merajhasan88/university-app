#include "loginprompt.h"
#include "ui_loginprompt.h"
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QDebug>
#include <QMessageBox>
loginPrompt::loginPrompt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginPrompt)
{
    ui->setupUi(this);
    loginPrompt::setWindowTitle("Login Required");
    ui->web_link->setObjectName("weblink");
    ui->web_link->setStyleSheet("QLabel#weblink{text-decoration: underline; color: blue;}");
    ui->web_link->openExternalLinks();
    //ui->web_link->setText("<a href=\"http://www.qtcentre.org\">If you don't have an account yet, \ncontact the administrator by \nclicking this link</a>");
    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //QSqlDatabase db_viewFaculty = QSqlDatabase::addDatabase("QMYSQL","SQLConnectionViewFaculty");
    QSqlDatabase db = QSqlDatabase::database();
//    db.setHostName("localhost");
//    db.setDatabaseName("uniapp");
//    db.setUserName("meraj");
//    db.setPassword("meraj346");

    bool ok = db.open();

    if(!ok){
    //    qDebug() << "Failed to connect to root mysql admin";
        qDebug()<< db.lastError();
    }
    else{
       qDebug() << "Connected to mysql admin";
    }

    QSqlQuery query_username("SELECT username FROM passwords");
    while(query_username.next()){
       username = query_username.value(0).toString();

     qDebug() << "username is:" <<username;

    }
    QSqlQuery query_password("SELECT password FROM passwords");
    while(query_password.next()){
        password = query_password.value(0).toString();

        qDebug() << "password is:" <<password;

    }



}

loginPrompt::~loginPrompt()
{
    delete ui;
}

void loginPrompt::on_loginExitButton_clicked()
{
    this->close();
}


void loginPrompt::on_loginSubmitButton_clicked()
{
    if(ui->username->text() == " " || ui->password->text() == " "){
        QMessageBox::warning(this,tr("Error"),tr("Either your usernae or password field is empty"),QMessageBox::Retry);
    }
    if(ui->username->text() == username && ui->password->text()==password){
        unimain->show();
        this->hide();
    }
    else{
        QMessageBox::warning(this,tr("Error"),tr("Invalid username or password"),QMessageBox::Retry);
    }

}

