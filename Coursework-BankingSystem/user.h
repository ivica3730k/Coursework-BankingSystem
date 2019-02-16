#pragma once
#include "pch.h"
using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::getline;
class user
{
public:
	user(database &_db);
	//User only specific functions********
	bool login(void);
	bool login(string* email, string* password);
	bool login(const char* email, const char* password);
	bool logout(void);
	bool changePass(string* oldpass, string*newpass, string *email);

	//Data export functions**********
	dbUserData listInfo(void);
	dbUserData listInfo(string *email);

	//Data export to file functions***
	bool printOut(void);
	bool printOut(string *email);
	bool printOut(const char *email);

	//ADMIN: User add functions*************
	bool add(void);
	bool add(string* name, string* surname, string * eMail, string * password, bool isAdmin);
	bool add(const char *name, const char* surname, const char * eMail, const char * password, bool isAdmin);

	//ADMIN: User delete functions**********
	bool del(void);
	bool del(string* email);
	bool del(const char * email);

	//ADMIN: list functions************
	bool listAll(void);


private:
	database *db;
};

