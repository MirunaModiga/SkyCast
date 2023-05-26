#include "requestregister.h"
#include "cexceptie.h"
#include "getweather.h"
#include "requestlogin.h"

QString RequestRegister::favcity=QString("");
getWeather RequestRegister::WeatherData=getWeather();

RequestRegister::RequestRegister(QString user,QString pass,QString Email,QString cty)
{
    QString bara{"/"};
    QString unu{"0"};
   //username,password,email
    creds.append(unu);
    creds.append(bara);
    creds.append(user);
    creds.append(bara);
    creds.append(pass);
    creds.append(bara);
    creds.append(Email);
    creds.append(bara);
    creds.append(cty);
    RequestRegister::favcity=cty; //butonul de back
    RequestLogin::favcity=cty; //butonul de back
    creds.append(bara);
}

bool RequestRegister::_request()
{
    // 1/username/password
    // 2/username/pass/reg/...
    QString data=tcpclient::getInstance().getData(creds);

    if(data!="NOK"){
        WeatherData.splitMessageWeather(data);
        return true;
    }
    /*else{
        CExceptie exc;
        exc.crashApp();
    }*/
    return false;

}
