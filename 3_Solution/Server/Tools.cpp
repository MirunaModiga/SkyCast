#define _CRT_SECURE_NO_WARNINGS
#include "Tools.h"
#include <curl/curl.h>
#include "rapidjson/document.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <memory.h>
#include <cstring>
#include <stdexcept>
#include <time.h>
#include "Exception.h"
#include"openssl/sha.h"

const std::string API_KEY = "a62b50492d5b4d58a7c73521232505";

vector<string> Tools::forecast;

vector<string> Tools::split(string word, char delimiter)
{
	string aux = "";
	vector<string>cuvinte;
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i] != delimiter)
		{
			aux += word[i];
		}
		else
		{
			cuvinte.push_back(aux);
			aux = "";
		}
	}
	return cuvinte;
}

size_t Tools::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


string Tools::sendWeather(vector<string>forecast)
{
    string weather;
    for (int i = 0; i < forecast.size(); i++) {
        weather.append(forecast[i]).append("/");
    }
    return weather;
}


//pair<string,string> Tools::getCoordonates(string city)
//{
//    CURL* curl;
//    CURLcode res;
//    for (int i = 0; i < city.size(); i++) {
//        if (city[i] == ' ') {
//            city[i] = '_';
//        }
//    }
//    string api_url = "https://api.api-ninjas.com/v1/geocoding?city=";
//    api_url.append(city).append("&country=").append("RO");
//    string response;
//    string latitude;
//    string longitude;
//
//    curl_global_init(CURL_GLOBAL_ALL);
//
//    curl = curl_easy_init();
//    if (curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
//
//        // Setam header-ul pentru cheia de API
//        struct curl_slist* headers = NULL;
//        headers = curl_slist_append(headers, "X-Api-Key: F15JSIXn83Hm1A5TOoLuwA==LeoDvMqE9qnX4lbt");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//
//        // Setam optiunea pentru a scrie datele primite intr-o variabila
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//        res = curl_easy_perform(curl);
//        if (res != CURLE_OK)
//        {
//            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//        }
//        else {
//            long http_status;
//            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
//            if (http_status == 200) {
//                // Process the response data
//            getResponseLat:
//                curl_slist_free_all(headers);
//                curl_easy_cleanup(curl);
//
//                Log::write("Request to GECODING API has been successful!");
//
//                vector<std::string> parts = splitAPIcoord(response, ",");
//
//                for (const std::string& part : parts)
//                {
//                    if (latitude.size() != 0 && longitude.size() != 0)
//                        break;
//                    if (part.find("\"lat") != string::npos)
//                    {
//                        latitude = splitAPIcoord(part, ":")[1];
//                    }
//                    else if (part.find("\"lon") != string::npos)
//                    {
//                        longitude = splitAPIcoord(part, ":")[1];
//                    }
//                }
//
//                curl_global_cleanup();
//
//                return make_pair(latitude, longitude);
//            }
//            else {
//                // Handle the error
//                std::cout << "API request failed with HTTP status code: " << http_status << std::endl;
//                int retries = 0;
//                try {
//                    while (retries < 3) {
//                        // Calculate the delay before the next retry using exponential backoff
//                        int delay_ms = (1 << retries) * 1000;
//                        std::cout << "Retrying after " << delay_ms << "ms..." << std::endl;
//
//                        // Wait for the specified delay before retrying
//                        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
//
//                        // Make the API request again
//                        res = curl_easy_perform(curl);
//                        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
//                        // ...
//                        if (http_status == 200) {
//                            // Process the response
//                            // ...
//                            goto getResponseLat;
//                            /*std::cout << "API request failed with HTTP status code: " << http_status << std::endl;
//                            return;*/
//                        }
//
//                        // Increment the number of retries
//                        retries++;
//                    }
//                    // If all retries fail, throw an exception or handle the error
//                    throw new Exception(502, "API GEOCODING request failed after multiple retries.");
//                }
//                catch (Exception* e)
//                {
//                    e->what();
//                }
//
//            }
//        }
//
//    }
//}

