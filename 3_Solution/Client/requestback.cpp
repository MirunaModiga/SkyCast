#include "requestback.h"

RequestBack::RequestBack()
{

}

bool RequestBack::_request()
{
   QString ans=tcpclient::getInstance().getData("4/Back/");
   return true;
}
