#ifndef REQUESTBACK_H
#define REQUESTBACK_H

#include "irequest.h"

class RequestBack : public IRequest
{
public:
    RequestBack();
    ~RequestBack(){};
    bool _request();
};

#endif // REQUESTBACK_H