//void Tools::getForecast(string city, string latitude, string longitude)
//{
//    CURL* curl;
//    CURLcode res;
//
//    if (latitude[0] == ' ')
//        latitude.erase(0, 1);
//    if (longitude[0] == ' ')
//        longitude.erase(0, 1);
//
//    string api_url = "https://api.api-ninjas.com/v1/weather?";
//    api_url.append("lat=").append(latitude);
//    api_url.append("&lon=").append(longitude);
//
//    string response;
//
//    curl_global_init(CURL_GLOBAL_ALL);
//
//    curl = curl_easy_init();
//    if (curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
//
//        // Setam header-ul pentru cheia de API
//        struct curl_slist* headers = NULL;
//        headers = curl_slist_append(headers, "X-Api-Key: F15JSIXn83Hm1A5TOoLuwA==LeoDvMqE9qnX4lbt");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//
//        // Setam optiunea pentru a scrie datele primite intr-o variabila
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//        res = curl_easy_perform(curl);
//        if (res != CURLE_OK)
//        {
//            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
//        }
//        else {
//            long http_status;
//            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
//            if (http_status == 200) {
//                // Process the response data
//            getResponse:
//                curl_slist_free_all(headers);
//                curl_easy_cleanup(curl);
//
//                Log::write("Request to WEATHER API has been successful!");
//                try {
//                    rapidjson::Document doc;
//                    if (doc.Parse(response.c_str()).HasParseError()) {
//                        throw new Exception(100, "Rapidjson's assert IsObject() FAILED!");
//                    }
//                    doc.Parse(response.c_str());
//
//                    int cloud_pct = doc["cloud_pct"].GetInt();
//                    int temp = doc["temp"].GetInt();
//                    int feels_like = doc["feels_like"].GetInt();
//                    int humidity = doc["humidity"].GetInt();
//                    int min_temp = doc["min_temp"].GetInt();
//                    int max_temp = doc["max_temp"].GetInt();
//                    double wind_speed = doc["wind_speed"].GetDouble();
//                    int wind_degrees = doc["wind_degrees"].GetInt();
//                    int sunrise = doc["sunrise"].GetInt();
//                    int sunset = doc["sunset"].GetInt();
//
//                    std::cout << "Cloud percent: " << cloud_pct << std::endl;
//                    std::cout << "Temperature: " << temp << std::endl;
//                    std::cout << "Feels like: " << feels_like << std::endl;
//                    std::cout << "Humidity: " << humidity << std::endl;
//                    std::cout << "Min temperature: " << min_temp << std::endl;
//                    std::cout << "Max temperature: " << max_temp << std::endl;
//                    std::cout << "Wind speed: " << wind_speed << std::endl;
//                    std::cout << "Wind degrees: " << wind_degrees << std::endl;
//                    std::cout << "Sunrise: " << sunrise << std::endl;
//                    std::cout << "Sunset: " << sunset << std::endl;
//
//                    wind_speed = wind_speed * 3.6;
//
//                    Tools::forecast = { city, to_string(temp),to_string(feels_like),to_string(cloud_pct), to_string(humidity),to_string(min_temp) ,to_string(max_temp),to_string(wind_speed),to_string(sunrise),to_string(sunset) };
//
//                    curl_global_cleanup();
//                    return;
//                }
//                catch (Exception* e)
//                {
//                    e->what();
//                }
//                
//            }
//            else {
//                // Handle the error
//                std::cout << "API request failed with HTTP status code: " << http_status << std::endl;
//                int retries = 0;
//                try {
//                    while (retries < 3) {
//                        // Calculate the delay before the next retry using exponential backoff
//                        int delay_ms = (1 << retries) * 1000;
//                        std::cout << "Retrying after " << delay_ms << "ms..." << std::endl;
//
//                        // Wait for the specified delay before retrying
//                        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
//
//                        // Make the API request again
//                        headers = curl_slist_append(headers, "X-Api-Key: F15JSIXn83Hm1A5TOoLuwA==LeoDvMqE9qnX4lbt");
//                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//
//                        // Setam optiunea pentru a scrie datele primite intr-o variabila
//                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
//                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
//
//                        res = curl_easy_perform(curl);
//                        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status);
//                        // ...
//                        if (http_status == 200) {
//                            // Process the response
//                            // ...
//                            goto getResponse;
//                            /*std::cout << "API request failed with HTTP status code: " << http_status << std::endl;
//                            return;*/                    
//                        }
//
//                        // Increment the number of retries
//                        retries++;
//                    }
//                    // If all retries fail, throw an exception or handle the error
//                    throw new Exception(502,"API WEATHER request failed after multiple retries.");
//                }
//                catch (Exception* e)
//                {
//                    e->what();
//                }
//
//            }
//        }
//        
//    }
//}


