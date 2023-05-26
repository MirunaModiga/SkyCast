#pragma once
#include "IRequest.h"

class RequestLogout :public IRequest
{
	string log;
	string raspuns;
public:
	RequestLogout();
	RequestLogout(string sentence);
	void gestionare_request();
	string gestionare_raspuns();

};