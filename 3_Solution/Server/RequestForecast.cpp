#include "RequestForecast.h"
#include "DB.h"

RequestForecast::RequestForecast()
{
	this->city = nullptr;
	this->raspuns = nullptr;
}

RequestForecast::RequestForecast(string sentence)
{
	vector<string> sentences = Tools::split(sentence, '/');
	this->city = sentences[1];
}

void RequestForecast::gestionare_request()
{
	int var = DB::getInstance().requestForecast(this->city);
	if (var == 3)
	{
		this->raspuns = Tools::sendWeather(Tools::getWeatherString());
		Tools::deleteForecast();
	}
	else
	{
		if (var == 1) {
			this->raspuns = "wrong city";
		}
		else if (var == 2) {
			this->raspuns = "eroare API";
		}
	}
}

string RequestForecast::gestionare_raspuns()
{
	return this->raspuns;
}

