#include "RequestRegister.h"
#include "DB.h"

RequestRegister::RequestRegister()
{
	this->username = nullptr;
	this->password = nullptr;
	this->email = nullptr;
	this->city = nullptr;
	this->raspuns = nullptr;
}

RequestRegister::RequestRegister(string sentence)
{
	vector<string> sentences = Tools::split(sentence, '/');
	this->username = sentences[1];
	this->password = sentences[2];
	this->email = sentences[3];
	this->city = sentences[4];
}

void RequestRegister::gestionare_request()
{
	bool var = DB::getInstance().registerUser(this->username, this->password, this->email,this->city);
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

string RequestRegister::gestionare_raspuns()
{
	return this->raspuns;
}
