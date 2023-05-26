#include "skycast.h"
#include "ui_skycast.h"

SkyCast::SkyCast(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SkyCast)
{
    ui->setupUi(this);
    QPixmap icon(":/resources/img/WhatsApp Image 2023-05-04 at 12.12.03.jpeg");
    ui->label_2->setPixmap(icon);
    QPixmap icon2(":/resources/img/SkyCastLogo.png");
    ui->label->setPixmap(icon2);
}

SkyCast::~SkyCast()
{
    delete ui;
}

void SkyCast::on_pushButton_SignIn_clicked()
{
    hide();
    SignIn signin;
    signin.setModal(true);
    signin.show();
    signin.resize(900,600);
    signin.exec();

}


void SkyCast::on_pushButton_LogIn_clicked()
{
    hide();
    LogIn login;
    login.setModal(true);
    login.show();
    login.resize(900,600);
    login.exec();
}

