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

	if (data.isValid) {
		if (data.isAdmin == "Yes") {
			cout << fmt::format("Welcome back, Admin {0} {1}.", data.name, data.surname) << endl;
			//user.add();
			user.del();
		
		}
		else {
			cout << fmt::format("Welcome back, {0} {1}.", data.name, data.surname) << endl;
			if (data.lastLogin == "Never") {
				user.getAditionalInfo(&data.email);
				return(1);
			}

		}
	}
	
	return (1);
}
