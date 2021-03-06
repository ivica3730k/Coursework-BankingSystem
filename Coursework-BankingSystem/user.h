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
	user(database &_db,bank &_bank);
	//User only specific functions********
	bool login(UserData &data);
	bool login(string* email, string* password,UserData &data);
	bool changePass(string* email);
	bool logout(string* email);
	bool checkBalance(string*email);

	bool checkByeMail(void);
	bool checkByeMail(string*mail);

	bool writeAdditionalInfo(string *email, additionalData data);

	

	//Data export functions**********
	UserData listInfo(void);
	UserData listInfo(string *email);

	//Data export to file functions***
	bool printOut(void);
	bool printOut(string *email);
	bool printOut(const char *email);

	//ADMIN: User add functions*************
	bool add(void);
	bool add(string* name, string* surname, string * eMail, string * password, bool isAdmin);
	

	//ADMIN: User delete functions**********
	bool del(void);
	bool del(string* email);


	//ADMIN: list functions************
	bool listAll(void);


private:
	bank *banking;
	database *db;
	
};

