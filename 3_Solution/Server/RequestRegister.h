#pragma once
#include "IRequest.h"

class RequestRegister :public IRequest
{
	string username;
	string password;
	string email;
	string city;
	string raspuns;
public:
	RequestRegister();
	RequestRegister(string sentence);
	void gestionare_request(); 
	string gestionare_raspuns();

};