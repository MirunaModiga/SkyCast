#pragma once
#include <iostream>
#include <string>
#include "Tools.h"
using namespace std;

class IRequest
{
public:
	virtual void gestionare_request() = 0;
	virtual string gestionare_raspuns() = 0;

	class Factory
	{
	public:
		static IRequest* getRequest(string sentence);
	};
};