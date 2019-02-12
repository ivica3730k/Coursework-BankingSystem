#pragma once
#include "sqlite3.h"
using std::string;

class database
{
public:
	database(const char *path);
	string hash(string* data);
	bool createUser(string* name, string* surname, string * eMail,string * password,bool isAdmin);
	
private:
	sqlite3 *db;
};

