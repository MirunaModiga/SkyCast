#include "requestlogin.h"
#include<QDebug>
#include "getweather.h"
#include "cexceptie.h"

QString RequestLogin::favcity=QString("");
getWeather RequestLogin::WeatherData=getWeather();

RequestLogin::RequestLogin(QString credentials):creds(credentials)
{

}

bool RequestLogin::_request()
{
    //send creds to server
    QString data=tcpclient::getInstance().getData(creds);

    if (creds.contains("//")) {
        return false;
    }

    if(data!="NOK"){
        QString copy=data;
        QString part = copy.split('/', Qt::SkipEmptyParts).at(0);
        RequestLogin::favcity=part;
        WeatherData.splitMessageWeather(data);
        return true;
    }
    //else{
    //    CExceptie exc;
    //    exc.crashApp();
    //}
    return false;
}