json Tools::getWeatherData(const string& url) {

    int retryCount = 0;
    bool exceptionThrown = false;

    while (retryCount < 3 && exceptionThrown!=true) {
        try {
            CURL* curl;
            CURLcode res;
            std::string readBuffer;

            curl_global_init(CURL_GLOBAL_DEFAULT);
            curl = curl_easy_init();

            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                res = curl_easy_perform(curl);      // se efectuează cererea HTTP

                if (res != CURLE_OK) {
                    fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                    throw new Exception(502, "API WEATHER request FAILED!");
                }
                curl_easy_cleanup(curl);
            }

            curl_global_cleanup();

            rapidjson::Document doc;
            if (doc.Parse(readBuffer.c_str()).HasParseError()) {
                throw new Exception(100, "Rapidjson's assert IsObject() FAILED!");
            }

            if (readBuffer.find("error") != std::string::npos) {
                doc.Parse(readBuffer.c_str());
                int codeError = doc["error"]["code"].GetInt();
                string messError = doc["error"]["message"].GetString();

                // Retry if JSON has errors
                retryCount++;
                if (retryCount < 3) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
                }

                throw new Exception(codeError, messError);
            }
            else {
                return json::parse(readBuffer);
                Log::write("Request to WEATHER API has been successful!");
            }
        }
        catch (Exception* e) {
            e->what();
            retryCount++;
            if (retryCount < 3) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else {
                exceptionThrown = true;
            }
        }
    }
    try {
        if (retryCount >= 3 && exceptionThrown == true) {
            throw new Exception(100, "JSON request failed after 3 retries.");
        }
    }
    catch (Exception* e)
    {
        e->what();
    }
    

    /*try {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
                throw new Exception(502, "API WEATHER request FAILED!");
            }
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        if (readBuffer.find("error") != std::string::npos) {
            rapidjson::Document doc;
            if (doc.Parse(readBuffer.c_str()).HasParseError()) {

                throw new Exception(100, "Rapidjson's assert IsObject() FAILED!");
            }
            doc.Parse(readBuffer.c_str());
            int codeError = doc["error"]["code"].GetInt();
            string messError = doc["error"]["message"].GetString();
             
            throw new Exception(codeError, messError);
        }
        else {
            return json::parse(readBuffer);
        }
    }
    catch (Exception* e) {
        e->what();
    }*/

}

