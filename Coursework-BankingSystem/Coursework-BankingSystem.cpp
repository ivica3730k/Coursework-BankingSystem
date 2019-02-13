#include "pch.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;


int main()
{
	database db("database.db");
	

	string name = "test1";
	string surname = "user1";
	string password = "testuserpass1";
	string email = "testuser@test";
	bool isAd = false;
	cout << db.checkUserTest(&email).name << endl;
	//db.createUser(&name, &surname, &password, &email, isAd);
	

	return(1);
  
}

