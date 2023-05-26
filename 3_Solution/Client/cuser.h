#ifndef CUSER_H
#define CUSER_H

#include "iuser.h"

class cuser : public iuser
{
protected:
    QString username;
    QString password;

public:
    cuser(QString usern,QString passwd);
    ~cuser();
    virtual bool sendCredentials()=0;
    void LogOut();
    virtual bool verifyconfirmation(QString passwd)=0;
};

#endif // CUSER_H
