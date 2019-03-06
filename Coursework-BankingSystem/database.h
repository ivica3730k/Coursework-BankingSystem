#pragma once
#include "pch.h"
#include "sqlite3.h"
using std::string;

struct balance {
	unsigned long int id;
	std::string senderEmail;
	std::string receiver;
	double amount;
	std::string currency;
	std::string createdOn;
	std::string claimed;

};

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
	

};


class database
{
public:
	
	database(const char *path);
	bool createUser(string* name, string* surname, string * eMail,string * password,bool isAdmin);
	bool createUserBalance(string* email);
	bool deleteUser(string* email);
	bool loginUser(string* email, string*password, UserData &_data);
	bool changePassword(string*email, string*oldpass, string*newpass);
	bool setlastLogOut(string* email);
	bool updateUserDetails(string* email, additionalData &data);
	bool checkAllDetails(string* email, std::vector<std::string> *data);
	bool listAllUsers(std::vector<string> *a);

	bool checkCurrencies(std::vector <std::string> *currset);
	bool addCurrency(string* name, string* label);
	bool checkBalance(std::vector <std::string> *balance,string * email);
	bool checkBalance(std::string* balance, std::string *currency, std::string*email);
	bool setUserBalance(string*email, string* currency, double& balance);
	string returnTime(void);
	UserData checkUser(string * email);
	unsigned long int getLastTransferId(void);
	bool logTransfer(string* senderMail,string* receiver,double amount, string* currency);
	bool logExportTransfer(string* senderMail, string* receiver, double amount, string* currency);
	bool readExportLog(unsigned long int id, balance & data);
	bool setClaimed(unsigned long int transferId);




private:
	
	sqlite3 *db =nullptr;
	string hash(string * data);

	bool deleteUserBalance(string* email);
	bool executeQuery(string * _query, int(*f)(void *, int, char **, char **), void* data);
	bool executeQuery(string * _query, int(*f)(void *, int, char **, char **));

	//callbacks
	static int callbackUsers(void *dataptr, int argc, char **argv, char **azColName);
	static int noCallback(void *dataptr, int argc, char **argv, char **azColName);
	static int callbackCheckAllUserDetails(void* dataptr, int argc, char** argv, char** azColName);
	static int callbackToVector(void* dataptr, int argc, char** argv, char** azColName);
	static int callbackOneString(void* dataptr, int argc, char** argv, char** azColName);
	static int callbackToVectorColNames(void* dataptr, int argc, char** argv, char** azColName);

	
};

