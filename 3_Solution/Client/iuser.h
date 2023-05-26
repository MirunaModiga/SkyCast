#ifndef IUSER_H
#define IUSER_H
//#include"cexceptie.h"
#include <QString>

class iuser
{
public:
    iuser();
    ~iuser();
    virtual bool sendCredentials()=0;
    virtual void LogOut()=0;
    virtual bool verifyconfirmation(QString passwd)=0;


};

#endif // IUSER_H
