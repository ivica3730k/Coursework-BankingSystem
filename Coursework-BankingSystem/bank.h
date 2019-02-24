#pragma once
#include "pch.h"
class bank
{
public:
	bank(database &_db);
	std::vector <std::string> availableCurrencies;
	std::vector<std::string> getCurencies(void);
	std::vector<std::string> getCurenciesTable(void);
	bool addCurrency(void);
	~bank();
private:
	database *db;
};

