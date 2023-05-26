#include "RequestBack.h"
#include "DB.h"

RequestBack::RequestBack()
{
	this->log = nullptr;
	this->raspuns = nullptr;
}

RequestBack::RequestBack(string sentence)
{
	vector<string> sentences = Tools::split(sentence, '/');
	this->log = sentences[1];
}

void RequestBack::gestionare_request()
{
	bool var = DB::getInstance().backUser(this->log);
	if (var)
	{
		this->raspuns = "OK";
	}
	else
	{
		this->raspuns = "NOK";
	}
}

string RequestBack::gestionare_raspuns()
{
	return this->raspuns;
}
