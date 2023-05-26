#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "normaluser.h"
#include <QPushButton>

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_pushButton_BackLogIn_clicked();

    void on_pushButton_LogInConnect_clicked();

private:
    Ui::LogIn *ui;
    normaluser * currentuser;
};

#endif // LOGIN_H

