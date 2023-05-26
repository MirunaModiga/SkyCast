#ifndef IEXCEPTIE_H
#define IEXCEPTIE_H
#include <QString>
#include<QMessageBox>
class IExceptie
{
public:
    IExceptie();
    virtual void LoginError()=0;
    virtual void RegisterError()=0;
    virtual void WrongConfirmation()=0;
    virtual void NotAbleToConnect()=0;
    virtual void WaitedforToMuchTime()=0;
    virtual void DisableConnection()=0;
    virtual void WrongCity()=0;


};

#endif // IEXCEPTIE_H
