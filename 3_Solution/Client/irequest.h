#ifndef IREQUEST_H
#define IREQUEST_H

#include<QString>
#include"tcpclient.h"
#include "getweather.h"

class IRequest
{
public:
    IRequest();
    virtual bool _request()=0;
protected:

};

#endif // IREQUEST_H
