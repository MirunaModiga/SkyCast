#pragma once
#include "Log.h"

class Exception
{
private:
	std::string message;
	int error_code;
public:
	Exception(int code, std::string message) :error_code(code), message(message) {
		Log::write("EXCEPTION CODE " + std::to_string(error_code));
	}
	void what();
};