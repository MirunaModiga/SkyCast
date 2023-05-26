#pragma once
#include "IRequest.h"

class RequestLogin :public IRequest
{
	string username;
	string password;
	string raspuns;
public:
	RequestLogin();
	RequestLogin(string sentence);
	void gestionare_request();
	string gestionare_raspuns();

};