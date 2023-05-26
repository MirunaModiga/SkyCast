#include "getweather.h"
#include <QDateTime>
#include <QDebug>
#include <QTime>

getWeather::getWeather(const getWeather& weatherData){
    this->city_=weatherData.city_; //nu inteleg aici
    this->temperature_=weatherData.temperature_;
    this->feels_like_=weatherData.feels_like_;
    this->cloud_=weatherData.cloud_;
    this->humidity_=weatherData.humidity_;
    this->min_temp_=weatherData.min_temp_;
    this->max_temp_=weatherData.max_temp_;
    this->wind_speed_= weatherData.wind_speed_;
    this->sunrise_time_=weatherData.sunrise_time_;
    this->sunset_time_=weatherData.sunset_time_;
    this->hourly_temperatures_=weatherData.hourly_temperatures_;
    this->min_temps_=weatherData.min_temps_;
    this->max_temps_=weatherData.max_temps_;
    this->codes_=weatherData.codes_;
    this->alerts_=weatherData.alerts_;
}

void getWeather::splitMessageWeather(QString serverMessage)
{
    QStringList parts = serverMessage.split('/');

    this->setCity(parts[0]);

    if (parts.size() >= 10) {
        this->setTemperature(parts[1].toDouble());
        this->setFeelsLike(parts[2].toDouble());
        this->setCloud((parts[3]).toInt());
        this->setHumidity(parts[4].toDouble());
        this->setMinTemp(parts[5].toDouble());
        this->setMaxTemp(parts[6].toDouble());
        this->setWindSpeed(parts[7].toDouble());
        this->setSunriseTime(parts[8]);
        this->setSunsetTime(parts[9]);
    }

    if (parts.size() >= 18) {
        for (int i = 10; i < 18; i++) {
            (this->hourly_temperatures_).push_back(parts[i].toDouble());
        }
    }

    if (parts.size() >= 40) {
        for (int i = 18; i < 25; i++) {
            this->min_temps_.push_back(parts[i].toDouble());
        }
        for (int i = 25; i < 32; i++) {
            this->max_temps_.push_back(parts[i].toDouble());
        }
        for (int i = 32; i < 39; i++) {
            this->codes_.push_back(parts[i]);
        }

        for (int i = 39; i < parts.size(); i++) {
            this->alerts_.push_back(parts[i]);
        }
    }


}
getWeather::~getWeather(){
    city_="";
    temperature_=0;
    feels_like_=0;
    cloud_=0;
    humidity_=0;
    min_temp_=0;
    max_temp_=0;
    wind_speed_=0;
    sunrise_time_="";
    sunset_time_="";
    hourly_temperatures_.clear();
    min_temps_.clear();
    max_temps_.clear();
    codes_.clear();
    alerts_.clear();
}
