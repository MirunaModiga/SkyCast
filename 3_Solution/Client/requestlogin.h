#ifndef REQUESTLOGIN_H
#define REQUESTLOGIN_H

#include "irequest.h"

class RequestLogin : public IRequest
{
protected:
    QString creds;
public:
    RequestLogin(QString credentials);
    ~RequestLogin(){};
    bool _request();
    static QString favcity;
    static getWeather WeatherData;
};

#endif // REQUESTLOGIN_H
