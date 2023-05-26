#include "login.h"
#include "ui_login.h"
#include "tcpclient.h"
#include <QMessageBox>
#include <QString>
#include<QPixmap>
#include "cexceptie.h"
#include "requestback.h"
#include "skycast.h"
#include "requestlogin.h"

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    ui->lineEdit_usernameLogIn->setPlaceholderText("Enter your username");
    ui->lineEdit_passwordLogIn->setPlaceholderText("Enter password");
    QPixmap icon(":/resources/img/WhatsApp Image 2023-05-04 at 12.12.03.jpeg");
    ui->label_2->setPixmap(icon);
    QPixmap icon2(":/resources/img/SkyCastLogo.png");
    ui->label->setPixmap(icon2);

}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_pushButton_LogInConnect_clicked()
{
    QString username = ui->lineEdit_usernameLogIn->text();
    QString password = ui->lineEdit_passwordLogIn->text();

    if(username==""||password==""){
          CExceptie exc;
          exc.LoginError();
    }

    currentuser=new normaluser(username,password);

    if(currentuser->sendCredentials()){
        QMessageBox::information(this, "LogIn", "Username and password is correct");
        this->hide();

        getWeather weatherData = RequestLogin::WeatherData;
        MainWindow mainWindow(nullptr, weatherData);
        mainWindow.resize(900,600);
        mainWindow.exec();
    }
    else{
        CExceptie exc;
        exc.LoginError();
    }

}


void LogIn::on_pushButton_BackLogIn_clicked()
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
