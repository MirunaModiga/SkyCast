#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QString>
#include <QMainWindow>
#include "mainwindow.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_pushButton_SignInConnect_clicked();

    void on_pushButton_BackSignIn_clicked();

private:
    Ui::SignIn *ui;
};

#endif // SIGNIN_H
