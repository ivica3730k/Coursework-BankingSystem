#pragma once
#include "pch.h"
#include "sqlite3.h"
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
	bool loginUser(string* email, string*password);
	
private:
	sqlite3 *db =nullptr;
	bool executeQuery(string * _query, int(*f)(void *, int , char **, char **), void* data);
	bool executeQuery(string * _query, int(*f)(void *, int, char **, char **));
	bool setLastLogin(string* email);
	string returnTime(void);
	string hash(string * data);
	
	//callbacks
	static int callbackUsers(void *dataptr, int argc, char **argv, char **azColName);
	static int noCallback(void *dataptr, int argc, char **argv, char **azColName);

	
};

