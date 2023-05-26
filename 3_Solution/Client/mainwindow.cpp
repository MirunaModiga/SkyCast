#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include"cexceptie.h"
#include "requestcity.h"
#include "requestlogin.h"
#include "requestlogout.h"
#include "requestregister.h"
#include "requestback.h"
#include "skycast.h"
#include "QScrollArea"
#include "QDate"

MainWindow::MainWindow(QWidget *parent, const getWeather& weatherData) :
    QDialog(parent),
    ui(new Ui::MainWindow),
    m_WeatherData(new getWeather(weatherData))
{
    ui->setupUi(this);
    ui->lineEdit_SearchBar->setPlaceholderText("Search City");

    //Afiseaza date meteo
    ui->label_NameCity->setText(m_WeatherData->city()); //afiseaza numele orasului de resedinta
    ui->label_temp->setText(QString::number(m_WeatherData->temperature()) + "°C"); //afiseaza temperatura orasului de resedinta
    ui->label_feelsLike->setText(QString::number(m_WeatherData->feelsLike()) + "°C"); //detaliile orasului de resedinta
    ui->label_clouds->setText(QString::number(m_WeatherData->cloud())+"%");
    ui->label_humidity->setText(QString::number(m_WeatherData->humidity())+"%");
    ui->label_minTemp->setText(QString::number(m_WeatherData->minTemp())+"°C");
    ui->label_maxTemp->setText(QString::number(m_WeatherData->maxTemp())+"°C");
    ui->label_windSpeed->setText(QString::number(m_WeatherData->windSpeed())+"km/h");
    ui->label_sunrise->setText(m_WeatherData->sunriseTime());
    ui->label_sunset->setText(m_WeatherData->sunsetTime());

    //alinierea temperaturilor
    ui->label_temp->setAlignment(Qt::AlignCenter);
    ui->label_feelsLike->setAlignment(Qt::AlignCenter);
    ui->label_clouds->setAlignment(Qt::AlignCenter);
    ui->label_humidity->setAlignment(Qt::AlignCenter);
    ui->label_minTemp->setAlignment(Qt::AlignCenter);
    ui->label_maxTemp->setAlignment(Qt::AlignCenter);
    ui->label_windSpeed->setAlignment(Qt::AlignCenter);
    ui->label_sunrise->setAlignment(Qt::AlignCenter);
    ui->label_sunset->setAlignment(Qt::AlignCenter);

    //label date vreme nume
    ui->label_NameCity->setAlignment(Qt::AlignCenter);
    ui->label_FeelsLike->setAlignment(Qt::AlignCenter);
    ui->label_Humidity->setAlignment(Qt::AlignCenter);
    ui->label_Clouds->setAlignment(Qt::AlignCenter);
    ui->label_MinTemp->setAlignment(Qt::AlignCenter);
    ui->label_MaxTemp->setAlignment(Qt::AlignCenter);
    ui->label_WindSpeed->setAlignment(Qt::AlignCenter);


    //setare iconite rasarit si apus
    QPixmap iconSunrise(":/resources/img/sunrise.png");
    ui->label_Sunrise->setPixmap(iconSunrise);
    QPixmap iconSunset(":/resources/img/sunset.png");
    ui->label_Sunset->setPixmap(iconSunset);

    //alinierea lor
    ui->label_Sunrise->setAlignment(Qt::AlignCenter);
    ui->label_Sunset->setAlignment(Qt::AlignCenter);


    //iconite MARI vreme in functie de conditiile meteo(soare,nori,ploaie,etc)
    QPixmap icon;

    if (m_WeatherData->temperature() > 25 && m_WeatherData->humidity() > 60 && m_WeatherData->windSpeed() < 10 && m_WeatherData->cloud() < 30) {
            icon.load(":/resources/img/sunny.png");
        }
    else if (m_WeatherData->temperature() > 25 && m_WeatherData->humidity() < 50 && m_WeatherData->windSpeed() < 10 && m_WeatherData->cloud() < 30) {
            icon.load(":/resources/img/sunny.png");
        }
    else if (m_WeatherData->temperature() >= 20 && m_WeatherData->cloud() > 20) {
            icon.load(":/resources/img/sunny-clouds.png");
    }
    else if(m_WeatherData->temperature() >= 20 && m_WeatherData->cloud() < 50){
            icon.load(":/resources/img/sunny-clouds.png");
    } else if (m_WeatherData->cloud() >= 50 && m_WeatherData->temperature() > 15 && m_WeatherData->temperature() < 25) {
            icon.load(":/resources/img/clouds.png");
    } else if (m_WeatherData->cloud() >= 50 && m_WeatherData->temperature() > 10 && m_WeatherData->temperature() <= 15) {
            icon.load(":/resources/img/sunny-clouds-rain.png");
    } else if (m_WeatherData->cloud() >= 50 && m_WeatherData->temperature() > 15 && m_WeatherData->temperature() <= 25) {
            icon.load(":/resources/img/clouds-rain.png");
    } else if (m_WeatherData->windSpeed() > 25 && m_WeatherData->temperature() > 10 && m_WeatherData->temperature() <= 25) {
            icon.load(":/resources/img/wind.png");
    } else if (m_WeatherData->temperature() <= 10) {
            icon.load(":/resources/img/sunny-clouds.png");
    } else if (m_WeatherData->temperature() < 20  && m_WeatherData->cloud() < 50 && m_WeatherData->windSpeed() <25){
            icon.load(":/resources/img/sunny-clouds.png");
    }else
    {
            icon.load(":/resources/img/unknown.png");
    }

    ui->label_Icon->setPixmap(icon);
    ui->label_Icon->setAlignment(Qt::AlignCenter);



    //A doua pagina din stacked Widget

    //orele
    ui->ora1_temp1->setText("00:00");
    ui->ora2_temp2->setText("03:00");
    ui->ora3_temp3->setText("06:00");
    ui->ora4_temp4->setText("09:00");
    ui->ora5_temp5->setText("12:00");
    ui->ora6_temp6->setText("15:00");
    ui->ora7_temp7->setText("18:00");
    ui->ora8_temp8->setText("21:00");
    //temperaturile de la fiecare ora
    ui->temp1_ora1->setText(QString ::number(m_WeatherData->hourlyTemperatures()[0]) + "°C");
    ui->temp2_ora2->setText(QString ::number(m_WeatherData->hourlyTemperatures()[1]) + "°C");
    ui->temp3_ora3->setText(QString ::number(m_WeatherData->hourlyTemperatures()[2]) + "°C");
    ui->temp4_ora4->setText(QString ::number(m_WeatherData->hourlyTemperatures()[3]) + "°C");
    ui->temp5_ora5->setText(QString ::number(m_WeatherData->hourlyTemperatures()[4]) + "°C");
    ui->temp6_ora6->setText(QString ::number(m_WeatherData->hourlyTemperatures()[5]) + "°C");
    ui->temp7_ora7->setText(QString ::number(m_WeatherData->hourlyTemperatures()[6]) + "°C");
    ui->temp8_ora8->setText(QString ::number(m_WeatherData->hourlyTemperatures()[7]) + "°C");
    //aliniere
    ui->temp1_ora1->setAlignment(Qt::AlignCenter);
    ui->temp2_ora2->setAlignment(Qt::AlignCenter);
    ui->temp3_ora3->setAlignment(Qt::AlignCenter);
    ui->temp4_ora4->setAlignment(Qt::AlignCenter);
    ui->temp5_ora5->setAlignment(Qt::AlignCenter);
    ui->temp6_ora6->setAlignment(Qt::AlignCenter);
    ui->temp7_ora7->setAlignment(Qt::AlignCenter);
    ui->temp8_ora8->setAlignment(Qt::AlignCenter);

    //temperaturile la zilele dintr o saptamana
    ui->max1_zi1->setText(QString::number(m_WeatherData->maxTemps()[0]) + "°C");
    ui->max2_zi2->setText(QString::number(m_WeatherData->maxTemps()[1]) + "°C");
    ui->max3_zi3->setText(QString::number(m_WeatherData->maxTemps()[2]) + "°C");
    ui->max4_zi4->setText(QString::number(m_WeatherData->maxTemps()[3]) + "°C");
    ui->max5_zi5->setText(QString::number(m_WeatherData->maxTemps()[4]) + "°C");
    ui->max6_zi6->setText(QString::number(m_WeatherData->maxTemps()[5]) + "°C");
    ui->max7_zi7->setText(QString::number(m_WeatherData->maxTemps()[6]) + "°C");

    ui->min1_zi1->setText(QString::number(m_WeatherData->minTemps()[0]) + "°C");
    ui->min2_zi2->setText(QString::number(m_WeatherData->minTemps()[1]) + "°C");
    ui->min3_zi3->setText(QString::number(m_WeatherData->minTemps()[2]) + "°C");
    ui->min4_zi4->setText(QString::number(m_WeatherData->minTemps()[3]) + "°C");
    ui->min5_zi5->setText(QString::number(m_WeatherData->minTemps()[4]) + "°C");
    ui->min6_zi6->setText(QString::number(m_WeatherData->minTemps()[5]) + "°C");
    ui->min7_zi7->setText(QString::number(m_WeatherData->minTemps()[6]) + "°C");
    //aliniere
    ui->max1_zi1->setAlignment(Qt::AlignCenter);
    ui->max2_zi2->setAlignment(Qt::AlignCenter);
    ui->max3_zi3->setAlignment(Qt::AlignCenter);
    ui->max4_zi4->setAlignment(Qt::AlignCenter);
    ui->max5_zi5->setAlignment(Qt::AlignCenter);
    ui->max6_zi6->setAlignment(Qt::AlignCenter);
    ui->max7_zi7->setAlignment(Qt::AlignCenter);
    ui->min1_zi1->setAlignment(Qt::AlignCenter);
    ui->min2_zi2->setAlignment(Qt::AlignCenter);
    ui->min3_zi3->setAlignment(Qt::AlignCenter);
    ui->min4_zi4->setAlignment(Qt::AlignCenter);
    ui->min5_zi5->setAlignment(Qt::AlignCenter);
    ui->min6_zi6->setAlignment(Qt::AlignCenter);
    ui->min7_zi7->setAlignment(Qt::AlignCenter);


    //vremea pe o saptamana
    QDate currentDate = QDate::currentDate();
    std::vector<QString>days;
    for (int i = 0; i < 7; i++) {
        // Adaugă ziua la mesaj
        days.push_back(currentDate.toString("dddd"));//sablon de formatare;specifica ca se doreste afisarea numelor complet

        // Treci la următoarea zi
        currentDate = currentDate.addDays(1);//actualizeaza currentDate trecand la ziua urmatoare
    }

    //numele zilelor pe o saptamana; ziua 0 e current date
    ui->zi1->setText(days[0]);
    ui->zi2->setText(days[1]);
    ui->zi3->setText(days[2]);
    ui->zi4->setText(days[3]);
    ui->zi5->setText(days[4]);
    ui->zi6->setText(days[5]);
    ui->zi7->setText(days[6]);
    //aliniere
    ui->zi1->setAlignment(Qt::AlignCenter);
    ui->zi2->setAlignment(Qt::AlignCenter);
    ui->zi3->setAlignment(Qt::AlignCenter);
    ui->zi4->setAlignment(Qt::AlignCenter);
    ui->zi5->setAlignment(Qt::AlignCenter);
    ui->zi6->setAlignment(Qt::AlignCenter);
    ui->zi7->setAlignment(Qt::AlignCenter);

    //iconite in functie de temperatura medie din ziua respectiva pentru fiecare zi din spatamana in parte
    QPixmap iconZi1(":/resources/img/"+m_WeatherData->codes()[0]+".png");
    QPixmap iconZi2(":/resources/img/"+m_WeatherData->codes()[1]+".png");
    QPixmap iconZi3(":/resources/img/"+m_WeatherData->codes()[2]+".png");
    QPixmap iconZi4(":/resources/img/"+m_WeatherData->codes()[3]+".png");
    QPixmap iconZi5(":/resources/img/"+m_WeatherData->codes()[4]+".png");
    QPixmap iconZi6(":/resources/img/"+m_WeatherData->codes()[5]+".png");
    QPixmap iconZi7(":/resources/img/"+m_WeatherData->codes()[6]+".png");
    ui->iconita_zi1->setPixmap(iconZi1);
    ui->iconita_zi2->setPixmap(iconZi2);
    ui->iconita_zi3->setPixmap(iconZi3);
    ui->iconita_zi4->setPixmap(iconZi4);
    ui->iconita_zi5->setPixmap(iconZi5);
    ui->iconita_zi6->setPixmap(iconZi6);
    ui->iconita_zi7->setPixmap(iconZi7);

    //alerte
    if(m_WeatherData->alerts().size() != 0)
    {
        for(int i=0;i<(int)m_WeatherData->alerts().size();i++){
            if(m_WeatherData->alerts()[i]!="" && m_WeatherData->alerts()[i] != "NOK"){
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText(m_WeatherData->alerts()[i]);
                msgBox.exec();
                break;
            }
        }
    }


    //poza buton refresh
    QPixmap iconRefresh(":/resources/img/transparent-refresh.png");
    ui->pushButton_refresh->setIcon(iconRefresh);
}

