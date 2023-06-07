#ifndef ADDFACULTY_H
#define ADDFACULTY_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
namespace Ui {
class AddFaculty;
}
using namespace cv;
class AddFaculty : public QMainWindow
{
    Q_OBJECT

public:
    Mat src, src_gray;
    Mat dst, detected_edges;
    int lowThreshold = 50;
    const int max_lowThreshold = 100;
    const int ratio = 3;
    const int kernel_size = 3;
    const char* window_name = "Edge Map";
    QGraphicsScene *scene = new QGraphicsScene(this);
    explicit AddFaculty(QWidget *parent = nullptr);
    ~AddFaculty();
signals:
    void on_facultycloseButtonClicked();
public slots:
    //static void CannyThreshold(int, void*);
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);
private slots:
    void on_addPhoto_clicked();


void showEvent(QShowEvent *event);


void on_addfacbackButton_clicked();

private:
    Ui::AddFaculty *ui;
};

#endif // ADDFACULTY_H
