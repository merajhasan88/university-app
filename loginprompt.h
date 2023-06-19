#ifndef LOGINPROMPT_H
#define LOGINPROMPT_H

#include <QDialog>
#include "unimain.h"
namespace Ui {
class loginPrompt;
}

class loginPrompt : public QDialog
{
    Q_OBJECT

public:
    QString username;
    QString password;
    explicit loginPrompt(QWidget *parent = nullptr);
    ~loginPrompt();

private slots:
    void on_loginExitButton_clicked();

    void on_loginSubmitButton_clicked();

private:
    Ui::loginPrompt *ui;
    UniMain *unimain= new UniMain;
};

#endif // LOGINPROMPT_H
