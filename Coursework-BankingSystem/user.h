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
	bool changePass(string* oldpass, string*newpass, string *email);
	//User add functions*************
	bool add(void);
	bool add(string* name, string* surname, string * eMail, string * password, bool isAdmin);
	bool add(const char *name, const char* surname, const char * eMail, const char * password, bool isAdmin);
	//User delete functions**********
	bool del(void);
	bool del(string* email);
	bool del(const char * email);
	//User list functions************
	bool listAll(void);
	//Data export functions**********
	dbUserData listInfo(void);
	dbUserData listInfo(string *email);
	//Data export to file functions***
	bool printOut(void);
	bool printOut(string *email);

private:
	database *db;
};

