#include "addcourse.h"
#include "ui_addcourse.h"
#include <QTextStream>
#include <QtWidgets>
#include <QFileSystemModel>
#include <QCloseEvent>
#include <QDebug>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlTableModel>

AddCourse::AddCourse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddCourse)
{
    ui->setupUi(this);
    QSqlDatabase db_addCourse = QSqlDatabase::addDatabase("QPSQL");

    db_addCourse.setHostName("localhost");
    db_addCourse.setDatabaseName("uniapp");
    db_addCourse.setUserName("postgres");
    db_addCourse.setPassword("meraj346");
    bool ok = db_addCourse.open();

    if(!ok){
        //    qDebug() << "Failed to connect to root mysql admin";
        qDebug()<< db_addCourse.lastError();
    }
    else{
        qDebug() << "Connected to postgresql admin in addcourse.cpp";
    }

    //QSqlTableModel *model = new QSqlTableModel;
    //model->setTable();

    //    QSqlQuery query;
    //        query.exec("DELETE FROM employee WHERE id = 1001");
    //    QSqlQuery query;
    //    query.exec("INSERT INTO employee (id, name, department)"
    //               "VALUES (1001, 'Meraj Hasan', 'Electrical')");
    //or
    //    query.prepare("INSERT INTO employee (id, name, department) "
    //                      "VALUES (?, ?, ?)");
    //        query.addBindValue(1002);
    //        query.addBindValue("Zakariyya Hasan");
    //        query.addBindValue("Computer");
    //        query.exec();


    ui->lineEdit_details->setFixedWidth(200);
        ui->label_details->setFixedWidth(93);
        ui->label->setFixedWidth(93);
        ui->label_2->setFixedWidth(93);
        ui->label_3->setFixedWidth(93);

        model = new QStandardItemModel(sizey,sizex,this); //see if this can be taken out of main tomorrow
        QModelIndex index;
        model->setHeaderData(0,Qt::Horizontal,
        QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,
        QObject::tr("Name"));
        model->setHeaderData(2,Qt::Horizontal,
        QObject::tr("Semester"));
        model->setHeaderData(3,Qt::Horizontal,
        QObject::tr("Department"));
        model->setHeaderData(4,Qt::Horizontal,
        QObject::tr("CGPA"));
        ui->doneButton->setFixedWidth(50);
        ui->backButton->setFixedWidth(50);
        //ui->backButton->setAttribute(Qt::AlignRight, true);
        ui->doneButton->setDisabled(true);
        ui->tableView->setModel(model);
                ui->tableView->verticalHeader()->hide();
                ui->tableView->horizontalHeader()->setStretchLastSection(true);
                connect(ui->submitButton, SIGNAL( clicked() ), this, SLOT( setTitle()  ) );//this sets title of table
        connect(ui->backButton, SIGNAL(clicked()),this, SLOT(close()));

        QPixmap image=QPixmap(":/logo.jpeg");
        //QGraphicsScene *scene = new QGraphicsScene(this);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(image);
        scene->addItem(item);

        ui->graphicsView->setScene(scene);
        //ui->graphicsView->show();
}

AddCourse::~AddCourse()
{
    delete ui;
}

void AddCourse::on_submitButton_clicked()
{
QString searchString = ui->lineEdit->text();
}

QTextStream& qStdOut2()
{
    static QTextStream ts( stdout );
    return ts;
}

void AddCourse::addColToTableView(QString name,int row)
{
    QModelIndex index;
    //following commented section adds a new row
    QStandardItem *item = new QStandardItem(name);
    QList<QStandardItem*> data;
    data << item;
//    QList<QStandardItem*> row;
//        row << item;
        //model->appendRow(item);//adds a new row
        //model->appendRow(row);//also adds a new row
        //model->insertColumn(col,row); //adds new column
        index = model->index(row,col,QModelIndex());

        model->setData(index,name);
        col++;

    //following adds something from line edit to whichever place in table
//        index = model->index(0,0,QModelIndex());

//        model->setData(index,name);
    //items << item;

//    for(int i = 0; i < items.size(); i++)
//    {
//        for(int j = 0; j < 1; j++)
//        {

//            model->setItem(i, j, items.at(i));
//        }
//    }
}

