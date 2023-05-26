#pragma once
#include "IRequest.h"
class RequestBack :public IRequest
{
	string log;
	string raspuns;
public:
	RequestBack();
	RequestBack(string sentence);
	void gestionare_request();
	string gestionare_raspuns();
};

