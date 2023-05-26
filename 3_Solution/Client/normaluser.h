#ifndef NORMALUSER_H
#define NORMALUSER_H

#include "cuser.h"
#include "getweather.h"

class normaluser : public cuser
{
public:
    normaluser(QString usern,QString passwd);
    ~normaluser(){};
    bool sendCredentials();
    bool verifyconfirmation(QString passwd);
};

#endif // NORMALUSER_H