void Tools::processWeatherData(const json& data,string city) {
    // Procesez datele meteo conform cerințelor

    forecast.push_back(city);

    double temperature = data["current"]["temp_c"];
    double wind_speed = data["current"]["wind_kph"];
    int humidity = data["current"]["humidity"];
    int cloud = data["current"]["cloud"];
    double feels_like = data["current"]["feelslike_c"];
    double min_temp = data["forecast"]["forecastday"][0]["day"]["mintemp_c"];
    double max_temp = data["forecast"]["forecastday"][0]["day"]["maxtemp_c"];
    string sunrise_time = data["forecast"]["forecastday"][0]["astro"]["sunrise"];
    string sunset_time = data["forecast"]["forecastday"][0]["astro"]["sunset"];

    forecast.push_back(to_string(temperature));
    forecast.push_back(to_string(feels_like));
    forecast.push_back(to_string(cloud));
    forecast.push_back(to_string(humidity));
    forecast.push_back(to_string(min_temp));
    forecast.push_back(to_string(max_temp));
    forecast.push_back(to_string(wind_speed));
    forecast.push_back(sunrise_time);
    forecast.push_back(sunset_time);

    // Afisam datele
    std::cout << "Temperature: " << temperature << "C" << std::endl;
    std::cout << "Wind Speed: " << wind_speed << " kph" << std::endl;
    std::cout << "Humidity: " << humidity << "%" << std::endl;
    std::cout << "Cloud Cover: " << cloud << "%" << std::endl;
    std::cout << "Feels Like: " << feels_like << "C" << std::endl;
    std::cout << "Min Temperature: " << min_temp << "C" << std::endl;
    std::cout << "Max Temperature: " << max_temp << "C" << std::endl;
    std::cout << "Sunrise Time: " << sunrise_time << std::endl;
    std::cout << "Sunset Time: " << sunset_time << std::endl;

    // Extragem datele pentru temperatura din 3 in 3 ore incepand cu ora curenta
    // Obțin ora curentă din sistem
    time_t now = time(nullptr);
    int next_hour = ceil(tm(*localtime(&now)).tm_hour / 3.0) * 3;

    // Parcurg vectorul cu datele meteorologice și afișez temperatura pentru fiecare intrare aflată la o oră multiplu de 3 
    for (auto& hourly_data : data["forecast"]["forecastday"][0]["hour"]) {
        std::string time = hourly_data["time"];
        double temp = hourly_data["temp_c"];
        std::tm tm_time = {};
        std::istringstream ss(time);
        ss >> std::get_time(&tm_time, "%Y-%m-%d %H:%M:%S");
        int hour = tm_time.tm_hour;
        if (hour % 3 == next_hour % 3) {
            std::cout << "Time: " << time << ", Temperature: " << temp << "C" << std::endl;
            forecast.push_back(to_string(temp));
        }
    }

    // Extragem datele pentru temperatura minima si maxima pentru fiecare din cele 7 zile urmatoare
    vector<string> min_temps;
    vector<string> max_temps;
    vector <string>codes;

    for (auto& forecast_data : data["forecast"]["forecastday"]) {
        double min_temp = forecast_data["day"]["mintemp_c"];
        double max_temp = forecast_data["day"]["maxtemp_c"];
        min_temps.push_back(to_string(min_temp));
        max_temps.push_back(to_string(max_temp));
        string code = to_string(forecast_data["day"]["condition"]["code"]);
        string icon = forecast_data["day"]["condition"]["icon"];
        if (icon.find("day") != std::string::npos) {
            code += 'd';
        }
        if (icon.find("night") != std::string::npos) {
            code += 'n';
        }
        codes.push_back(code);
    }

    forecast.insert(forecast.end(), min_temps.begin(), min_temps.end());
    forecast.insert(forecast.end(), max_temps.begin(), max_temps.end());
    forecast.insert(forecast.end(), codes.begin(), codes.end());


    // Afisam datele
    std::cout << "Weather for " << data["location"]["name"] << ", " << data["location"]["country"] << " for the next 7 days:" << std::endl;
    for (int i = 0; i < 7; i++) {
        std::string date = data["forecast"]["forecastday"][i]["date"];
        std::cout << "Date: " << date << ", Min Temperature: " << min_temps[i] << "C, Max Temperature: " << max_temps[i] << "C" << std::endl;
        
    }

    // Extragem alertele
    std::vector<std::string> alerts;
    auto count_alert = data.count("alerts");
    if (data["alerts"]["alert"].size() > 0) {
        // procesează alertele
        for (auto& alert_data : data["alerts"]["alert"]) {
            std::string alert = alert_data["desc"];
            alerts.push_back(alert);
        }

        if (alerts.size() > 0) {
            std::cout << "Weather alerts for " << data["location"]["name"] << ", " << data["location"]["country"] << ":" << std::endl;
            for (auto& alert : alerts) {
                std::cout << alert << std::endl;
            }
        }
    }
    else {
        alerts.push_back("NOK");
    }
    cout << endl;

    forecast.insert(forecast.end(), alerts.begin(), alerts.end());

}

int Tools::getForecast(string city)
{
    /*if (!Tools::check_city_exists(city)) {
        return 1;
    }*/

    string copy_city = city;
    for (int i = 0; i < copy_city.size(); i++) {
        if (copy_city[i] == ' ') {
            copy_city[i] = '%20';
        }
    }

    string apiUrl = "http://api.weatherapi.com/v1/forecast.json?key=" + API_KEY + "&q=" + copy_city + "&days=7&aqi=no&alerts=yes";

    json weatherData = getWeatherData(apiUrl);
    try {
        if (weatherData.size()<=1) {
            throw new Exception(1000, "json EMPTY");
        }
        else {
            processWeatherData(weatherData, city);
            return 3;
        }
    }
    catch (Exception* e) {
        e->what();
        return 2;
    }
}

string Tools::base64(string password)
{
    const unsigned char* input = reinterpret_cast<const unsigned char*> (password.c_str());
    int length = strlen((char*)input);
    BIO* bmem, * b64;
    BUF_MEM* bptr;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char* buff = (char*)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length - 1);
    buff[bptr->length - 1] = 0;

    BIO_free_all(b64);

    return string(buff);
}

string Tools::hashPass(string password)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    unsigned char* dataS = new unsigned char[password.size()];
    strcpy(reinterpret_cast<char*>(dataS), password.c_str());

    SHA256(dataS, password.size(), hash);

    std::stringstream ss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return base64(ss.str());
}

bool Tools::check_city_exists(string city)
{
    ifstream file("oraseRO.txt");
    string line;
    while (getline(file, line)) {
        if (line == city) {
            return true;
        }
    }
    return false;
}


