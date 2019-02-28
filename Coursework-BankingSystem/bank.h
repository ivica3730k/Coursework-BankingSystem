#pragma once
#include "pch.h"
class bank
{
public:
	bank(database &_db);
	std::vector <std::string> availableCurrencies;
	std::vector<std::string> getCurencies(void);
	std::vector<std::string> getCurenciesTable(void);
	void printAllBalance(string * email);
	void printOneBalance(string * email);
	bool transfer(string* sendermail);
	bool addCurrency(void);

	

	~bank();
private:
	bool setBalance(string* email, string* label, double &balance);
	bool getBalance(string* email, string*label, double &balance);
	database *db;
};

