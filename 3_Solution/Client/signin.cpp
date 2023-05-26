#include "signin.h"
#include "ui_signin.h"
#include<QMessageBox>
#include <tcpclient.h>
#include "requestregister.h"
#include "cexceptie.h"
#include "skycast.h"
#include "requestback.h"

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    ui->lineEdit_usernameSignIn->setPlaceholderText("Enter your username");
    ui->lineEdit_passwordSignIn->setPlaceholderText("Enter password");
    ui->lineEdit_emailSignIn->setPlaceholderText("Enter your Email");
    ui->lineEdit_citySignIn->setPlaceholderText("Enter your city of residence");
    QPixmap icon(":/resources/img/WhatsApp Image 2023-05-04 at 12.12.03.jpeg");
    ui->label_2->setPixmap(icon);
    QPixmap icon2(":/resources/img/SkyCastLogo.png");
    ui->label->setPixmap(icon2);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_pushButton_SignInConnect_clicked()
{
    QString username = ui->lineEdit_usernameSignIn->text();
    QString password = ui->lineEdit_passwordSignIn->text();
    QString email = ui->lineEdit_emailSignIn->text();
    QString city = ui->lineEdit_citySignIn->text();


    RequestRegister req(username,password,email,city); //seteaza datele de conectare

    if(req._request()){
        tcpclient::setUsername(username);
        QMessageBox::information(this,"SignIn","Congratulation! Enjoy your search!");
        this->hide();

        getWeather weatherData = RequestRegister::WeatherData;
        MainWindow mainWindow(nullptr, weatherData);
        mainWindow.setModal(true);
        mainWindow.resize(900,600);
        mainWindow.show();
        mainWindow.exec();
    }
    else{
        CExceptie exc;
        exc.RegisterError();
    }

}

void SignIn::on_pushButton_BackSignIn_clicked()
{
    RequestBack back;
           if(back._request()){
               this->hide();
               SkyCast * skycast=new SkyCast(this->parentWidget());

               skycast->resize(900,600);
               skycast->show();
            } else{
               CExceptie exc;
               exc.WaitedforToMuchTime();
           }


}
