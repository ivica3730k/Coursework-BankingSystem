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

	std::vector<string>::iterator i;

	for (i = currset.begin(); i < currset.end(); ++i) {
		std::string Currency = *i;
		++i;
		std::string Label = *i;
		toReturn.push_back(*i);

	}

	return(toReturn);

}

std::vector<std::string> bank::getCurenciesTable(void)
{
	//std::cout << "Balances available on the system are: " << std::endl;
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


void bank::printOneBalance(string * email)
{
	std::cout << "Available currencies for you to check are" << std::endl;
	getCurenciesTable();
	std::cout << "\nInput label of currency you would like to check: ";
	std::string checkLabel;
	std::getline(std::cin, checkLabel);
	std::transform(checkLabel.begin(), checkLabel.end(), checkLabel.begin(), ::toupper);

	std::string balance;
	bool exec = db->checkBalance(&balance,&checkLabel, email);

	if (exec) {
		std::cout << std::stod(balance) << " " << checkLabel << endl;
	}

}

bool bank::transfer(string* sendermail)
{
	std::cout << "Available currencies to transfer are:" << std::endl;
	getCurenciesTable();
	std::vector<std::string> availableCurrencies = getCurencies();
	std::cout << std::endl;
	std::cout << "Input currency label you want to transfer:";
	std::string curr;
	std::getline(std::cin, curr);
	std::transform(curr.begin(), curr.end(), curr.begin(), ::toupper);

	if (std::find(availableCurrencies.begin(), availableCurrencies.end(), curr) != availableCurrencies.end() == false) {
		std::cout<<"\nThis currency is not present on the system, aborting transfer!" << std::endl;
		return false;
	}

	std::string _ammountToSend;
	std::cout << "\n"<<fmt::format("Input ammount of {0} you want to send: ",curr);
	std::getline(std::cin, _ammountToSend);
	double ammountToSend = stod(_ammountToSend);
	double availableAmmount;
	getBalance(sendermail, &curr, availableAmmount);

	if (ammountToSend > availableAmmount) {
		std::cout << "\n" << fmt::format("Ammount that you want to send exceeds your balance.Currently you have {0} {1} on your account,aborting transfer", availableAmmount, curr);
		return false;
	}

	if (ammountToSend <= 0) {
		std::cout << "\nAmmount to send can't be negative number or zero (0),aborting transfer!" << std::endl;
		return false;
	}

	std::string receiverEmail;
	std::cout << "\nInput eMail of the users you would like to send:";
	std::getline(std::cin, receiverEmail);
	std::transform(receiverEmail.begin(), receiverEmail.end(), receiverEmail.begin(), ::tolower);

	if (db->checkUser(&receiverEmail).isValid == false) {
		std::cout << "\n" << fmt::format("User with email {0} does not exsist on system, aborting transfer", receiverEmail);
		return false;
	}
	
	double newBalance = availableAmmount - ammountToSend;
	setBalance(sendermail, &curr, newBalance);

	double receiverAmmount;
	getBalance(&receiverEmail, &curr, receiverAmmount);
	receiverAmmount += ammountToSend;
	setBalance(&receiverEmail, &curr, receiverAmmount);

	std::cout << "\nTransfer completed sucesfully!" << std::endl;
	return true;

}

void bank::printAllBalance(string * email)
{
	
	std::vector<std::string> balance;
	bool exec = db->checkBalance(&balance, email);

	if (exec) {

		VariadicTable < std::string, std::string > vt({ "Currency","Ammount" });
		std::vector<string>::iterator j;

		for (j = balance.begin(); j < balance.end(); ++j) {
			std::string curr = *j;
			++j;
			std::string amm = *j;


			vt.addRow({curr,amm});
		}
		
		vt.print(std::cout);

	}
	
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

bool bank::getBalance(string * email, string * label,double &balance)
{
	std::transform(label->begin(), label->end(), label->begin(), ::toupper);
	std::vector<std::string> availableLabels = getCurencies();


	if (std::find(availableLabels.begin(), availableLabels.end(), *label) != availableLabels.end()){
		std::string _balance;
		db->checkBalance(&_balance, label, email);
		balance = (stod(_balance));
		return true;
	}

	std::cout << "This currency is not present on the system" << std::endl;

	return false;
}

bool bank::setBalance(string * email, string * label, double & balance)
{
	bool exec = db->setUserBalance(email, label, balance);
	return exec;
}


