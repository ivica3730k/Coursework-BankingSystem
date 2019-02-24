#pragma once
#include "pch.h"
#include "sqlite3.h"
using std::string;


struct additionalData {
	string title;
	string nationality;
	string dateOfBirth;
	string placeOfBirth;
	string address;
	string phonenum;
};

struct UserData {

	bool isValid = 0;
	string name;
	string surname;
	string email;
	string password;
	string isAdmin;
	string lastLogOut;
	void clear(void);

};


class database
{
public:
	bool createUserBalance(string* email);
	database(const char *path);
	bool createUser(string* name, string* surname, string * eMail,string * password,bool isAdmin);
	bool deleteUser(string* email);
	bool loginUser(string* email, string*password, UserData &_data);
	bool listAllUsers(std::vector<string> *a);
	bool updateUserDetails(string* email, additionalData &data);
	bool checkAllDetails(string* email, std::vector<std::string> *data);
	bool setlastLogOut(string* email);

	bool checkCurrencies(std::vector <std::string> *currset);
	bool addCurrency(string* name, string* label);
	
private:
	UserData checkUser(string * email);
	sqlite3 *db =nullptr;
	bool executeQuery(string * _query, int(*f)(void *, int , char **, char **), void* data);
	bool executeQuery(string * _query, int(*f)(void *, int, char **, char **));
	string returnTime(void);
	string hash(string * data);
	bool deleteUserBalance(string* email);

	


	//callbacks
	static int callbackUsers(void *dataptr, int argc, char **argv, char **azColName);
	static int noCallback(void *dataptr, int argc, char **argv, char **azColName);
	static int callbackCheckAllUserDetails(void* dataptr, int argc, char** argv, char** azColName);
	static int callbackToVector(void* dataptr, int argc, char** argv, char** azColName);

	
};

