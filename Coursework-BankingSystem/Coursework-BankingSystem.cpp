#include "pch.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;


int main()
{
	database db("database.db"); //create instance of database type db
	user user(db); //and assign it to user class of user

	user.add();

	
	
	/*
	string name = "test1";
	string surname = "user1";
	string password = "12345678";
	string email = "email.com";
	bool isAd = false;
	//cout << db.checkUser(&email).name << endl;
	//db.createUser(&name, &surname,&email,&password,isAd);
	std::cout<<db.loginUser(&email, &password);
	*/
	return(1);
  
}

