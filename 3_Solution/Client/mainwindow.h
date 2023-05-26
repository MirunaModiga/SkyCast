#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include"getweather.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, const getWeather& weatherData = getWeather());
    ~MainWindow();

private slots:

    void on_pushButton_Search_clicked();

    void on_pushButton_back_clicked();

    void on_pag2_clicked();

    void on_pag1_clicked();

    void on_pushButton_refresh_clicked();

private:
    Ui::MainWindow *ui;
    getWeather *m_WeatherData;
};

#endif // MAINWINDOW_H
