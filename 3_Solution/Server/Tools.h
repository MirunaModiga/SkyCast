#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Tools
{
private:
	static vector<string>forecast;
public:
	static vector<string> getWeatherString() { return forecast; }
	static vector<string> split(string word, char delimiter);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static string sendWeather(vector<string>forecast);

	static json getWeatherData(const string& url);
	static void processWeatherData(const json& data,string city);
	static int getForecast(string city);

	static string base64(string password);
	static string hashPass(string password);
	static bool check_city_exists(string city);
	static void deleteForecast() { Tools::forecast.clear(); }
};
