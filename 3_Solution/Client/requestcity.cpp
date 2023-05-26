#include "requestcity.h"
#include "cexceptie.h"
#include "getweather.h"

getWeather RequestCity::WeatherData=getWeather();

RequestCity::RequestCity(QString cty)
{
    QString bara{"/"};
    QString doi{"2"};
   //city
    creds.append(doi);
    creds.append(bara);
    creds.append(cty);
    creds.append(bara);
}

bool RequestCity::_request()
{
    // 2/city/
    QString data=tcpclient::getInstance().getData(creds);

    /*if(data!="NOK"){
        WeatherData.splitMessageWeather(data);
        return true;
    }
    else{
      CExceptie exc;
      exc.WrongCity();

      CExceptie exc1;
      exc1.crashApp();

    }*/


    if(data=="wrong city"){
        CExceptie exc;
        exc.WrongCity();
    }
    else if(data=="eroare API"){
        CExceptie exc1;
        exc1.crashApp();
    }
    else{
        WeatherData.splitMessageWeather(data);
        return true;
    }

    return false;

}

