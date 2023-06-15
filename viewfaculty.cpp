#include "viewfaculty.h"
#include "ui_viewfaculty.h"
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
#include <QSqlTableModel>
#include <QTableView>
#include <QStyle>
#include <QSqlRecord>
#include <QVector>
#include "viewfacultycustomsqlmodel.h"
#include <iostream>
using namespace std;
ViewFaculty::ViewFaculty(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewFaculty)
{
    ui->setupUi(this);


cout<<"Constructor called"<<endl;
    ViewFaculty::setWindowTitle("View Faculty Members");
    QWidget *contentWidget = new QWidget();
    QGridLayout *layoutG = new QGridLayout();

    QGroupBox *boxTables = new QGroupBox(contentWidget);
    boxTables->setFixedWidth(555);
    boxTables->setObjectName("coloredBorder");
    boxTables->setStyleSheet("QGroupBox#coloredBorder{border: 5px solid black;}");
    //QFrame *frame = new QFrame;
    //frame->setLayout(boxTables);
    //frame->setObjectName("mainBorder");
    //this->setStyleSheet("QFrame {border: 5px solid black;}");
    //frame->setStyleSheet("frame {border: 5px solid black;}");
    //QHBoxLayout *layoutH = new QHBoxLayout(boxTables);
    QVBoxLayout *layoutV = new QVBoxLayout(boxTables);
    //layoutH->addLayout(layoutV);
    layoutG->addWidget(boxTables,0,0, Qt::AlignLeft); //tables added
    //add dynamic edit buttons with a table within Gridlayout too

    layoutG->setColumnStretch(0, 10000);

    //layoutH->addLayout(layoutV);

    //layoutG->addWidget(ui->viewFacultybBckButton,0,1,Qt::AlignTop);//button added
layoutG->setVerticalSpacing(50);
    //layoutG->setColumnStretch(1, 1000);
     layoutG->setHorizontalSpacing(200);
    //    ui->viewFacultybBckButton->setGeometry(700,30,8,5);
    //layoutH->setSpacing(50);
//    layoutH->setContentsMargins(30,20,50,50);
    connect(ui->viewFacultybBckButton, SIGNAL(clicked()),this, SLOT(close()));
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("uniapp");
    db.setUserName("meraj");
    db.setPassword("meraj346");
    bool ok = db.open();

    if(!ok){
    //    qDebug() << "Failed to connect to root mysql admin";
        qDebug()<< db.lastError();
    }
    else{
       qDebug() << "Connected to mysql admin";
    }
//Delete and create below
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


    QList<QString> depList; //dynamic array
    QList<QString> uniquedepList;
    int i = 0;
    QSqlQuery query("SELECT department FROM employee");
    while(query.next()){
        QString department = query.value(0).toString();
        depList.insert(i,department);
        qDebug() << "Department list:" <<department;
        i++;
    }
//    QSqlTableModel *model = new QSqlTableModel;
//    //ViewFacultyCustomSqlModel *model = new ViewFacultyCustomSqlModel(0,db);
//        model->setTable("employee");

//       //model->setFilter("department = 'Electrical'");
//        //model->setSort(2, Qt::DescendingOrder);
//        model->select();

//        //Extracting a single column
//        for (int i = 0; i < model->rowCount(); ++i) {
//            QString department = model->record(i).value("department").toString();
//           // int salary = model->record(i).value("salary").toInt();
//            depList.insert(i,department); //insert into dynamic array
//           // qDebug() << "Department is: "<<depList[i]; //retrieve dynamic array value
//        }

       for (int j = 0; j< depList.size();j++){
           int depCount = 0;
       for (int k = j; k<depList.size() && depCount <2;k++){
           if(depList[j]==depList[k]){
               depCount++;
               }
       }
       if(depCount == 1){
       uniquedepList.push_back(depList[j]);
       }
       }
       for (int i = 0; i< uniquedepList.size();i++){
        qDebug() << "Unique department list is:" << uniquedepList[i];
       }
        int start_y = 10;
        //ViewFacultyCustomSqlModel *modelLoop = new ViewFacultyCustomSqlModel(0,db);
       for (int i = 0; i< uniquedepList.size();i++){
           QString match_dept = uniquedepList[i];
           //ViewFacultyCustomSqlModel *modelLoop = new ViewFacultyCustomSqlModel(0,db);
           QSqlTableModel *modelLoop = new QSqlTableModel;
           modelLoop->setTable("employee");
           modelLoop->select();
           QString querystring = QString("department = %1%2%3").arg("'").arg(uniquedepList[i]).arg("'");
           qDebug() << querystring;
           modelLoop->setFilter(querystring);
           int dynamic_rows = modelLoop->rowCount();//How many rows in the table
//           qDebug() << "dynamic rows are" <<dynamic_rows;
           QLabel *label = new QLabel;
           label->setText(uniquedepList[i]);
           //setGeometry(x_pos,y_pos,width1,height1);
           label->setGeometry(30,start_y,100,20);

          modelLoop->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          modelLoop->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
           modelLoop->setHeaderData(2, Qt::Horizontal, QObject::tr("Department"));
           QTableView *view = new QTableView;

            /* label->setParent(ui->scrollArea);
           view->setParent(ui->scrollArea);*/ //binds newly created table to the current view. Fix its size tomorrow.
           QVBoxLayout *layoutVButtons = new QVBoxLayout;
           QVBoxLayout *layoutVButtonsDelete = new QVBoxLayout;
           QHBoxLayout *layoutMergeWithTables = new QHBoxLayout;
           layoutMergeWithTables->addWidget(view);
           //layoutVButtons->addLayout(layoutMergeWithTables);
           layoutMergeWithTables->addLayout(layoutVButtons);
           layoutMergeWithTables->addLayout(layoutVButtonsDelete);
           //layoutH->addLayout(layoutVButtons);

           // label->setParent(contentWidget);
          // view->setParent(contentWidget);
           //Then in a for loop read department-wise from mysql and create a new label and table for each department
              view->setModel(modelLoop);
//              modelLoop->setEditStrategy(QSqlTableModel::OnManualSubmit);
//              view->setSelectionMode(QAbstractItemView::SingleSelection);
//              view->setSelectionBehavior(QAbstractItemView::SelectRows);
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);
              //view->setFixedWidth(365);
              //view->setFixedHeight(200);
              view->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//allows change of size of one column in particular
              view->setColumnWidth(1,150);
              view->setGeometry(30,start_y+10+label->geometry().height(),365,200);
//setGeometry isnt working

              view->setStyleSheet("QHeaderView::section {background-color:black; color: white}");
               view->verticalHeader()->hide();
             // view->setStyleSheet("padding-left: 20px; padding-top: 50px;"
               //         );
              layoutV->addWidget(label);
              //layoutV->addWidget(view);
               layoutV->addLayout(layoutMergeWithTables);
              for(int i = 0; i< dynamic_rows;i++){
                 QPushButton *button_dynamic = new QPushButton;
                 QPushButton *button_dynamic_delete = new QPushButton;

                 //get pointer to the button
                  //button_dynamic->setText(QString ("Edit %1").arg(i));
                  button_dynamic->setText("Edit");
                  layoutVButtons->addWidget(button_dynamic);
                  layoutVButtons->setAlignment(Qt::AlignTop);
                  layoutVButtons->setContentsMargins(0,25,0,0);
                  button_dynamic_delete->setText("Delete");
                  layoutVButtonsDelete->addWidget(button_dynamic_delete);
                  layoutVButtonsDelete->setAlignment(Qt::AlignTop);
                  layoutVButtonsDelete->setContentsMargins(0,25,0,0);
                  connect(button_dynamic,&QPushButton::clicked,[button_dynamic,view,i,modelLoop, this](){
                              if(button_dynamic->text()=="Edit"){
                                  QModelIndex tableIndex = view->model()->index(i,0,QModelIndex());
                                  qDebug() << "Clicked_row sent is: "<<tableIndex;
                                  emit signal_clickedRow(tableIndex);
                                  button_dynamic->setText("Save");
                                  modelLoop->setEditStrategy(QSqlTableModel::OnManualSubmit);//apply all these strategies only to a particular row and particular columns
                                  view->setSelectionMode(QAbstractItemView::SingleSelection);//modify these two
                                  view->setSelectionBehavior(QAbstractItemView::SelectItems);
//                                  view->setEditTriggers(view->editTriggers().setFlag();
//                                  QModelIndexList tableIndexes = view->selectionModel()->selectedRows();
                                   view->selectRow(i);

                                   //qDebug() << "Current Index is:" << view->currentIndex();
                                   //qDebug() << "Edit Trigger of view is:" << view->editTriggers();
                                   //Change this flag to set only that cell editable
                                   Qt::ItemFlags flag = view->currentIndex().flags();
                                   //flag.setFlag(Qt::ItemIsEditable,true);//not working
                                    //qDebug() << "Flag of current index is:" << flag;
                                    view->setEditTriggers(QAbstractItemView::SelectedClicked);
                              }
                              else if(button_dynamic->text()=="Save"){
                                  //modelLoop->setData(modelLoop->index(0,0),75000);
//                                  modelLoop->dataChanged();
//                                  QModelIndexList tableIndexes = view->selectionModel()->selectedRows();
                                  //emit signal_clickedRow(i);
                                  //viewfaccustsqlmod->clicked_row = i;
//                                  qDebug() << "clicked_row is:" << viewfaccustsqlmod->clicked_row;
                                  QModelIndex tableIndexes = view->model()->index(i,0,QModelIndex());//this should only return that particular cell. So 0, should be replaced by that number //also why not use modelLoop directly instead of view->model()?
                                   QString receivedStr = view->model()->data(view->currentIndex()).toString();//receives currently selected cell

                                   //view->model()-> use this for delete
//                                  for(int i = 0; i< tableIndexes.length(); i++)
//                                  {qDebug() << "tableIndex selected is:" << tableIndexes[i];
//                                  }
                                  view->edit(tableIndexes);
                                  // qDebug() << "Received string from table is:" << receivedStr;
                                  //qDebug() << "tableIndex selected is:" << tableIndexes;
                                  //view->edit(view->currentIndex());
                                  //view->setItemDelegateForRow(i, new QItemDelegate);
//                                  connect(view,&QTableView::activated,[&](){
//                                      qDebug()<< "row activated";
//                                  });

                                  button_dynamic->setText("Edit");
                                  if(view->currentIndex().row() == i){
                                      modelLoop->submitAll();
                                      view->setEditTriggers(QAbstractItemView::NoEditTriggers);
                                  }
                                  else{
                                      QMessageBox::warning(this,tr("Error"),tr("Clicked on wrong save button"),QMessageBox::Retry);
                                  }

                              }
                          });
                  connect(button_dynamic_delete,&QPushButton::clicked,[button_dynamic_delete,button_dynamic,view,i,modelLoop, this,layoutVButtons,layoutVButtonsDelete](){
                      if(QMessageBox::question(this,tr("System:"),tr("Are you sure you want to delete this entry?"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes){
                          modelLoop->setEditStrategy(QSqlTableModel::OnManualSubmit);//apply all these strategies only to a particular row and particular columns
                          view->setSelectionMode(QAbstractItemView::SingleSelection);//modify these two
                          view->setSelectionBehavior(QAbstractItemView::SelectItems);
                           view->selectRow(i);
                           view->setEditTriggers(QAbstractItemView::SelectedClicked);
                        QModelIndex tableIndexes = view->model()->index(i,0,QModelIndex());//this should only return that particular cell. So 0, should be replaced by that number //also why not use modelLoop directly instead of view->model()?
                        bool is_row_removed = modelLoop->removeRow(tableIndexes.row());
                        modelLoop->submitAll();
                        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
                        button_dynamic->deleteLater();
                        button_dynamic_delete->deleteLater();
                        qDebug()<<"Is row removed?: "<<is_row_removed;
                      }

                  });

              }
//ui->viewFacultybBckButton->setParent(ui->scrollArea);
//              ui->viewFacultybBckButton->setParent(contentWidget);
//               contentWidget->layout()->addWidget(label);
//                contentWidget->layout()->addWidget(view);
               // contentWidget->layout()->addWidget(ui->viewFacultybBckButton);
//           label->show();
//           view->show();
              //layoutH->addLayout(layoutVButtons);
              //layoutMergeWithTables->addLayout(layoutVButtons);
             //layoutH->addLayout(layoutMergeWithTables);
           start_y = start_y+240;
       }
//      QScrollBar *scrollbarV = new QScrollBar;
       // contentWidget->layout()->addWidget(ui->viewFacultybBckButton);

        //ui->scrollArea->addScrollBarWidget(scrollbarV,Qt::AlignRight);

              contentWidget->setLayout(layoutG);
     //contentWidget->layout()->addWidget(ui->scrollArea);

//       //contentWidget->setMaximumWidth(365);


       QScrollArea *scrollArea = new QScrollArea();
//       ui->scrollAreaWidgetContents->isFullScreen();
       scrollArea->setWidget(contentWidget);
       ui->viewFacultybBckButton->setParent(scrollArea);
       ui->viewFacultybBckButton->setGeometry(700,30,50,30);
//       //scrollArea->setMaximumWidth(365);
       setCentralWidget(scrollArea);
//layout->addWidget(label);
//layout->addWidget(view);
//window->show();
        //    view->show();
//       ui->tableView->setModel(model);
//       ui->tableView->show();

 //ui->scrollArea->setWidgetResizable(true);
       /*setCentralWidget(ui->scrollArea);*///check forums

}

ViewFaculty::~ViewFaculty()
{
    delete ui;
}
void ViewFaculty::closeEvent(QCloseEvent *event){
    if(QMessageBox::question(this,tr("System:"),tr("Are you sure you want to close this window?"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes){
        emit on_viewfacultycloseButtonClicked();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void ViewFaculty::on_viewFacultybBckButton_clicked()
{

}

void ViewFaculty::changeTextEditButton(QPushButton *button_d){
    if(button_d->text()=="Edit"){
        button_d->setText("Save");
    }
    else if(button_d->text()=="Save"){
        button_d->setText("Edit");
    }
}

//Qt::ItemFlags QSqlTableModel::flags(const QModelIndex& index) const {
//    Qt::ItemFlags flags;
//    flags = QSqlTableModel::flags(index);

//    if(index.row()== ViewFaculty::clicked_row)
//    {flags |= Qt::ItemIsEditable;
//        return flags;
//        }
//    return (QSqlTableModel::flags(index) & ~Qt::ItemIsEditable);
//}
