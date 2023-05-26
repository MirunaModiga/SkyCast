#pragma once
#include "IRequest.h"

class RequestRegisterCity :public IRequest
{
	string city;
	string raspuns;
public:
	RequestRegisterCity();
	/*RequestRegisterCity(string sentence);
	void gestionare_request();
	string gestionare_raspuns();*/

};