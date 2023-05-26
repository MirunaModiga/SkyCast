#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Log
{
private:
	std::string message;
	std::string file_log;
public:
	Log(){}
	static void write(std::string message);
};
