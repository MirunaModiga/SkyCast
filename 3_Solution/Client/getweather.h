#ifndef GETWEATHER_H
#define GETWEATHER_H

#include<QStringList>
#include<QString>

class getWeather
{
private:
    QString city_;
    double temperature_;
    double feels_like_;
    int cloud_;
    int humidity_;
    double min_temp_;
    double max_temp_;
    double wind_speed_;
    QString sunrise_time_;
    QString sunset_time_;
    std::vector<double> hourly_temperatures_;
    std::vector<double> min_temps_;
    std::vector<double> max_temps_;
    std::vector<QString> codes_;
    std::vector<QString> alerts_;

public:
    getWeather(){}
    getWeather(const getWeather& weatherData);

    //gettere
    QString city() const { return city_; }
    double temperature() const { return temperature_; }
    double feelsLike() const { return feels_like_; }
    int cloud() const { return cloud_; }
    int humidity() const { return humidity_; }
    double minTemp() const { return min_temp_; }
    double maxTemp() const { return max_temp_; }
    double windSpeed() const { return wind_speed_; }
    QString sunriseTime() const { return sunrise_time_; }
    QString sunsetTime() const { return sunset_time_; }
    std::vector<double> hourlyTemperatures() const { return hourly_temperatures_; }
    std::vector<double> minTemps() const { return min_temps_; }
    std::vector<double> maxTemps() const { return max_temps_; }
    std::vector<QString> codes() const { return codes_; }
    std::vector<QString> alerts() const { return alerts_; }

    //settere
    void setCity(QString city) { city_ = city; }
    void setTemperature(double temperature) { temperature_ = temperature; }
    void setFeelsLike(double feelsLike) { feels_like_ = feelsLike; }
    void setCloud(int cloud) { cloud_ = cloud; }
    void setHumidity(int humidity) { humidity_ = humidity; }
    void setMinTemp(double minTemp) { min_temp_ = minTemp; }
    void setMaxTemp(double maxTemp) { max_temp_ = maxTemp; }
    void setWindSpeed(double windSpeed) { wind_speed_ = windSpeed; }
    void setSunriseTime(const QString& sunriseTime) { sunrise_time_ = sunriseTime; }
    void setSunsetTime(const QString& sunsetTime) { sunset_time_ = sunsetTime; }
    void setHourlyTemperatures(const std::vector<double>& hourlyTemperatures) { hourly_temperatures_ = hourlyTemperatures; }
    void setMinTemps(const std::vector<double>& minTemps) { min_temps_ = minTemps; }
    void setMaxTemps(const std::vector<double>& maxTemps) { max_temps_ = maxTemps; }
    void setCodes(const std::vector<QString>& codes) { codes_ = codes; }
    void setAlerts(const std::vector<QString>& alerts) { alerts_ = alerts; }


    void splitMessageWeather(QString serverMessage);
    ~getWeather();
};

#endif // GETWEATHER_H
