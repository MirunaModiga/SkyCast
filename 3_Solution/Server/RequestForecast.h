#pragma once
#include "IRequest.h"

class RequestForecast :public IRequest
{
	string city;
	string raspuns;
public:
	RequestForecast();
	RequestForecast(string sentence);
	void gestionare_request();
	string gestionare_raspuns();

};