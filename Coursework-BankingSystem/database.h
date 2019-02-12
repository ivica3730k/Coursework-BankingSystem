#pragma once
#include "sqlite3.h"
#include "fmt-master/format.h"
#include "picosha2.h"
using std::string;



struct dbUserData {
	bool isValid = 0;
	string name;
	string surname;
	string email;
	string password;
	bool isAdmin;
	string lastLogin;
	

};
class database
{
public:
	database(const char *path);
	bool createUser(string* name, string* surname, string * eMail,string * password,bool isAdmin);
	dbUserData checkUser(string * email);
private:
	sqlite3 *db;
	string hash(string* data);
	static int callbackUsers(void *dataptr, int argc, char **argv, char **azColName);
	char* data[];
	
};

