#ifndef UNIMAIN_H
#define UNIMAIN_H

#include <QMainWindow>
#include "addcourse.h"
#include <QtWidgets>
#include "addfaculty.h"
#include "viewfaculty.h"
#include "viewfacultycustomsqlmodel.h"
#include "class_catchclicked_view_faculty.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UniMain; }
QT_END_NAMESPACE
//class AddCourse;
class UniMain : public QMainWindow
{
    Q_OBJECT

public:

    int wID;
//    bool backsignal = false;
    bool addCourseFlag = false;

    //bool on_addCourse_clicked();
    //bool addCourseFlag;
    UniMain(QWidget *parent = nullptr);
    ~UniMain();

private slots:
    void on_addCourse_clicked();
    void destroy_main();
    void closeit(QCloseEvent *event);
    void showMain();

    void on_addFaculty_clicked();

    void on_viewFaculty_clicked();

private:
    Ui::UniMain *ui;
    UniMain *nWin;
    //AddCourse *addCourse;
    AddCourse *addCourse =new AddCourse;
    AddFaculty *addFaculty =new AddFaculty;
    ViewFaculty *viewFaculty = new ViewFaculty;
    ViewFacultyCustomSqlModel *viewfacultycustomsqltablemodel = new ViewFacultyCustomSqlModel;
    Class_catchclicked_view_faculty *class_clicked = new Class_catchclicked_view_faculty;
    //Class_clicked *class_clicked = new Class_clicked;
};
#endif // UNIMAIN_H