MainWindow::~MainWindow()
{
    RequestLogout logout;
           if(logout._request()){
              qDebug()<<"Logout succeded!";
              tcpclient::getInstance().stop();
              tcpclient::destroyInstance();
            }
    delete m_WeatherData;
    delete ui;
}

void MainWindow::on_pushButton_Search_clicked()
{
    QString searchBar = ui->lineEdit_SearchBar->text();

    if(searchBar==' '){
          CExceptie exc;
          exc.LoginError();
    }


    RequestCity req(searchBar);

    if(req._request()){
        this->hide();
        delete m_WeatherData;

        getWeather weatherData = RequestCity::WeatherData;
        RequestCity::WeatherData.setAlerts({""});
        MainWindow mainWindow(nullptr, weatherData);
        mainWindow.setModal(true);
        mainWindow.resize(900,600);
        mainWindow.show();
        mainWindow.exec();

    }
    else{
        CExceptie exc;
        exc.WrongCity();
    }


}


void MainWindow::on_pushButton_back_clicked()
{
    RequestCity req(RequestLogin::favcity);

    if(req._request()){
        this->hide();
        delete m_WeatherData;

        if(RequestRegister::favcity!=QString("")){
            MainWindow mainWindow(nullptr,RequestRegister::WeatherData);
            mainWindow.setModal(true);
            mainWindow.resize(900,600);
            mainWindow.show();
            mainWindow.exec();
        }
        else{
            MainWindow mainWindow(nullptr,RequestLogin::WeatherData);
            mainWindow.setModal(true);
            mainWindow.resize(900,600);
            mainWindow.show();
            mainWindow.exec();
        }
    }
    else{
        CExceptie exc;
        exc.WrongCity();
    }
}

void MainWindow::on_pag2_clicked()
{
    ui->page_2->hide();
    ui->page->resize(900,600);
    ui->page->show();
}

void MainWindow::on_pag1_clicked()
{
    ui->page->hide();
    ui->page_2->resize(900,600);
    ui->page_2->show();
}


void MainWindow::on_pushButton_refresh_clicked()
{
    QString cityRefresh = m_WeatherData->city();

    RequestCity req(cityRefresh);

    if(req._request()){
        this->hide();

        getWeather weatherData = RequestCity::WeatherData;
        MainWindow mainWindow(nullptr, weatherData);
        mainWindow.setModal(true);
        mainWindow.resize(900,600);
        mainWindow.show();
        mainWindow.exec();
    }
    else{
        CExceptie exc;
        exc.WrongCity();
    }
}

