#include "unimain.h"
//#include "addcourse.h"
//#include "viewfaculty.h"
#include "loginprompt.h"
#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //UniMain w;
    loginPrompt prompt;
    //ViewFaculty v;
    //AddCourse addC;
    //w.show();
    prompt.show();

//    bool addCourseFlag;
    //addCourseFlag = w.on_addCourse_clicked();
    //addCourseFlag;
    //UniMain::on_addCourse_clicked();
    //addCourseFlag = on_addCourse_clicked();
//    if(w.addCourseFlag){
//        //w.hide();
      QTextStream out(stdout);
//        //qStdOut() << searchString;
//        out << "In Main with ID:" <<Qt::endl;
//        w.wID = w.winId();
//        out << w.wID <<Qt::endl;
//    }
    return a.exec();
}
QTextStream& qStdOut1()
{
    static QTextStream ts( stdout );
    return ts;
}
