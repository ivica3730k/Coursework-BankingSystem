#pragma once
#include "pch.h"
class menu
{
public:
	menu(UserData *data,user &_user);
	~menu();
	int display(void);

	
private:

	void adminMenu(void);
	void userMenu(void);
	bool completeData(void);
	
	UserData *userdata;
	user *userset;
	std::string name;
	std::string surname;
	std::string email;
	std::string isAdmin;
	bool admin;
	std::string lastLogOut;

	
};

