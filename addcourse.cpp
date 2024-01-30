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
    QSqlDatabase db_addCourse = QSqlDatabase::addDatabase("QMYSQL");

    db_addCourse.setHostName("localhost");
    db_addCourse.setDatabaseName("uniapp");
    db_addCourse.setUserName("meraj");
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
    id = searchString;
    ui->lineEdit_ID->clear();
    //col++;

}


void AddCourse::on_submitButtonName_clicked()
{
    QString searchString = ui->lineEdit_name->text();
    QTextStream out(stdout);

    addColToTableView(searchString,row-1);
    name = searchString;
    ui->lineEdit_name->clear();
}


void AddCourse::on_submitButtonDetails_clicked()
{
    QString searchString = ui->lineEdit_details->text();
    QTextStream out(stdout);

    addColToTableView(searchString,row-1);
    if(col == 3){
        ui->label_details->setText("Department:");
        semester= searchString;
    }
    if(col == 4){
        ui->label_details->setText("CGPA:");
        department = searchString;
        ui->lineEdit_details->clear();
    }
    if(col==5){
        ui->label_details->setText("Add Photo:");
        cgpa = (searchString);
        ui->lineEdit_details->clear();
        ui->lineEdit_details->hide();
        QSqlQuery query_insert;

        QString query_string2 = QString("INSERT INTO %1 (id,name,semester,department,cgpa,photo) VALUES (:id,:name,:semester,:department,:cgpa,:photo)").arg(table_name);
            //QFile* imageFile=new QFile(":/logo.jpeg");
            //imageFile->open(QIODevice::ReadOnly);
            //image_bytes=imageFile->readAll();
            //imageFile->close();


        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image")); //Use QFile tomorroiw here
        if (!fileName.isEmpty()) {
            QImage tempImage(fileName);
            if (tempImage.isNull()) {
                QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
                return;
            }
            //QPixmap mypix(fileName);
            QBuffer buffer(&image_bytes);
            buffer.open(QIODevice::WriteOnly);
            QPixmap::fromImage(tempImage).save(&buffer,"JPG");
            //tempImage.save(&buffer);
        }
        //qDebug()<<"Image bytes are: "<<image_bytes;
        QString photo_data = QString((image_bytes.toBase64()));
        //qDebug()<<"Photo data is: "<<photo_data;
        query_insert.prepare(query_string2);

        query_insert.bindValue(":id",id.toInt());
        query_insert.bindValue(":name",name);
        query_insert.bindValue(":semester",semester);
        query_insert.bindValue(":department",department);
        query_insert.bindValue(":cgpa",cgpa.toFloat());//Getting truncated. Fix this
        query_insert.bindValue(":photo",photo_data);
        if(!query_insert.exec()){
            qDebug()<<query_insert.lastError().text();
            //show a message using this error in case somebody leaves a field blank
        }
        QString query_string_readback = QString("SELECT photo from %1").arg(table_name);
        if(!query_insert.exec(query_string_readback)){
            qDebug()<<query_insert.lastError().text();
        }
        else{
            query_insert.last();//what if we change it to last to display latest image?Submit Button, auto clearing and
            //Deletion from table is also problematic
            QByteArray outByteArray = query_insert.value(0).toByteArray();
            qDebug()<<"Data from database: "<<QByteArray::fromBase64(outByteArray);
            QPixmap outPixmap=QPixmap();
            outPixmap.loadFromData(QByteArray::fromBase64(outByteArray));
            QLabel *myLabel = new QLabel(this);
            myLabel->setWindowFlags(Qt::Window);
            myLabel->setPixmap(outPixmap);
            myLabel->show();
        }
        QString query_string_readback2 = QString("SELECT name from %1").arg(table_name);
        if(!query_insert.exec(query_string_readback2)){
            qDebug()<<query_insert.lastError().text();
        }
        else{
            query_insert.last();
            qDebug()<<"Name is: "<<query_insert.value(0).toString();
        }
//        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image")); //Use QFile tomorroiw here
//        if (!fileName.isEmpty()) {
//            QImage tempImage(fileName);
//            if (tempImage.isNull()) {
//                QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
//                return;
//            }
//            //QPixmap mypix(fileName);
//            QBuffer buffer(&image_bytes);
//            buffer.open(QIODevice::WriteOnly);
//            QPixmap::fromImage(tempImage).save(&buffer,"JPG");
//            //tempImage.save(&buffer);
//        }
//        QFile* imageFile=new QFile(":/logo.jpeg");
//        imageFile->open(QIODevice::ReadOnly);
//        image_bytes=imageFile->readAll();
//        imageFile->close();
//        delete imageFile;
    }
    if(col == 6){
//        QSqlQuery query;
//        qDebug()<<"Image bytes are: "<<image_bytes;
//        QString photo_data = QString((image_bytes.toBase64()));
//        qDebug()<<"Photo data is: "<<photo_data;
//        QString query_string = QString("INSERT INTO %1 (id,name,semester,department,cgpa,photo) VALUES (%2,%3,%4,%5,%6,:%7)").arg(table_name).arg(id).arg(name).arg(semester).arg(department).arg(cgpa).arg(photo_data);
//        query.exec(query_string);
//        //"You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near 'Nawaz,5,Computer,2.81,)' at line 1 QMYSQL: Unable to execute query"
//        //Check from MYSQL db tomorrow what is being entered. Also print photo_data
//        //Issue resolved with photodata. Need to see how to read it from file.
//         //But mysql query is still a problem and unable to read QByteArray converted to base 64. Check that too.
//        //Read from file successfully. Need to fix mysql error in query
//        if(!query.exec()){
//            qDebug()<<query.lastError().text();
//        }
//        else{
//            qDebug()<<query.result();
//        }

        ui->label_details->setText("Semester:");
        ui->lineEdit_details->show();
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
    table_name =(ui->lineEdit->text()).toLower();
    table_name.replace(" ","_");
    qDebug()<<table_name;
    //also add a popup if someone adds an ampersand
    //QString temp_table ="temp_table";
    QString query_string = QString("CREATE TABLE IF NOT EXISTS %1(id INT NOT NULL, name VARCHAR(200) NOT NULL, semester VARCHAR(200) NOT NULL, department VARCHAR(200) NOT NULL, cgpa DECIMAL NOT NULL, photo LONGBLOB)").arg(table_name);
    query_create.exec(query_string);
        if(!query_create.exec()){
            qDebug()<<query_create.lastError().text();
            //show a message using this error in case somebody leaves a field blank
        }
//        QSqlQuery query_insert;
//        QString name_t = "meraj";
//        QString sem_t = "4th";
//        QString dept_t = "Elec";
//        QString query_string2 = QString("INSERT INTO %1 (id,name,semester,department,cgpa,photo) VALUES (:id,:name,:semester,:department,:cgpa,:photo)").arg(temp_table);
//                //QFile* imageFile=new QFile(":/logo.jpeg");
//                //imageFile->open(QIODevice::ReadOnly);
//                //image_bytes=imageFile->readAll();
//                //imageFile->close();


//        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image")); //Use QFile tomorroiw here
//        if (!fileName.isEmpty()) {
//            QImage tempImage(fileName);
//            if (tempImage.isNull()) {
//            QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
//            return;
//            }
//            //QPixmap mypix(fileName);
//            QBuffer buffer(&image_bytes);
//            buffer.open(QIODevice::WriteOnly);
//            QPixmap::fromImage(tempImage).save(&buffer,"JPG");
//            //tempImage.save(&buffer);
//        }
//        //qDebug()<<"Image bytes are: "<<image_bytes;
//        QString photo_data = QString((image_bytes.toBase64()));
//        //qDebug()<<"Photo data is: "<<photo_data;
//        query_insert.prepare(query_string2);

//        query_insert.bindValue(":id",1002);
//                    query_insert.bindValue(":name",name_t);
//                    query_insert.bindValue(":semester",sem_t);
//                    query_insert.bindValue(":department",dept_t);
//                    query_insert.bindValue(":cgpa",3.20);
//                    query_insert.bindValue(":photo",photo_data);
//            if(!query_insert.exec()){
//                qDebug()<<query_insert.lastError().text();
//                //show a message using this error in case somebody leaves a field blank
//            }
//           QString query_string_readback = QString("SELECT photo from %1").arg(temp_table);
//            if(!query_insert.exec(query_string_readback)){
//                qDebug()<<query_insert.lastError().text();
//            }
//            else{
//                query_insert.first();
//                QByteArray outByteArray = query_insert.value(0).toByteArray();
//                qDebug()<<"Data from database: "<<QByteArray::fromBase64(outByteArray);
//                QPixmap outPixmap=QPixmap();
//                outPixmap.loadFromData(QByteArray::fromBase64(outByteArray));
//                QLabel *myLabel = new QLabel(this);
//                myLabel->setWindowFlags(Qt::Window);
//                myLabel->setPixmap(outPixmap);
//                myLabel->show();
//            }
//            QString query_string_readback2 = QString("SELECT name from %1").arg(temp_table);
//            if(!query_insert.exec(query_string_readback2)){
//                qDebug()<<query_insert.lastError().text();
//            }
//            else{
//            query_insert.first();
//                qDebug()<<"Name is: "<<query_insert.value(0).toString();
//            }
            //image inserted successfully. Need to read it back to see if it was saved correctly
   // QString query_string = QString("CREATE TABLE IF NOT EXISTS %1(id INT NOT NULL, name VARCHAR(200) NOT NULL, semester VARCHAR(200) NOT NULL, department VARCHAR(200) NOT NULL, cgpa DECIMAL NOT NULL, photo BLOB NOT NULL)").arg(table_name);
//    query_create.exec(query_string);
//    if(!query_create.exec()){
//        qDebug()<<query_create.lastError().text();
//        //show a message using this error in case somebody leaves a field blank
//    }

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
    qDebug()<<"Row count is: "<<row;
    for(int i=0;i<row;i++){
        for(int j=0;j<5;j++){
            model->removeRows(i,1,QModelIndex());
        }
    }
//    QModelIndexList indexes= ui->tableView->selectionModel()->selectedRows();
//    while(!indexes.isEmpty()){
//            model->removeRows(indexes.last().row(),1);
//            indexes.removeLast();
//    }
    col = 0;
    row = 0;
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
