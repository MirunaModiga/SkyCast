#include "RequestLogin.h"
#include "DB.h"

RequestLogin::RequestLogin()
{
	this->username = nullptr;
	this->password = nullptr;
	this->raspuns = nullptr;
}

RequestLogin::RequestLogin(string sentence)
{
	vector<string> sentences = Tools::split(sentence, '/');
	this->username = sentences[1];
	this->password = sentences[2];
}

void RequestLogin::gestionare_request()
{
	bool var = DB::getInstance().loginUser(this->username, this->password);
	if (var)
	{
		this->raspuns = Tools::sendWeather(Tools::getWeatherString());
		Tools::deleteForecast();
	}
	else
	{
		this->raspuns = "NOK";
	}
}

string RequestLogin::gestionare_raspuns()
{
	return this->raspuns;
}
