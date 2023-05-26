#ifndef REQUESTREGISTER_H
#define REQUESTREGISTER_H

#include "irequest.h"


class RequestRegister : public IRequest
{
protected:
    QString creds;
public:
    RequestRegister(QString usern,QString passwd,QString em, QString cty);
    ~RequestRegister(){};
    bool _request();
    static QString favcity;
    static getWeather WeatherData;

};

#endif // REQUESTREGISTER_H
