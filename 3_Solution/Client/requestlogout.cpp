#include "requestlogout.h"

RequestLogout::RequestLogout()
{

}

bool RequestLogout::_request()
{
   QString ans=tcpclient::getInstance().getData("5/Logout/");
   return true;
}
