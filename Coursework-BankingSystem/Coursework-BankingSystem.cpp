#include "pch.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	database db("database.db"); //create instance of database type db
	user user(db); //and assign it to user class of user

	UserData data;
	user.login(data);

	menu menu(&data, user);
	menu.display();

	return (1);
}
