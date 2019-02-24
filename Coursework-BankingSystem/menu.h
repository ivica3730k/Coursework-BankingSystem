#pragma once
#include "pch.h"
class menu
{
public:
	menu(UserData *data,user &_user,bank &_bk);
	~menu();
	int display(void);

	
private:

	void adminMenu(void);
	void userMenu(void);
	void completeData(void);
	void updateData(void);
	void wait(void);
	void clear(void);
	
	bank *banking;
	UserData *userdata;
	user *userset;
	std::string name;
	std::string surname;
	std::string email;
	std::string isAdmin;
	bool admin;
	std::string lastLogOut;

	
};

