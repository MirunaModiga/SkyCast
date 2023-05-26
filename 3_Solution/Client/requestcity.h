#ifndef REQUESTCITY_H
#define REQUESTCITY_H

#include "irequest.h"


class RequestCity : public IRequest
{
protected:
    QString creds;
public:
    RequestCity(){creds=QString("");}
    RequestCity(QString cty);
    ~RequestCity(){}
    bool _request();
    static getWeather WeatherData;
};

#endif // REQUESTCITY_H
