#include "RequestRegisterCity.h"
#include "DB.h"

RequestRegisterCity::RequestRegisterCity()
{
	this->city = nullptr;
	this->raspuns = nullptr;
}

//RequestRegisterCity::RequestRegisterCity(string sentence)
//{
//	vector<string> sentences = Tools::split(sentence, '/');
//	this->city = sentences[1];
//}
//
//void RequestRegisterCity::gestionare_request()
//{
//	bool var = DB::getInstance().registerCity(this->city);
//	if (var)
//	{
//		this->raspuns = Tools::sendWeather(Tools::getWeatherString());
//		//this->raspuns = "OK";
//	}
//	else
//	{
//		this->raspuns = "NOK";
//	}
//}
//
//string RequestRegisterCity::gestionare_raspuns()
//{
//	return this->raspuns;
//}
