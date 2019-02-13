#include "pch.h"
using std::string;
int main()
{	
	
	database db("database.db"); 
	auth auth();
	string email = "ln3@gmaaXXisadsal.com";
	std::cout<< db.checkUser(&email).password << std::endl;
	
	return(1);
  
}

