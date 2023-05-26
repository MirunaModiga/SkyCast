#pragma once
#include <iostream>
#include <mysql.h>
#include "Exception.h"
using namespace std;

class DB
{
private:
	static DB* instance;
	int qstate;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;		
	//string latitude;
	//string longitude;
	DB() {
		conn = mysql_init(0);	//initializez conexiunea la baza de date
		conn = mysql_real_connect(conn, "localhost", "root", "modi4112", "skycast", 3306, NULL, 0);	
		//conectarea la baza de date "skycast" de pe serverul local (localhost)

		try {
			if (conn)
				Log::write("Connection to database has been successful!");
			else
				throw new Exception(401, "FAILED connection to database");
		}
		catch (Exception* e)
		{
			e->what();
		}
	}
public:
	static DB& getInstance();
	void destroyInstance();

	bool registerUser(string username, string  password, string email,string city); //0
	bool loginUser(string username, string  password); //1
	bool logOutUser(string log); //5
	bool backUser(string log); //4
	int requestForecast(string city); //2
};

