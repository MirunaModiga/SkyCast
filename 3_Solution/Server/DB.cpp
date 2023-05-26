#include "DB.h"
#include "Exception.h"
#include "Tools.h"
#include <string.h>
#include <openssl/sha.h>

DB* DB::instance = nullptr;

DB& DB::getInstance()
{
	if (DB::instance == nullptr)
		DB::instance = new DB();

	return *DB::instance;
}

void DB::destroyInstance()
{
	if (DB::instance != nullptr)
	{
		delete DB::instance;
		DB::instance = nullptr;
	}
}

bool DB::registerUser(string username, string password, string email,string city)
{
	string userCity;
	// 0/Modi/modi4112/modi@yahoo.com/Craiova/
	//INSERT INTO Users (username, password,email,city) VALUES ("Modi","modi4112","modi@yahoo.com");
	string query2 = "SELECT username, email FROM Users;";
	const char* q2 = query2.c_str();
	int qstate2 = mysql_query(conn, q2);  //executa query-ul
	try
	{
		if (!qstate2)		//interogarea este efectuată cu succes -> qstate = 0 
		{
			res = mysql_store_result(conn);		//stochez rezultatele interogarii
			row = mysql_fetch_row(res);			
			while (row)
			{
				if (row[0] == username || row[2] == email)
				{
					throw new Exception(400, "REGISTER ERROR - username already taken!");
					return false;
				}
				row = mysql_fetch_row(res);
			}
			
			string hashPass = Tools::hashPass(password);

			string query = "INSERT INTO users (username, password, email,city) VALUES (\"" +
				username + "\",\"" + hashPass + "\",\"" + email + "\",\"" + city + "\");";
			const char* q = query.c_str();
			qstate = mysql_query(conn, q);  //executa query-ul
			if (!qstate)
			{
				res = mysql_store_result(conn);

				string query = "SELECT city FROM Users WHERE username=\"" + username + "\" AND password=\"" + hashPass + "\";";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				userCity = row[0];

				//DB::getInstance().registerCity(row[0]);
				//Tools::getForecast(userCity,this->latitude, this->longitude);

				Tools::getForecast(userCity);

				Log::write("REGISTER successful: User " + username + " created an account!");
				return true;
			}
			else
			{
				cout << "Query failed: " << mysql_error(conn) << endl;
				throw new Exception(400, "REGISTER ERROR - query failed");
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
			throw new Exception(400, "REGISTER ERROR - query failed");
		}
	}
	catch (Exception* e)
	{
		e->what();
		return false;
	}
}

bool DB::loginUser(string username, string password)
{
	string userCity;
	// 1/Modi/modi4112
	//SELECT Username, Password FROM users WHERE username="Modi" AND password="parola";
	string hashPass = Tools::hashPass(password);
	string query = "SELECT username, password FROM Users WHERE username=\"" + username + "\" AND password=\"" + hashPass + "\";";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);  //executa query-ul
	try
	{
		if (!qstate)
		{
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row)
			{
				string query = "SELECT city FROM Users WHERE username=\"" + username + "\" AND password=\"" + hashPass + "\";";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				userCity = row[0];

				//DB::getInstance().registerCity(row[0]);
				//Tools::getForecast(userCity, this->latitude, this->longitude);

				Tools::getForecast(userCity); 

				Log::write("LOGIN successful: User "+ username + " connected!");

				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
			throw new Exception(402, "LOGIN ERROR - query failed");
		}
	}
	catch (Exception* e)
	{
		e->what();
		return false;
	}
}

bool DB::logOutUser(string log)
{
	if (log == "Logout") {
		Log::write("LOGOUT");
		return true;
	}
	else
		return false;
}

bool DB::backUser(string log)
{
	if (log == "Back") {
		Log::write("BACK");
		return true;
	}
	else
		return false;
}

//bool DB::registerCity(string city)
//{
//	// 2/Tecuci/
//	string query2 = "SELECT cityname FROM Cities;";
//	const char* q2 = query2.c_str();
//	int qstate2 = mysql_query(conn, q2);  //executa query-ul
//	try
//	{
//		if (!Tools::check_city_exists(city))
//		{
//			throw new Exception(401, "this CITY does not EXIST!");
//			return false;
//		}
//		if (!qstate2)
//		{
//			res = mysql_store_result(conn);
//			row = mysql_fetch_row(res);
//			while (row)
//			{
//				if (row[0] == city)
//				{
//					string querycoord = "SELECT latitudine,longitudine FROM Cities;";
//					const char* qcoord = querycoord.c_str();
//					int qstatecoord = mysql_query(conn, qcoord);  //executa query-ul
//					if (!qstatecoord)
//					{
//						res = mysql_store_result(conn);
//						row = mysql_fetch_row(res);
//						this->latitude = row[0];
//						this->longitude = row[1];
//
//
//						//Tools::getForecast(city, latitude, longitude);
//					}
//					return true;
//				}
//				row = mysql_fetch_row(res);
//			}
//			this->latitude = Tools::getCoordonates(city).first;
//			this->longitude = Tools::getCoordonates(city).second;
//
//			Tools::getForecast(city,latitude, longitude);
//
//			string query = "INSERT INTO Cities (cityname,latitudine,longitudine) VALUES (\"" +
//				city + "\",\"" + latitude + "\",\"" + longitude + "\");";
//			const char* q = query.c_str();
//			qstate = mysql_query(conn, q);  //executa query-ul
//			if (!qstate)
//			{
//				res = mysql_store_result(conn);
//
//				Log::write("REGISTER CITY successful: City " + city + " has been added!");
//				return true;
//			}
//			else
//			{
//				cout << "Query failed: " << mysql_error(conn) << endl;
//				throw new Exception(401, "REGISTER CITY ERROR - query failed");
//			}
//		}
//		else
//		{
//			cout << "Query failed: " << mysql_error(conn) << endl;
//			throw new Exception(401, "REGISTER CITY ERROR - query failed");
//		}
//	}
//	catch (Exception* e)
//	{
//		e->what();
//		return false;
//	}
//}

int DB::requestForecast(string city)
{
	return Tools::getForecast(city);
}
