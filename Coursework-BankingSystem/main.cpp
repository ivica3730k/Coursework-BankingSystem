#include "pch.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	database db("database.db"); //create instance of database type db
	bank bank(db);
	user user(db,bank); //and assign it to user class of user



	cout << "Welcome to Virtual Currency trading platform!" << endl;

	do {

		cout << endl;
		cout << "1.Login" << endl;
		cout << "0.Exit";
		cout << "\nPlease input your choice: ";
		int choice = INT_MAX;
		cin >> choice;
		while ((getchar()) != '\n');
		cout << endl;

		if (choice == 1) {
			UserData data;
			if (user.login(data)) {
				menu menu(&data, user,bank);
				menu.display();
				menu.~menu();
			}
		}
		else if (choice == 0) {
			break;
		}
		else {

			cout<< "\nWrong input,please try again!" << endl;
		}

	} while (true);

	return (1);
}
