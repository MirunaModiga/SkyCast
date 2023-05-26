#include "normaluser.h"
#include"requestlogin.h"
normaluser::normaluser(QString usern, QString passwd):cuser(usern,passwd)
{
}

bool normaluser::sendCredentials()
{
  QString bara{"/"};
  QString unu{"1"};
  QString credentials;
  credentials.reserve(username.length()+unu.length()+bara.length()+bara.length()+password.length());
  credentials.append(unu);
  credentials.append(bara);
  credentials.append(username);
  credentials.append(bara);
  credentials.append(password);
  credentials.append(bara);
  //request catre server
  RequestLogin req(credentials);
  return req._request();
  //send to server
  //return requestlogin...


}

bool normaluser::verifyconfirmation(QString passwd)
{
    if(this->password==passwd)
    {
        return true;
    }
    return false;
}
