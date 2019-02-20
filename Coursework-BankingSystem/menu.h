#pragma once
#include "pch.h"
class menu
{
public:
	menu(UserData *data,user &_user);
	~menu();
	void display(void);
	void adminMenu(void);
	void completeData(void);
private:
	
	UserData *userdata;
	user *userset;
	std::string name;
	std::string surname;
	std::string email;
	std::string isAdmin;
	bool admin;
	std::string lastLogin;
};

