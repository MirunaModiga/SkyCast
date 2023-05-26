#ifndef SKYCAST_H
#define SKYCAST_H

#include <QMainWindow>
#include "signin.h"
#include "login.h"
QT_BEGIN_NAMESPACE
namespace Ui { class SkyCast; }
QT_END_NAMESPACE

class SkyCast : public QMainWindow
{
    Q_OBJECT

public:
    SkyCast(QWidget *parent = nullptr);
    ~SkyCast();

private slots:
    void on_pushButton_SignIn_clicked();

    void on_pushButton_LogIn_clicked();

private:
    Ui::SkyCast *ui;
    SignIn *signin;
    LogIn *login;

};
#endif // SKYCAST_H
