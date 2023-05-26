#ifndef REQUESTLOGOUT_H
#define REQUESTLOGOUT_H

#include "irequest.h"

class RequestLogout : public IRequest
{
public:
    RequestLogout();
    ~RequestLogout(){};
    bool _request();
};

#endif // REQUESTLOGOUT_H
