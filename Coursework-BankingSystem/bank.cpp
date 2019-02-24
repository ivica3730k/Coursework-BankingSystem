#pragma once
#include "pch.h"
#include "bank.h"


bank::bank(database &_db)
{
	db = &_db;
	availableCurrencies = getCurencies();
}


bank::~bank()
{
}


std::vector<std::string> bank::getCurencies(void)
{
	std::vector <std::string> toReturn;
	std::vector<std::string> currset;
	db->checkCurrencies(&currset);
	//VariadicTable<std::string, std::string> vt({"Currency", "Label"});

	std::vector<string>::iterator i;

	for (i = currset.begin(); i < currset.end(); ++i) {
		std::string Currency = *i;
		toReturn.push_back(*i);
		++i;
		std::string Label = *i;


		//vt.addRow({ Currency, Label });
	}

	//vt.print(std::cout);
	return(toReturn);

}

std::vector<std::string> bank::getCurenciesTable(void)
{
	std::vector <std::string> toReturn;
	std::vector<std::string> currset;
	db->checkCurrencies(&currset);
	VariadicTable<std::string, std::string> vt({"Currency", "Label"});

	std::vector<string>::iterator i;

	for (i = currset.begin(); i < currset.end(); ++i) {
		std::string Currency = *i;
		toReturn.push_back(*i);
		++i;
		std::string Label = *i;


		vt.addRow({ Currency, Label });
	}

	vt.print(std::cout);
	return(toReturn);
}

bool bank::addCurrency(void)
{
	std::cout << "Enter currency name: ";
	std::string name;
	std::getline(std::cin, name);
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	name[0] = toupper(name[0]);
	std::cout << "Enter currency label: ";
	std::string label;
	std::getline(std::cin, label);
	std::transform(label.begin(), label.end(), label.begin(), ::toupper);
	
	bool exec = db->addCurrency(&name, &label);

	return exec;
}

