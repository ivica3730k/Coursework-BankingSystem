#include "pch.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	database db("database.db"); //create instance of database type db
	user user(db); //and assign it to user class of user

	do {
		UserData data;
		//add ability to exit or to log in again here
		cout << "LogIN" << endl;
		if (user.login(data)) {
			menu menu(&data, user);
			menu.display();
			menu.~menu();
		}

	} while (true);

	return (1);
}
