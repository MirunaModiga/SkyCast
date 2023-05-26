#include "RequestLogin.h"
#include "RequestRegister.h"
#include "RequestRegisterCity.h"
#include "RequestForecast.h"
#include "RequestLogout.h"
#include "RequestBack.h"

IRequest* IRequest::Factory::getRequest(string sentence)
{
	int key = stoi(Tools::split(sentence, '/')[0]);

	switch (key) {
	case 0:
		return new RequestRegister(sentence);
	case 1:
		return new RequestLogin(sentence);
	case 2:
		return new RequestForecast(sentence);
	case 4:
		return new RequestBack(sentence);
	case 5:
		return new RequestLogout(sentence);
	default:
		return nullptr;
	}
}