void AddCourse::on_submitButtonID_clicked()
{

    QString searchString = ui->lineEdit_ID->text();
        QTextStream out(stdout);
        //QStandardItem *item = new QStandardItem(searchString);
        row++;
        model->setRowCount(row);
        //UniApp::sizey = 2;//learn how to change it dynamically. Done. Use setRowCount()

        //model->insertRow(row,item);
        addColToTableView(searchString,row-1);
        //col++;

}


void AddCourse::on_submitButtonName_clicked()
{
    QString searchString = ui->lineEdit_name->text();
        QTextStream out(stdout);

        addColToTableView(searchString,row-1);

}


void AddCourse::on_submitButtonDetails_clicked()
{
    QString searchString = ui->lineEdit_details->text();
        QTextStream out(stdout);

        addColToTableView(searchString,row-1);
        if(col == 3){
        ui->label_details->setText("Department:");
        }
        if(col == 4){
        ui->label_details->setText("CGPA:");
        ui->lineEdit_details->clear();
        }
        if(col==5){
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"));
        if (!fileName.isEmpty()) {
            QImage tempImage(fileName);
            if (tempImage.isNull()) {
                QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
                return;
            }

        }
        }
        if(col == 6){
        ui->label_details->setText("Semester:");
        ui->lineEdit_details->clear();
        ui->doneButton->setDisabled(false);
        QMessageBox::information(
            this,
            tr("System:"),
            tr("Thank you. You may add another student") );
            clear_addnewRow();
        }

}

void AddCourse::setTitle(){
        QSqlQuery query_create;
        //parse the string here. Fill spaces with underscore and everything in toLower
        QString query_string = QString("CREATE TABLE IF NOT EXISTS %1(id integer NOT NULL, name VARCHAR(200) NOT NULL, semester VARCHAR(200) NOT NULL, department VARCHAR(200) NOT NULL, cgpa NUMERIC NOT NULL, photo BYTEA NOT NULL)").arg(ui->lineEdit->text());
        query_create.exec(query_string);
        //    QSqlQuery query;
        //        query.exec("DELETE FROM employee WHERE id = 1001");
        //    QSqlQuery query;
        //    query.exec("INSERT INTO employee (id, name, department)"
        //               "VALUES (1001, 'Meraj Hasan', 'Electrical')");
        //or
        //    query.prepare("INSERT INTO employee (id, name, department) "
        //                      "VALUES (?, ?, ?)");
        //        query.addBindValue(1002);
        //        query.addBindValue("Zakariyya Hasan");
        //        query.addBindValue("Computer");
        //        query.exec();

    ui->label_title->setText(ui->lineEdit->text());
}

void AddCourse::clear_addnewRow(){
    ui->lineEdit_ID->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_details->clear();
    col = 0;

}


void AddCourse::on_doneButton_clicked()
{
    ui->lineEdit->clear();
        ui->label_title->clear();
        ui->lineEdit_ID->clear();
        ui->lineEdit_name->clear();
        ui->lineEdit_details->clear();
        for(int i=0;i<row;i++){
            for(int j=0;j<5;j++){
             model->removeRows(i,j,QModelIndex());
            }
        }
        col = 0;
        ui->doneButton->setDisabled(true);
        QMessageBox::information(
            this,
            tr("System:"),
            tr("Saved successfully. You may add another course and its students") );
}

void AddCourse::closeEvent(QCloseEvent *event){
    if(QMessageBox::question(this,tr("System:"),tr("Are you sure you want to close this window?"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes){
        emit on_closeButtonClicked();
        event->accept();
    }
    else {
        event->ignore();
    }
}
void AddCourse::showEvent(QShowEvent *event){
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}
