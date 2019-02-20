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

	cout << data.isAdmin << endl;
	if (data.isAdmin == "Yes") {
		cout << fmt::format("Welcome back, Admin {0} {1}.", data.name, data.surname) << endl;
		user.add();
	
	}
	else {
		cout << fmt::format("Welcome back, {0} {1}.", data.name, data.surname) << endl;
		if (data.lastLogin == "Never") {
			/*additionalData extraUserData;
			menu::completeData(extraUserData);
			db.updateUserDetails(&data.email, extraUserData);*/
			user.getAditionalInfo(&data.email);
			return(1);
		}

	}

	/*
	
	
	user.add("Ivica", "Matic", "ivica20002003@gmail.com", "motobecane2", true);
	UserData userdata;
	user.login(userdata);
	cout << userdata.lastLogin << endl;

	UserData userdata2;
	string password = "12345678";
	string email = "email.com";
	user.login(&email, &password, userdata2);
	cout << userdata.lastLogin << endl;


	return 0;
	*/

	/*
	database db("database.db"); //create instance of database type db
	user user(db); //and assign it to user class of user
	string name = "test1";
	string surname = "user1";
	string password = "12345678";
	string email = "email.com";
	bool isAd = false;
	//cout << db.checkUser(&email).name << endl;
	user.add(&name, &surname,&email,&password,isAd);

	user.del();
	*/
	return (1);
}
