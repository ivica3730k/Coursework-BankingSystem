#include "pch.h"
#include "fmt-master/format.h"

int main()
{	
	
	database db("database.db"); 
	std::string a = "Ivica";
	
	std::cout << db.createUser(&a, &a, &a, &a, 0) << std::endl;
	
	return(1);
  
}

