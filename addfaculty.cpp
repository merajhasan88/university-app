#include "addfaculty.h"
#include "ui_addfaculty.h"
#include <QTextStream>
#include <QtWidgets>
#include <QFileSystemModel>
#include <QCloseEvent>
#include <QDebug>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
using namespace cv;
AddFaculty::AddFaculty(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AddFaculty)
{
    ui->setupUi(this);
    connect(ui->addfacbackButton, SIGNAL(clicked()),this, SLOT(close()));


    ui->addfacgraphicsView->setScene(scene);
}

AddFaculty::~AddFaculty()
{
    delete ui;
}

void AddFaculty::on_addPhoto_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
            "/home/developer/Pictures");
    if (!fileName.isEmpty()) {
        QImage tempImage(fileName);
        if (tempImage.isNull()) {
            QMessageBox::information(this, tr("Load Warning"), tr("Cannot load %1.").arg(fileName));
            return;
        }
        scene->clear();
        unsigned int numBlackPixels = 0;
        QImage image = tempImage.convertToFormat(QImage::Format_RGB32);
        QVector<QVector<int>> imgArray(image.height(),QVector<int>(image.width(),0));
        for(unsigned int i =0; i< image.height();i++){
            for(unsigned int j =0; j< image.width();j++){
                QColor clrCurrent(image.pixel(j,i));
                int r = clrCurrent.red();
                int g = clrCurrent.green();
                int b = clrCurrent.blue();
                int a = clrCurrent.alpha();
                if(r+g+b <20 && a > 240){
                    imgArray[i][j] = 1;
                    //qDebug() << imgArray[i][j];
                    numBlackPixels+=1;
                }
                else {
                    imgArray[i][j] = 0;
                    //qDebug() << imgArray[i][j];
                }
            }
        }
        qDebug() <<"black pixels are" <<numBlackPixels;
        //qDebug() <<"imgArray is:" <<imgArray;
        src= imread(samples::findFile(fileName.toStdString()),IMREAD_COLOR);
        dst.create(src.size(),src.type());
        cvtColor(src,src_gray,COLOR_BGR2GRAY);
        namedWindow(window_name, WINDOW_AUTOSIZE);
        blur(src_gray, detected_edges, Size(3,3));
        Canny(detected_edges,detected_edges, lowThreshold,lowThreshold*ratio, kernel_size);
        dst = Scalar::all(0);
        src.copyTo(dst,detected_edges);

       createTrackbar("Min Threshold:",window_name, &lowThreshold, max_lowThreshold);
        //CannyThreshold(0,0);
       imshow(window_name,dst);
       waitKey(0);

        QPixmap pixmap = QPixmap::fromImage(image);
        //ui->addfacgraphicsView->setFixedSize(image.width(),image.height());
        //int width = ui->graphicsView->geometry().width();
        //int height = ui->graphicsView->geometry().height();
        //	        QMessageBox::information(this, tr("WIDTH HEIGHT"), tr("Width= %1 Height= %2").arg(QString::number(width, 10), QString::number(height, 10)));
        //QGraphicsScene *viewScene = new QGraphicsScene(QRectF(0, 0, width, height), 0);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        scene->addItem(item);
        scene->setSceneRect(0,0,image.width(),image.height());
//        int addfacgrwidth = ui->addfacgraphicsView->geometry().width();
//        int addfacgrheight = ui->addfacgraphicsView->geometry().height();
//        int imagew = image.width();
//        int imageh = image.height();
//        addfacgrheight = imageh;
//        addfacgrwidth = imagew;

//        ui->addfacgraphicsView->setScene(scene);
//        if(image.height()<ui->addfacgraphicsView->height() || image.width()<ui->addfacgraphicsView->width()){
//            ui->addfacgraphicsView->setFixedSize(image.width(),image.height());
//           // ui->addfacgraphicsView->resize(image.width(),image.height());
//            ui->addfacgraphicsView->setMinimumWidth(image.width());
//            ui->addfacgraphicsView->setMinimumHeight(image.height());
//            ui->addfacgraphicsView->setFixedSize(image.width(),image.height());
//            ui->addfacgraphicsView->setMinimumSize(image.size());
//            ui->addfacgraphicsView->setMaximumSize(image.size());
//        ui->addfacgraphicsView->ensureVisible(scene->sceneRect());
//        ui->addfacgraphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
//        ui->addfacgraphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
//        ui->addfacgraphicsView->show();
//        }
//        else{
        ui->addfacgraphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
        //ui->addfacgraphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);//try and remove the white border here by changing size of the graphics vew
        //}
        }
}

void AddFaculty::closeEvent(QCloseEvent *event){
    if(QMessageBox::question(this,tr("System:"),tr("Are you sure you want to close this window?"),QMessageBox::Yes,QMessageBox::No )==QMessageBox::Yes){
        emit on_facultycloseButtonClicked();
        event->accept();
    }
    else {
        event->ignore();
    }
}

void AddFaculty::showEvent(QShowEvent *event){//change this to dialog
//    ui->addfacgraphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}



void AddFaculty::on_addfacbackButton_clicked()
{

}

void AddFaculty::resizeEvent(QResizeEvent* event)
{
   // ui->graphicsView->resize(event->size());
   QMainWindow::resizeEvent(event);
}
//void AddFaculty::CannyThreshold(int, void*){
//    blur(src_gray, detected_edges, Size(3,3));
//    Canny(detected_edges,detected_edges, lowThreshold,lowThreshold*ratio, kernel_size);
//    dst = Scalar::all(0);
//    src.copyTo(dst,detected_edges);
//    imshow(window_name,dst);
//}
