#include "pch.h"
#include "fmt-master/format.h"
using std::string;
int main()
{	
	
	database db("database.db"); 
	string name = "Leon";
	string surname = "Matic";
	string email = "leon23@gmail.com";
	string passwd = "medjed ko obicno";
	bool isAdmin = false;

	db.createUser(&name,&surname,&email,&passwd,isAdmin);
	//std::cout<<db.checkUser(&a).isValid<<std::endl;
	
	
	
	return(1);
  
}

